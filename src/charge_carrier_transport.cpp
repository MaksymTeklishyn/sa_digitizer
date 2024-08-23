#include "charge_carrier_transport.h"
#include <iostream>
#include <TCanvas.h>  



void ChargeCarrierTransport::setElectricField(const ElectricField& field) {
    eField = &field;
}

void ChargeCarrierTransport::setMagneticField(const MagneticField& field) {
    mField = &field;
}

TVector3 ChargeCarrierTransport::move(ChargeCarrier &particle) {
    // Get the current position of the particle
    TVector3 currentPosition = particle.getPosition();

    // Initialize the full step vector to zero
    TVector3 fullStep(0, 0, 0);

    // Add the diffusion step to the full step
    fullStep += diffusionStep(particle);

    // Check if the electric field is set
    if (!eField) {
        std::cerr << "Error: Electrical field not set in ChargeCarrierTransport." << std::endl;
        return fullStep;
    }

    // Get the electric field at the current position
    TVector3 eFieldStrength = eField->getFieldStrength(currentPosition);

    // Calculate the drift step due to the electric field
    TVector3 driftVelocity = driftStep(particle, eFieldStrength);

    // Add the Lorentz force effect if the magnetic field is set
    if (mField) {
        TVector3 mFieldStrength = mField->getFieldStrength(currentPosition);
        driftVelocity += lorentzForceStep(particle, driftVelocity, mFieldStrength);
    }

    // Calculate the final step by adding the drift velocity
    fullStep += driftVelocity * TIME_STEP;

    // Update the particle's position with the full step
    particle.setPosition(currentPosition + fullStep);
    
    particlePath.push_back(particle.getPosition());
    // Return the full step vector
    return fullStep;
}

TGraph2D* ChargeCarrierTransport::plotPath() {
    if (particlePath.empty()) {
        std::cerr << "No data to plot!" << std::endl;
        return nullptr;
    }

    TGraph2D* graph = new TGraph2D(particlePath.size());

    for (size_t i = 0; i < particlePath.size(); ++i) {
        const TVector3 &pos = particlePath[i];
        graph->SetPoint(i, pos.X(), pos.Y(), pos.Z());
    }

    // Optionally, set the title and other properties here
    graph->SetTitle("Particle Path;X [#mum];Y [#mum];Z [#mum]");

    return graph;
}

TVector3 ChargeCarrierTransport::driftStep(const ChargeCarrier &particle, const TVector3 &fieldStrength) const {
    // Calculate drift due to electric field: v = μE
    return particle.getCharge() * particle.getMobility() * fieldStrength;
}

TVector3 ChargeCarrierTransport::lorentzForceStep(const ChargeCarrier &particle, const TVector3 &driftVelocity, const TVector3 &fieldStrength) const {
    // Calculate the change in velocity due to the magnetic field (Lorentz force): Δv = q(v × B) / m
    return particle.getCharge() * (driftVelocity.Cross(fieldStrength));
}

TVector3 ChargeCarrierTransport::diffusionStep(const ChargeCarrier &particle) {
    // Calculate diffusion based on a Gaussian distribution
    double sigma = sqrt(2 * diffusionCoeff * TIME_STEP);
    return TVector3(randomGenerator.Gaus(0, sigma), randomGenerator.Gaus(0, sigma), randomGenerator.Gaus(0, sigma));
}

