#ifndef SURFACE_H
#define SURFACE_H

#include <vector>
#include <TVector2.h>
#include <TPolyLine3D.h>

class Surface {
public:
    // Constructor that takes a list of vertices
    Surface(const std::vector<TVector2>& vertices);

    // Method to get the vertices of the surface
    const std::vector<TVector2>& getVertices() const;

    // Method to get the footprint of the surface as a TPolyLine3D object
    TPolyLine3D getFootprint() const;

private:
    std::vector<TVector2> vertices;  // Vertices defining the surface in the XY plane
};

#endif // SURFACE_H























