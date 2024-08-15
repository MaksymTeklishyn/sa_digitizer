#include "strip_electrode.h"

/**
 * @brief Constructor for the StripElectrode class.
 * @param stripWidth The width of the strip.
 * @param stereoAngle The stereo angle of the strip in degrees.
 * @param voltage The voltage applied to the electrode. Defaults to 0.0.
 */
StripElectrode::StripElectrode(double stripWidth, double stereoAngle, double voltage)
    : Electrode(nullptr, voltage) // Initialize base class with nullptr for surface, as we'll set it manually
{
    // Create a TGeoPolygon for the strip
    TGeoPolygon* stripSurface = new TGeoPolygon(4); // 4 sides for a rectangle
    double length = 10 * stripWidth;
    double xCoord[4] = {stripWidth/2, -stripWidth/2, -stripWidth/2, stripWidth/2};
    double yCoord[4] = {length/2, length/2, -length/2, -length/2};
    stripSurface->SetXY(xCoord, yCoord);

    // Now set the surface in the base class
    setSurface(stripSurface);
}

