#include "electrode.h"

// Constructor implementation
Electrode::Electrode(TGeoPolygon* surface, double voltage)
    : surface(surface), voltage(voltage), weightingField(ElectricalField(TVector3(0, 0, 0))) {}

// Setter methods
void Electrode::setVoltage(double voltage) {
    this->voltage = voltage;
}

void Electrode::setSurface(TGeoPolygon* surface) {
    this->surface = surface;
}

void Electrode::setWeightingField(const ElectricalField& field) {
    this->weightingField = field;
}

// Getter methods
double Electrode::getVoltage() const {
    return voltage;
}

const TGeoPolygon* Electrode::getSurface() const {
    return surface;
}

const ElectricalField& Electrode::getWeightingField() const {
    return weightingField;
}

