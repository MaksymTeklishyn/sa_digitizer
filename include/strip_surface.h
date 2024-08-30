#ifndef STRIP_SURFACE_H
#define STRIP_SURFACE_H

#include "surface.h"

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
     *
     * This constructor initializes the StripSurface with the given width and angle.
     * The surface is centered around the origin (0, 0) in the XY plane.
     *
     * @param width The width of the StripSurface, defining the size across the central axis.
     * @param angle The orientation of the StripSurface, in degrees, counterclockwise from the X-axis.
     *              Defaults to 0 degrees if not specified.
     */
    StripSurface(double width, double angle = 0);

private:
    double width;  ///< The width of the StripSurface, defining the size across the central axis.
    double angle;  ///< The orientation of the StripSurface, in degrees counterclockwise from the X-axis.
};

#endif // STRIP_SURFACE_H

