#include "surface.h"
#include <TCanvas.h>
#include <TPolyLine3D.h>
#include <TROOT.h>

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
        // Assuming Z coordinate is 0 since vertices are 2D
        polyline.SetPoint(i, vertices[i].X(), vertices[i].Y(), 0);
    }
    polyline.SetPoint(vertices.size(), vertices[0].X(), vertices[0].Y(), 0);
    polyline.SetLineColor(kGreen);
    polyline.SetLineWidth(2);
    return polyline;
}

