#include "surface.h"
#include "iostream"
#include <TPolyLine3D.h>

// Constructor
Surface::Surface(const std::vector<TVector2>& vertices)
    : vertices(vertices) {}

// Get the vertices of the surface
const std::vector<TVector2>& Surface::getVertices() const {
    return vertices;
}

// Get the footprint of the surface as a TPolyLine3D object
TPolyLine3D Surface::getFootprint() const {
    TPolyLine3D polyline(vertices.size());
    for (size_t i = 0; i < vertices.size(); i++) {
        polyline.SetPoint(i, vertices[i].X(), vertices[i].Y(), 0.0); // Assuming Z = 0
    }
    polyline.SetPoint(vertices.size(), vertices[0].X(), vertices[0].Y(), 0.0); // Close the loop
    polyline.SetLineColor(kGreen);
    polyline.SetLineWidth(2);
    return polyline;
}

// Check whether a point is inside the polygon
bool Surface::isInside(const TVector2& point) const {
    int n = vertices.size();
    bool inside = false;
/*
    // Debug output
    std::cout << "Checking point: (" << point.X() << ", " << point.Y() << ")" << std::endl;
    std::cout << "Number of vertices: " << n << std::endl;

    for (int i = 0, j = n - 1; i < n; j = i++) {
        const TVector2& vi = vertices[i];
        const TVector2& vj = vertices[j];

        // Debug output for each vertex
        std::cout << "Vertex " << i << ": (" << vi.X() << ", " << vi.Y() << ")" << std::endl;
        std::cout << "Vertex " << j << ": (" << vj.X() << ", " << vj.Y() << ")" << std::endl;

        if (((vi.Y() > point.Y()) != (vj.Y() > point.Y())) &&
            (point.X() < (vj.X() - vi.X()) * (point.Y() - vi.Y()) / (vj.Y() - vi.Y()) + vi.X())) {
            inside = !inside;
        }
    }
*/
    return inside;
}


// Get the surface function as a std::function
std::function<bool(const TVector2&)> Surface::getSurfaceFunction() const {
    return [this](const TVector2& point) -> bool {
        return isInside(point);
    };
}
