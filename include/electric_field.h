#ifndef ELECTRICAL_FIELD_H
#define ELECTRICAL_FIELD_H

#include "vector_field.h"

/**
 * @brief A class representing an electric field, inheriting from VectorField.
 *
 * The ElectricField class allows for the definition and manipulation of an electric field
 * based on a user-defined function. It provides methods to get the field strength at a specific
 * position and to visualize the field component along a given direction.
 */
class ElectricField : public VectorField {
public:
    /**
     * @brief Default constructor for the ElectricField class. Zero field value everywhere.
     */
    ElectricField()
        : VectorField() {}

    /**
     * @brief Constructor that initializes the electric field with a given function.
     * 
     * @param func A function that takes a position (TVector3) and returns the field strength (TVector3).
     */
    ElectricField(std::function<TVector3(const TVector3&)> func)
        : VectorField(func) {}

    /**
     * @brief Constructor that initializes the electric field with a uniform field vector.
     * 
     * This constructor creates a uniform field that returns the same vector at any position in space.
     * 
     * @param uniformField The TVector3 vector that defines the uniform field strength.
     */
    ElectricField(const TVector3& uniformField)
        : VectorField(uniformField) {}

    /**
     * @brief Destructor for the ElectricField class.
     */
    ~ElectricField() {}
};

#endif // ELECTRICAL_FIELD_H

