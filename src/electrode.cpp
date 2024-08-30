#include "electrode.h"
#include <TPolyLine3D.h>
#include <TCanvas.h>
#include <TROOT.h>

// Constructor
Electrode::Electrode(const Surface& surface, const TVector3& position, double voltage)
    : position(position), voltage(voltage), footprint(surface.getFootprint()) {
    // Place the electrode at the given position
    place(position);
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

// Moves the electrode's footprint to a new position in 3D space
void Electrode::place(const TVector3& newPosition) {
    position = newPosition;
    updateFootprint();
}

// Updates the footprint to the current position
void Electrode::updateFootprint() {
    Float_t* points = footprint.GetP();
    int nPoints = footprint.GetN();

    for (int i = 0; i < nPoints; ++i) {
        int index = i * 3;  // Each point has 3 coordinates (x, y, z)
        points[index]     = points[index] + position.X();  // Update X
        points[index + 1] = points[index + 1] + position.Y();  // Update Y
        points[index + 2] = position.Z();  // Update Z
    }
}

// Visualize the electrode's surface using TPolyLine3D
void Electrode::drawFootprint(const char* option /* = "SAME" */) {
    footprint.Draw(option);
}

