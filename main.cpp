#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH3D.h>
#include <TRandom3.h>
#include <TView.h>
#include <TView3D.h>
#include "charge_carrier.h"
#include "electric_field.h"
#include "charge_carrier_transport.h"
#include "constants.h"
#include "field_functions.h"
#include "electrode.h"
#include "pixel_surface.h"
#include "strip_surface.h"

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


    // Create an Electrode object with the Surface and a Z position of 100 micrometers
    Electrode electrode(PixelSurface(50., 150.), TVector3(100, 0, 100.));
    Electrode electrodeStrip(StripSurface(58., 7.5), TVector3(50, 0, 0));
    


    // Create a canvas to plot everything together
    TCanvas* c1 = new TCanvas("c1", "Combined Plot", 1200, 800);


    // Define the viewing range
    Double_t rmin[3] = {-300, -300, 0};
    Double_t rmax[3] = {300, 300, 320};

    // Set up the 3D view with OpenGL
    TView3D *view = new TView3D(1, rmin, rmax);


    // Create a dummy 3D histogram to draw axes with a smaller range
    TH3D* h3 = new TH3D("h3", ";X [#mum];Y [#mum];Z [#mum]",
                        1, rmin[0], rmax[0],   // X-axis range
                        1, rmin[1], rmax[1],   // Y-axis range
                        1, rmin[2], rmax[2]);  // Z-axis range
    h3->SetLineColor(0);  // Make the histogram itself invisible
    h3->SetStats(0);      // Hide the statistics box
    h3->Draw();           // Draw only the axes

    // Draw the particle path on the same canvas
    pathGraph->Draw("LINE SAME");

    electrode.drawFootprint("SAME");
    electrodeStrip.drawFootprint("SAME");

    // Adjust the viewing range to better match both the graph and the volume
//  TView *view = TView::CreateView(1);
//  view->SetRange(-150, -150, 0, 150, 150, 320); // Adjust based on your expected ranges


    // Update and display the canvas
    c1->Update();
    c1->Draw();

    // Run the ROOT application to display the canvas
    app.Run();

    // Clean up dynamically allocated memory
    delete pathGraph;
    delete c1;
    delete h3;

    return 0;
}

