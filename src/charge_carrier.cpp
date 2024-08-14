#include "charge_carrier.h"
#include "constants.h" // Include the constants header for mobility values

ChargeCarrier::ChargeCarrier(const TVector3& pos, int ch)
    : position(pos), charge(ch) {
    // Assign mobility based on the charge
    mobility = (charge > 0) ? HOLE_MOBILITY : ELECTRON_MOBILITY;
}

double ChargeCarrier::getMobility() const {
    return mobility;
}

int ChargeCarrier::getCharge() const {
    return charge;
}

TVector3 ChargeCarrier::getPosition() const {
    return position;
}

void ChargeCarrier::setPosition(const TVector3& newPosition) {
    position = newPosition;
}

