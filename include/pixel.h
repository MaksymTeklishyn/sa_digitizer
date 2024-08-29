#ifndef PIXEL_H
#define PIXEL_H

#include "surface.h"

class Pixel : public Surface {
public:
    // Constructor with width and optional length
    // If length is 0, it will default to the width value
    Pixel(double width, double length = 0);

private:
    double width;
    double length;
};

#endif // PIXEL_H

