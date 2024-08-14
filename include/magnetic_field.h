#ifndef MAGNETIC_FIELD_H
#define MAGNETIC_FIELD_H

#include "vector_field.h"

/**
 * @brief A class representing a magnetic field, inheriting from VectorField.
 * 
 * The MagneticField class allows for the definition and manipulation of a magnetic field
 * based on a user-defined function. It provides methods to get the field strength at a specific
 * position and to visualize the field component along a given direction.
 */
class MagneticField : public VectorField {
public:
    /**
     * @brief Constructor that initializes the magnetic field with a given function.
     * 
     * @param func A function that takes a position (TVector3) and returns the field strength (TVector3).
     */
    MagneticField(std::function<TVector3(const TVector3&)> func)
        : VectorField(func) {}

    /**
     * @brief Constructor that initializes the magnetic field with a uniform field vector.
     * 
     * This constructor creates a uniform field that returns the same vector at any position in space.
     * 
     * @param uniformField The TVector3 vector that defines the uniform field strength.
     */
    MagneticField(const TVector3& uniformField)
        : VectorField(uniformField) {}

    /**
     * @brief Destructor for the MagneticField class.
     */
    ~MagneticField() {}
};

#endif // MAGNETIC_FIELD_H





























