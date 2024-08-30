#ifndef CHARGE_CARRIER_TRANSPORT_H
#define CHARGE_CARRIER_TRANSPORT_H

#include "charge_carrier.h"
#include "electric_field.h"
#include "magnetic_field.h"
#include "constants.h"
#include <TRandom3.h>
#include <TGraph2D.h>

/**
 * @brief Class to handle the transport of charge carriers in electric and magnetic fields, considering drift, diffusion, and the Lorentz force.
 */
class ChargeCarrierTransport {
public:
    /**
     * @brief Default constructor for ChargeCarrierTransport.
     */
    ChargeCarrierTransport() = default;

    /**
     * @brief Sets the electric field to be used for calculating drift.
     * 
     * @param field The electric field to be set.
     */
    void setElectricField(const ElectricField& field);

    /**
     * @brief Sets the magnetic field to be used for calculating the Lorentz force.
     * 
     * @param field The magnetic field to be set.
     */
    void setMagneticField(const MagneticField& field);

    /**
     * @brief Moves the charge carrier by one time step considering drift, diffusion, and the Lorentz force.
     * 
     * This method calculates the total displacement of the charge carrier due to diffusion,
     * drift in the electric field, and the effect of the magnetic field. The particle's position
     * is then updated based on this displacement.
     * 
     * @param particle The charge carrier to be moved.
     * @return TVector3 The total displacement vector (in μm) for this time step.
     */
    TVector3 move(ChargeCarrier &particle);
	
    TGraph2D* plotPath();

    /**
     * @brief Sets the diffusion coefficient used for calculating diffusion effects.
     * 
     * @param coeff The diffusion coefficient to be set.
     */
    void setDiffusionCoeff(double coeff);

    /**
     * @brief Gets the current diffusion coefficient.
     * 
     * @return double The current diffusion coefficient.
     */
    double getDiffusionCoeff() const;

private:
    const ElectricField* eField = nullptr;    ///< Pointer to the electric field (initialized to nullptr)
    const MagneticField* mField = nullptr;      ///< Pointer to the magnetic field (initialized to nullptr)
    double diffusionCoeff = 100.0;               ///< Default diffusion coefficient
    TRandom3 randomGenerator;                   ///< Random generator for diffusion
    std::vector<TVector3> particlePath;  	///< Vector to store the particle's path

    /**
     * @brief Calculates the drift step of the charge carrier due to the electric field.
     * 
     * @param particle The charge carrier undergoing drift.
     * @param fieldStrength The strength of the electric field at the particle's position.
     * @return TVector3 The drift displacement vector (in μm).
     */
    TVector3 driftStep(const ChargeCarrier &particle, const TVector3 &fieldStrength) const;

    /**
     * @brief Applies the effect of the magnetic field on the particle's motion (Lorentz force).
     * 
     * This method calculates the velocity change of the particle due to the magnetic field.
     * 
     * @param particle The charge carrier.
     * @param driftVelocity The current drift velocity of the particle due to the electric field.
     * @param fieldStrength The strength of the magnetic field at the particle's position.
     * @return TVector3 The change in velocity (in μm/ns) due to the magnetic field.
     */
    TVector3 lorentzForceStep(const ChargeCarrier &particle, const TVector3 &driftVelocity, const TVector3 &fieldStrength) const;

    /**
     * @brief Applies a diffusion step to the particle's motion.
     * 
     * @param particle The charge carrier undergoing diffusion.
     * @return TVector3 The diffusion displacement vector (in μm).
     */
    TVector3 diffusionStep(const ChargeCarrier &particle);
};

#endif // CHARGE_CARRIER_TRANSPORT_H

