#ifndef SURFACE_H
#define SURFACE_H

#include <vector>
#include <TVector2.h>
#include <TPolyLine3D.h>

/**
 * @class Surface
 * @brief Represents a 2D surface in the XY plane defined by a set of vertices.
 *
 * The Surface class provides a way to represent and work with 2D surfaces.
 * It stores a list of vertices that define the shape of the surface and can generate a
 * 3D footprint of the surface in the XY plane (with Z = 0).
 */
class Surface {
public:
    /**
     * @brief Constructs a Surface object from a list of vertices.
     *
     * The constructor initializes the Surface with the provided vertices,
     * which define the shape of the surface in the XY plane.
     *
     * @param vertices A vector of TVector2 objects representing the vertices of the surface.
     *                 The vertices should be provided in a counterclockwise order to define the surface correctly.
     */
    Surface(const std::vector<TVector2>& vertices);

    /**
     * @brief Returns the vertices that define the surface.
     *
     * This method provides access to the list of vertices that define the surface.
     *
     * @return A constant reference to a vector of TVector2 objects representing the vertices of the surface.
     */
    const std::vector<TVector2>& getVertices() const;

    /**
     * @brief Generates a 3D footprint of the surface.
     *
     * This method creates a TPolyLine3D object that represents the footprint of the surface in 3D space.
     * The footprint is defined in the XY plane, with the Z coordinate set to 0 for all vertices.
     *
     * @return A TPolyLine3D object representing the 3D footprint of the surface.
     */
    TPolyLine3D getFootprint() const;

private:
    std::vector<TVector2> vertices;  ///< Vertices defining the surface in the XY plane.
    TPolyLine3D footprint;
};

#endif // SURFACE_H

