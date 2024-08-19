#ifndef ELECTRODE_H
#define ELECTRODE_H

#include <functional>
#include <TVector3.h>
#include <TF3.h>
#include "electrical_field.h"

/**
 * @class Electrode
 * @brief Represents an electrode in a detector, with a surface defined by an arbitrary function in 3D space.
 */
class Electrode {
public:
    /**
     * @brief Constructor for the Electrode class.
     * @param surfaceFunc A function that defines the surface in 3D space.
     * @param voltage The voltage applied to the electrode. Defaults to 0.0.
     */
    Electrode(std::function<bool(const TVector3&)> surfaceFunc, double voltage = 0.0);

    /**
     * @brief Static function to define a flat strip in the XY-plane, rotated around the z-axis.
     * @param width The width of the strip.
     * @param length The length of the strip. Defaults to 10 times the width.
     * @param angle The rotation angle around the z-axis in degrees.
     * @return A function that checks if a point is within the defined rectangle.
     */
    static std::function<bool(const TVector3&)> flatStrip(double width, double length = 0, double angle = 0);

    // Method to create and return a TF3 visualization of the electrode surface
    TF3* createSurfaceFunction3D(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax) const;

    /**
     * @brief Sets the voltage of the electrode.
     * @param voltage The voltage to be set.
     */
    void setVoltage(double voltage);

    /**
     * @brief Sets the surface function of the electrode.
     * @param surfaceFunc A function that defines the surface in 3D space.
     */
    void setSurfaceFunction(std::function<bool(const TVector3&)> surfaceFunc);

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
     * @brief Gets the surface function of the electrode.
     * @return The function defining the electrode surface.
     */
    std::function<bool(const TVector3&)> getSurfaceFunction() const;

    /**
     * @brief Gets the weighting field associated with the electrode.
     * @return A reference to the ElectricalField object representing the weighting field.
     */
    const ElectricalField& getWeightingField() const;

private:
    double voltage;  ///< Voltage of the electrode
    std::function<bool(const TVector3&)> surfaceFunc;  ///< Function defining the electrode surface
    ElectricalField weightingField;  ///< Weighting field associated with the electrode
};

#endif // ELECTRODE_H

