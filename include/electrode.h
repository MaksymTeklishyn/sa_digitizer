#ifndef ELECTRODE_H
#define ELECTRODE_H

#include <functional>
#include <TVector3.h>
#include <TF3.h>
#include "electric_field.h"
#include "surface.h"
#include <TPolyLine3D.h>

/**
 * @class Electrode
 * @brief Represents an electrode in a detector, with a surface defined by an arbitrary function in 3D space.
 */
class Electrode {
public:
    /**
     * @brief Constructs an Electrode with the given surface, position, and voltage.
     * @param surface A reference to a Surface object defining the electrode's geometry.
     * @param position The position of the electrode in 3D space (default is (0,0,0)).
     * @param voltage The voltage of the electrode (default is 0.0V).
     */
    Electrode(const Surface& surface, const TVector3& position = TVector3(0, 0, 0), double voltage = 0.0);

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
     * @param field A reference to an ElectricField object representing the weighting field.
     */
    void setWeightingField(const ElectricField& field);

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
     * @return A reference to the ElectricField object representing the weighting field.
     */
    const ElectricField& getWeightingField() const;

    /**
     * @brief Moves the electrode's footprint to a new position in 3D space.
     * @param newPosition The new position for the electrode.
     */
    void place(const TVector3& newPosition);

    /**
     * @brief Visualizes the electrode's surface.
     * @param option The drawing option for ROOT (default is "SAME").
     */
    void drawFootprint(const char* option = "SAME");

private:
    TPolyLine3D footprint;  ///< Footprint of the electrode in 3D space
    TVector3 position;  ///< Position of the electrode in 3D space
    double voltage;  ///< Voltage of the electrode
    std::function<bool(const TVector3&)> surfaceFunc;  ///< Function defining the electrode surface
    ElectricField weightingField;  ///< Weighting field associated with the electrode

    /**
     * @brief Updates the footprint to the current position.
     */
    void updateFootprint();
};

#endif // ELECTRODE_H

