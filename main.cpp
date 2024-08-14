// main.cpp
#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TGraph.h>
#include <TGeoManager.h>
#include <TGeoVolume.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoMatrix.h>
#include <TRandom3.h>
#include "charge_carrier.h"
#include "electrical_field.h"
#include "charge_carrier_transport.h"
#include "constants.h"
#include "field_functions.h"

int main(int argc, char **argv) {
    // Initialize ROOT application to handle graphics
    TApplication app("ROOT Application", &argc, argv);

    // Create the ElectricalField object with the linearElectricField function
    ElectricalField eField([=](const TVector3& position) -> TVector3 {
        return diodElectricFieldZ(position, 320., 60., 150.);
    });
    // Draw the Z-component of the electric field
//  eField.drawFieldComponent(TVector3(0, 0, 1), TVector3(0, 0, 320)); 

    // Create the MagneticField object with a uniform field
    MagneticField mField(TVector3(0, 1, 0));

//  TVector3 initialPosition(0, 0, 320./2); // Position in micrometers
    ChargeCarrier particle(TVector3(0, 0, 320./2));

    ChargeCarrierTransport mover;
    mover.setElectricalField(eField);
//  mover.setMagneticField(mField);
    
    for (int step = 0; step < 100; ++step) {
        mover.move(particle); // Time step is now a global constant
        TVector3 newPosition = particle.getPosition();
        std::cout << "New position after step " << step << ": (" 
                  << newPosition.X() << " µm, " << newPosition.Y() << " µm, " << newPosition.Z() << " µm)" << std::endl;
    }
    // Get the particle path graph
    TGraph2D* pathGraph = mover.plotPath();

    // Create the TGeoManager to handle the geometry
    TGeoManager* geoManager = new TGeoManager("Detector", "Detector Geometry");

    // Create a 58x200x300 um^3 box representing the detector volume
    TGeoMaterial* matSi = new TGeoMaterial("Silicon", 28.0855, 14, 2.33);
    TGeoMedium* medSi = new TGeoMedium("MediumSi", 1, matSi);
    TGeoVolume* detectorVolume = geoManager->MakeBox("DetectorVolume", medSi, 58.0 / 2, 200.0 / 2, 300.0 / 2);
    detectorVolume->SetLineColor(kBlue);

    // Create a translation matrix to shift the detector by 320/2 µm upstream in the z direction
    TGeoTranslation* translation = new TGeoTranslation(0, 0, -320.0 / 2);  // Shift by -320/2 µm in the z direction

    // Place the detector volume with the translation applied
    TGeoVolume* topVolume = geoManager->MakeBox("TopVolume", medSi, 58.0 / 2, 200.0 / 2, 300.0 / 2);
    geoManager->SetTopVolume(topVolume);
    topVolume->AddNode(detectorVolume, 1, translation);

    // Draw both graphs on the same canvas
    TCanvas* c1 = new TCanvas("c1", "Combined Plot", 800, 600);

    // Draw the detector volume
    geoManager->CloseGeometry();
    detectorVolume->Draw("gl");  // Draw with OpenGL for interactive 3D visualization
 
    pathGraph->Draw("LINE SAME");
    c1->Update();
    c1->Draw();

    // Run the ROOT application to display the canvas
    app.Run();

    // Clean up
    delete pathGraph;
    delete c1;

    return 0;

}

