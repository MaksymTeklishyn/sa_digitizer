#ifndef ELECTRODE_H
#define ELECTRODE_H

#include <TGeoPolygon.h>
#include "electrical_field.h"

/**
 * @class Electrode
 * @brief Represents an electrode in a detector, including its voltage, surface geometry, and associated weighting field.
 */
class Electrode {
public:
    /**
     * @brief Constructor for the Electrode class.
     * @param surface Pointer to a TGeoPolygon object representing the surface of the electrode.
     * @param voltage The voltage applied to the electrode. Defaults to 0.0.
     */
    Electrode(TGeoPolygon* surface, double voltage = 0.0);

    /**
     * @brief Sets the voltage of the electrode.
     * @param voltage The voltage to be set.
     */
    void setVoltage(double voltage);

    /**
     * @brief Sets the surface geometry of the electrode.
     * @param surface Pointer to a TGeoPolygon object representing the surface of the electrode.
     */
    void setSurface(TGeoPolygon* surface);

    /**
     * @brief Sets the weighting field associated with the electrode.
     * @param field A reference to an ElectricalField object representing the weighting field.
     */
    void setWeightingField(const ElectricalField& field);

    /**
     * @brief Gets the voltage of the electrode.
     * @return The voltage of the electrode.
     */
    double getVoltage() const;

    /**
     * @brief Gets the surface geometry of the electrode.
     * @return A pointer to the TGeoPolygon object representing the surface of the electrode.
     */
    const TGeoPolygon* getSurface() const;

    /**
     * @brief Gets the weighting field associated with the electrode.
     * @return A reference to the ElectricalField object representing the weighting field.
     */
    const ElectricalField& getWeightingField() const;

private:
    double voltage;                  ///< Voltage applied to the electrode
    TGeoPolygon* surface;            ///< Pointer to the surface geometry of the electrode
    ElectricalField weightingField;  ///< Weighting field associated with the electrode
};

#endif // ELECTRODE_H

