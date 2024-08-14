#include "charge_carrier_transport.h"
#include <iostream>

void ChargeCarrierTransport::setElectricalField(const ElectricalField& field) {
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

    // Return the full step vector
    return fullStep;
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

