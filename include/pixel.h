#ifndef PIXEL_H
#define PIXEL_H

#include "surface.h"

/**
 * @class Pixel
 * @brief Represents a rectangular or square surface centered around the origin in the XY plane.
 *
 * The Pixel class is a specific type of Surface that is defined by its width and length.
 * It is centered around the origin (0, 0) in the XY plane. If the length is not specified,
 * the Pixel is considered square, with the length equal to the width.
 */
class Pixel : public Surface {
public:
    /**
     * @brief Constructs a Pixel object with the specified width and length.
     *
     * This constructor initializes the Pixel with the given width and length.
     * The surface is centered around the origin (0, 0) in the XY plane. If the length is 0,
     * it will default to the value of the width, making the Pixel a square.
     *
     * @param width The width of the Pixel, corresponding to the horizontal dimension.
     * @param length The length of the Pixel, corresponding to the vertical dimension.
     *               Defaults to 0, in which case the length will be set equal to the width.
     */
    Pixel(double width, double length = 0);

private:
    double width;  ///< The width of the Pixel, defining the size in the X dimension.
    double length; ///< The length of the Pixel, defining the size in the Y dimension. Defaults to the width if not specified.
};

#endif // PIXEL_H

