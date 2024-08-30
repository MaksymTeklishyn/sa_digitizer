#ifndef STRIP_SURFACE_H
#define STRIP_SURFACE_H

#include "surface.h"
#include <vector>
#include <TVector2.h>

/**
 * @class StripSurface
 * @brief Represents an infinitely long flat strip with a defined width and angle.
 *
 * The StripSurface class is a specific type of Surface that is defined by its width and orientation angle.
 * It is considered infinitely long along its central axis and has a finite width across that axis.
 */
class StripSurface : public Surface {
public:
    /**
     * @brief Constructs a StripSurface object with the specified width and angle.
     * @param width The width of the StripSurface.
     * @param angle The orientation angle of the StripSurface in degrees.
     */
    StripSurface(double width, double angle = 0);

private:
    double width;  ///< The width of the StripSurface
    double angle;  ///< The orientation of the StripSurface in degrees

    /**
     * @brief Generates the vertices of a very long rectangle (strip) with the specified width and angle.
     * @return A vector of TVector2 representing the vertices of the rotated strip.
     */
    std::vector<TVector2> buildStripVertices(double stripWidth, double stripAngle) const;
};

#endif // STRIP_SURFACE_H

