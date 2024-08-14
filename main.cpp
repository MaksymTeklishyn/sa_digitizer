// main.cpp
#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TGraph.h>
#include <TF1.h>
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

    std::cout << "Particle mobility: " << particle.getMobility() << " µ^2Vns" << std::endl;
    std::cout << "Particle charge: " << particle.getCharge() << " e" << std::endl;
    TVector3 pos = particle.getPosition();
    std::cout << "Particle position: (" << pos.X() << " µm, " << pos.Y() << " µm, " << pos.Z() << " µm)" << std::endl;

    // Using functional dependence for electric field
    ChargeCarrierTransport mover;
    mover.setElectricalField(eField);
//  mover.setMagneticField(mField);
    
    for (int step = 0; step < 10; ++step) {
        mover.move(particle); // Time step is now a global constant
        TVector3 newPosition = particle.getPosition();
        std::cout << "New position after step " << step << ": (" 
                  << newPosition.X() << " µm, " << newPosition.Y() << " µm, " << newPosition.Z() << " µm)" << std::endl;
    }

    mover.plotPath();

    app.Run();
    return 0;
}

