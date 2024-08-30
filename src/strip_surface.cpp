#include "strip_surface.h"
#include <cmath>
#include <iostream>

// Constructor
StripSurface::StripSurface(double width, double angle)
    : width(width), angle(angle), Surface(buildStripVertices(width, angle))
{
    // Ensure the width and angle are correctly passed and assigned
    std::cout << "Constructed StripSurface with width: " << width << ", angle: " << angle << std::endl;
}

// Private function to build the strip vertices
std::vector<TVector2> StripSurface::buildStripVertices(double stripWidth, double stripAngle) const {
    double halfWidth =  stripWidth / 2.0;
    double halfLength = 1e6;  // Very long length to simulate an infinitely long strip

    // Vertices of the rectangle before rotation
    std::vector<TVector2> vertices = {
        TVector2(halfWidth, halfLength),
        TVector2(-halfWidth, halfLength),
        TVector2(-halfWidth, -halfLength),
        TVector2(halfWidth, -halfLength)
    };
    // Angle in radians
    double angleRad = stripAngle * M_PI / 180.0;

    // Rotate the vertices by the specified angle
    for (auto& vertex : vertices) {
        double x = vertex.X() * std::cos(angleRad) - vertex.Y() * std::sin(angleRad);
        double y = vertex.X() * std::sin(angleRad) + vertex.Y() * std::cos(angleRad);
        vertex.Set(x, y);
    }

    return vertices;
}

