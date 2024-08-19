#include "electrode.h"
#include <cmath>

Electrode::Electrode(std::function<bool(const TVector3&)> surfaceFunc, double voltage)
    : surfaceFunc(surfaceFunc), voltage(voltage) {}

std::function<bool(const TVector3&)> Electrode::flatStrip(double width, double length, double angle) {
    if (length == 0) {
        length = 10 * width;
    }

    // Convert angle to radians
    double radAngle = angle * M_PI / 180.0;

    // Define the flat strip function
    return [=](const TVector3& point) -> bool {
        // Translate the point back to origin and rotate by -angle around z-axis
        double xRot = point.X() * cos(radAngle) + point.Y() * sin(radAngle);
        double yRot = -point.X() * sin(radAngle) + point.Y() * cos(radAngle);

        // Check if the rotated point is within the rectangle bounds
        return std::abs(xRot) <= width / 2.0 && std::abs(yRot) <= length / 2.0 && std::abs(point.Z()) < 1e-6;
    };
}

TF3* Electrode::createSurfaceFunction3D(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax) const {
    auto surfaceLambda = [this](double* xyz, double* params) -> double {
        TVector3 point(xyz[0], xyz[1], xyz[2]);
        return surfaceFunc(point) ? 1.0 : 0.0;
    };

    TF3* surfaceFunction = new TF3("surfaceFunction", surfaceLambda, xMin, xMax, yMin, yMax, zMin, zMax, 0, "surfaceFunction");
    surfaceFunction->SetTitle("Electrode Surface;X [um];Y [um];Z [um]");
//  TF3* surfaceFunction = new TF3("surfaceFunction", "x+y+z", xMin, xMax, yMin, yMax, zMin, zMax, 0, "surfaceFunction");
    return surfaceFunction;
}

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

