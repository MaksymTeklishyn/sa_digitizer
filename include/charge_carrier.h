// include/charge_carrier.h
#ifndef CHARGE_CARRIER_H
#define CHARGE_CARRIER_H

#include <TVector3.h>

class ChargeCarrier {
public:
    ChargeCarrier(TVector3 position = TVector3(0, 0, 0), double mobility = 135, int charge = -1); 
    ~ChargeCarrier();

    void setMobility(double mobility);
    double getMobility() const;

    void setCharge(int charge);
    double getCharge() const;

    void setPosition(const TVector3& position);
    TVector3 getPosition() const;

private:
    double mobility; // um^2/Vns 
    int charge; // e
    TVector3 position; // um
};

#endif // CHARGE_CARRIER_H

