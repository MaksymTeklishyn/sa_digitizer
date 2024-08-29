#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH3D.h>
#include <TGeoManager.h>
#include <TGeoVolume.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoMatrix.h>
#include <TRandom3.h>
#include <TView.h>
#include "charge_carrier.h"
#include "electric_field.h"
#include "charge_carrier_transport.h"
#include "constants.h"
#include "field_functions.h"
#include "electrode.h"
#include "pixel.h"

int main(int argc, char **argv) {
    // Initialize ROOT application to handle graphics
    TApplication app("ROOT Application", &argc, argv);

    // Create the ElectricField object with the linearElectricField function
    ElectricField eField([](const TVector3& position) -> TVector3 {
        return diodElectricFieldZ(position, 320., 60., 150.);
    });
//  ElectricField eField;

    // Initialize a charge carrier at a specific position
    ChargeCarrier particle(TVector3(0, 0, 320.0 / 2));  // Position in micrometers

    // Set up the ChargeCarrierTransport with the electric field
    ChargeCarrierTransport mover;
    mover.setElectricField(eField);

    // Simulate the movement of the particle over multiple steps
    for (int step = 0; step < 50; ++step) {
        mover.move(particle);
        TVector3 newPosition = particle.getPosition();
        std::cout << "New position after step " << step << ": ("
                  << newPosition.X() << " µm, " << newPosition.Y() << " µm, " << newPosition.Z() << " µm)" << std::endl;
    }

    // Get the particle path graph
    TGraph2D* pathGraph = mover.plotPath();
    pathGraph->SetLineColor(kOrange);
    pathGraph->SetLineWidth(2);

    // Create the TGeoManager to handle the geometry
    TGeoManager* geoManager = new TGeoManager("Detector", "Detector Geometry");

    // Create a 58x200x300 um^3 box representing the detector volume
    TGeoMaterial* matSi = new TGeoMaterial("Silicon", 28.0855, 14, 2.33);
    TGeoMedium* medSi = new TGeoMedium("MediumSi", 1, matSi);
    TGeoVolume* detectorVolume = geoManager->MakeBox("DetectorVolume", medSi, 58.0 / 2, 200.0 / 2, 320.0 / 2);
    detectorVolume->SetLineColor(kBlue);
    detectorVolume->SetLineWidth(1);
    detectorVolume->SetLineStyle(kDashed);

    // Create a translation matrix to shift the detector by 320/2 µm upstream in the z direction
    TGeoTranslation* translation = new TGeoTranslation(0, 0, 320.0 / 2);  // Shift by 320/2 µm in the z direction

    // Create a top-level volume larger than the detector volumes
    TGeoVolume* topVolume = geoManager->MakeBox("TopVolume", medSi, 900.0 / 2, 900.0 / 2, 900.0 / 2);
    geoManager->SetTopVolume(topVolume);

    // Place the detector volume with the translation applied
    topVolume->AddNode(detectorVolume, 1, translation);

    // Define a rectangular surface in the XY plane
    std::vector<TVector2> vertices = {
        TVector2(0, 0),
        TVector2(100, 0),
        TVector2(100, 50),
        TVector2(0, 50)
    };


    // Create an Electrode object with the Surface and a Z position of 100 micrometers
//  Electrode electrode(Surface(vertices), 100.0);
    Electrode electrode(Pixel(50.), 100.0);
    


    // Create a canvas to plot everything together
    TCanvas* c1 = new TCanvas("c1", "Combined Plot", 800, 600);

    // Create a dummy 3D histogram to draw axes with a smaller range
    TH3D* h3 = new TH3D("h3", ";X [#mum];Y [#mum];Z [#mum]", 
                        10, -150, 150, 10, -150, 150, 10, 0, 320);
    h3->SetLineColor(0);  // Make the histogram itself invisible
    h3->SetStats(0);      // Hide the statistics box
    h3->Draw();           // Draw only the axes

    // Draw the detector volume
    geoManager->CloseGeometry();
//  topVolume->Draw("SAME");  // Draw with OpenGL for interactive 3D visualization

    // Draw the particle path on the same canvas
    pathGraph->Draw("LINE SAME");

    electrode.drawFootprint("SAME");

    // Adjust the viewing range to better match both the graph and the volume
    TView *view = TView::CreateView(1);
    view->SetRange(-150, -150, 0, 150, 150, 320); // Adjust based on your expected ranges

    // Update and display the canvas
    c1->Update();
    c1->Draw();

    // Run the ROOT application to display the canvas
    app.Run();

    // Clean up dynamically allocated memory
    delete pathGraph;
    delete c1;
    delete translation;
    delete h3;

    return 0;
}

