#include "strip_surface.h"
#include <cmath>

// Constructor
StripSurface::StripSurface(double width, double angle)
    : Surface({
        TVector2(0, 0),
        TVector2(0, 0),
        TVector2(0, 0),
        TVector2(0, 0)
    }),
    width(width), angle(angle)
{
    // No additional assignment needed, base class is already initialized
}

