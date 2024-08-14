#ifndef CHARGE_CARRIER_H
#define CHARGE_CARRIER_H

#include <TVector3.h>

/**
 * @brief Class representing a charge carrier (electron or hole) in a semiconductor.
 */
class ChargeCarrier {
public:
    /**
     * @brief Constructor to initialize a charge carrier at a given position.
     * 
     * @param position The initial position of the charge carrier.
     * @param charge The charge of the carrier (e.g., +1 for holes, -1 for electrons).
     */
    ChargeCarrier(const TVector3& position, int charge = -1);

    /**
     * @brief Gets the mobility of the charge carrier.
     * 
     * @return double The mobility of the charge carrier in µm^2/V/ns.
     */
    double getMobility() const;

    /**
     * @brief Gets the charge of the carrier.
     * 
     * @return int The charge of the carrier (+1 for hole, -1 for electron).
     */
    int getCharge() const;

    /**
     * @brief Gets the position of the charge carrier.
     * 
     * @return TVector3 The current position of the charge carrier.
     */
    TVector3 getPosition() const;

    /**
     * @brief Sets the position of the charge carrier.
     * 
     * @param newPosition The new position of the charge carrier.
     */
    void setPosition(const TVector3& newPosition);

private:
    TVector3 position; ///< Current position of the charge carrier
    int charge;        ///< Charge of the carrier (+1 for hole, -1 for electron)
    double mobility;   ///< Mobility of the charge carrier in µm^2/V/ns
};

#endif // CHARGE_CARRIER_H

