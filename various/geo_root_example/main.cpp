#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TGeoShape.h"
#include "TGeoMatrix.h"
#include "TGeoMaterial.h"
#include "TGeoMedium.h"
#include "TGeoBBox.h"
#include "TGeoTube.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TPolyLine3D.h"
#include "TMath.h"

void defineGeometry() {
    // Create a geometry manager
    TGeoManager *geom = new TGeoManager("particleTransport", "Particle Transport Geometry");

    // Define materials
    TGeoMaterial *matVacuum = new TGeoMaterial("Vacuum", 0, 0, 0);
    TGeoMaterial *matIron = new TGeoMaterial("Iron", 55.85, 26, 7.87);

    // Define media
    TGeoMedium *vacuum = new TGeoMedium("Vacuum", 1, matVacuum);
    TGeoMedium *iron = new TGeoMedium("Iron", 2, matIron);

    // Create the top volume (world volume)
    TGeoVolume *top = geom->MakeBox("Top", vacuum, 100, 100, 100); // cm
    geom->SetTopVolume(top);

    // Create a box volume and add it to the top volume
    TGeoVolume *box = geom->MakeBox("Box", iron, 10, 10, 10); // cm
    top->AddNode(box, 1, new TGeoTranslation(0, 0, 0)); // cm

    // Create a tube volume and add it to the top volume
    TGeoVolume *tube = geom->MakeTube("Tube", iron, 0, 5, 20); // cm
    top->AddNode(tube, 1, new TGeoTranslation(20, 0, 0)); // cm

    // Close the geometry
    geom->CloseGeometry();
}

void simulateParticleTransport(int nParticles) {
    TGeoManager *geom = gGeoManager;
    if (!geom) {
        std::cerr << "Geometry not defined!" << std::endl;
        return;
    }

    // Get the dimensions of the top volume
    TGeoVolume *top = geom->GetTopVolume();
    TGeoBBox *topShape = (TGeoBBox*)top->GetShape();
    double xMax = topShape->GetDX();
    double yMax = topShape->GetDY();
    double zMax = topShape->GetDZ();

    // Create a canvas for drawing
    TCanvas *canvas = new TCanvas("canvas", "Particle Transport Visualization", 800, 600);
    top->Draw("gl"); // Draw the geometry

    TRandom random;

    for (int i = 0; i < nParticles; ++i) {
        // Define initial particle position and direction
        double x = random.Uniform(-xMax, xMax); // cm
        double y = random.Uniform(-yMax, yMax); // cm
        double z = random.Uniform(-zMax, zMax); // cm
        double dx = random.Uniform(-1.0, 1.0);  // direction cosines
        double dy = random.Uniform(-1.0, 1.0);
        double dz = random.Uniform(-1.0, 1.0);

        // Normalize direction
        double norm = TMath::Sqrt(dx * dx + dy * dy + dz * dz);
        dx /= norm;
        dy /= norm;
        dz /= norm;

        TPolyLine3D *track = new TPolyLine3D();
        track->SetPoint(0, x, y, z);

        // Transport the particle through the geometry
        for (int step = 0; step < 1000; ++step) {
            geom->FindNode(x, y, z);
            TGeoNode *node = geom->GetCurrentNode();
            if (!node) break;

            TGeoMaterial *material = node->GetVolume()->GetMedium()->GetMaterial();
            double stepLength = 1.0; // cm, step size

            // Apply simple scattering
            double theta = random.Gaus(0, 0.1); // small angle scattering
            double phi = random.Uniform(0, 2 * TMath::Pi());

            dx += stepLength * TMath::Sin(theta) * TMath::Cos(phi);
            dy += stepLength * TMath::Sin(theta) * TMath::Sin(phi);
            dz += stepLength * TMath::Cos(theta);

            // Normalize direction
            norm = TMath::Sqrt(dx * dx + dy * dy + dz * dz);
            dx /= norm;
            dy /= norm;
            dz /= norm;

            // Update position
            x += stepLength * dx;
            y += stepLength * dy;
            z += stepLength * dz;

            // Check if the particle is still within the top volume boundaries
            if (x < -xMax || x > xMax || y < -yMax || y > yMax || z < -zMax || z > zMax) break;

            track->SetNextPoint(x, y, z);
        }

        track->SetLineColor(kRed);
        track->Draw("SAME");
    }

    canvas->Update();
}

int main() {
    defineGeometry();
    simulateParticleTransport(10); // Generate and simulate 10 particles
    return 0;
}

