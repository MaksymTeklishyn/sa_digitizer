#include "electrode.h"

Electrode::Electrode(std::function<bool(const TVector3&)> surfaceFunc, double voltage)
    : surfaceFunc(surfaceFunc), voltage(voltage) {}

void Electrode::setVoltage(double voltage) {
    this->voltage = voltage;
}

void Electrode::setSurfaceFunction(std::function<bool(const TVector3&)> surfaceFunc) {
    this->surfaceFunc = surfaceFunc;
}

void Electrode::setWeightingField(const ElectricalField& field) {
    this->weightingField = field;
}

double Electrode::getVoltage() const {
    return voltage;
}

std::function<bool(const TVector3&)> Electrode::getSurfaceFunction() const {
    return surfaceFunc;
}

const ElectricalField& Electrode::getWeightingField() const {
    return weightingField;
}

