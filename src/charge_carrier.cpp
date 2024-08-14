// src/charge_carrier.cpp
#include "charge_carrier.h"

ChargeCarrier::ChargeCarrier(TVector3 pos, double m, int c) 
    : position(pos), mobility(m), charge(c) {}

ChargeCarrier::~ChargeCarrier() {}

void ChargeCarrier::setMobility(double m) {
    mobility = m;
}

double ChargeCarrier::getMobility() const {
    return mobility;
}

void ChargeCarrier::setCharge(int c) {
    charge = c;
}

double ChargeCarrier::getCharge() const {
    return charge;
}

void ChargeCarrier::setPosition(const TVector3& pos) {
    position = pos;
}

TVector3 ChargeCarrier::getPosition() const {
    return position;
}


