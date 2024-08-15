#ifndef STRIP_ELECTRODE_H
#define STRIP_ELECTRODE_H

#include "electrode.h"
#include <TGeoPolygon.h>

/**
 * @class StripElectrode
 * @brief Represents a strip electrode, which is a specialized type of Electrode.
 */
class StripElectrode : public Electrode {
public:
    /**
     * @brief Constructor for the StripElectrode class.
     * @param stripWidth The width of the strip.
     * @param stereoAngle The stereo angle of the strip in degrees.
     * @param voltage The voltage applied to the electrode. Defaults to 0.0.
     */
    StripElectrode(double stripWidth, double stereoAngle, double voltage = 0.0);
};

#endif // STRIP_ELECTRODE_H

