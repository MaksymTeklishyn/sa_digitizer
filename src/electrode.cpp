#include "electrode.h"
#include <TPolyLine3D.h>

// Constructor
Electrode::Electrode(const Surface& surface, double voltage)
    : footprint(surface.getFootprint()), voltage(voltage) {
    // The footprint is initialized directly from the Surface's footprint
    // Voltage is stored in the member variable
}

// Set the voltage of the electrode
void Electrode::setVoltage(double voltage) {
    this->voltage = voltage;
}

// Set the surface function of the electrode
void Electrode::setSurfaceFunction(std::function<bool(const TVector3&)> surfaceFunc) {
    this->surfaceFunc = surfaceFunc;
}

// Set the weighting field associated with the electrode
void Electrode::setWeightingField(const ElectricField& field) {
    this->weightingField = field;
}

// Get the voltage of the electrode
double Electrode::getVoltage() const {
    return voltage;
}

// Get the surface function of the electrode
std::function<bool(const TVector3&)> Electrode::getSurfaceFunction() const {
    return surfaceFunc;
}

// Get the weighting field associated with the electrode
const ElectricField& Electrode::getWeightingField() const {
    return weightingField;
}

// Method to draw the footprint
void Electrode::drawFootprint(const char* option /* = "SAME" */) {
    footprint.Draw(option);
}




