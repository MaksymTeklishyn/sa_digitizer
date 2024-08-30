#include "pixel_surface.h"

// Constructor
PixelSurface::PixelSurface(double width, double length)
    : Surface({
        TVector2(-width / 2, - (length == 0 ? width : length) / 2),  // Bottom-left corner
        TVector2(width / 2, - (length == 0 ? width : length) / 2),   // Bottom-right corner
        TVector2(width / 2, (length == 0 ? width : length) / 2),     // Top-right corner
        TVector2(-width / 2, (length == 0 ? width : length) / 2)     // Top-left corner
    }), width(width), length(length == 0 ? width : length) {
    // The Surface constructor is called with vertices for a rectangle or square centered around the origin
}

