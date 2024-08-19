#ifndef VECTOR_FIELD_H
#define VECTOR_FIELD_H

#include <TVector3.h>
#include <functional>
#include <TF1.h>
#include <TCanvas.h>
#include <string>

/**
 * @brief A generic class representing a vector field in a given space.
 * 
 * The VectorField class allows for the definition and manipulation of a vector field
 * based on a user-defined function. It provides methods to get the field strength at a specific
 * position and to visualize the field component along a given direction.
 */
class VectorField {
public:
    /**
     * @brief Default constructor for the VectorField class.
     */
    VectorField();

    /**
     * @brief Constructor that initializes the vector field with a given function.
     * 
     * @param func A function that takes a position (TVector3) and returns the field strength (TVector3).
     */
    VectorField(std::function<TVector3(const TVector3&)> func);

    /**
     * @brief Constructor that initializes the vector field with a uniform field vector.
     * 
     * This constructor creates a uniform field that returns the same vector at any position in space.
     * 
     * @param uniformField The TVector3 vector that defines the uniform field strength.
     */
    VectorField(const TVector3& uniformField);

    /**
     * @brief Destructor for the VectorField class.
     */
    virtual ~VectorField();

    /**
     * @brief Gets the field strength at a specific position.
     * 
     * This method evaluates the field function at the given position and returns the corresponding field strength.
     * 
     * @param position The position in space where the field strength is to be evaluated.
     * @return TVector3 The field strength at the given position.
     */
    virtual TVector3 getFieldStrength(const TVector3& position) const;

    /**
     * @brief Redefines the vector field with a new function.
     * 
     * This method allows the user to change the function that defines the vector field after the object has been created.
     * 
     * @param func A new function that defines the vector field.
     */
    virtual void defineField(std::function<TVector3(const TVector3&)> func);

    /**
     * @brief Draws the field component along a specified direction.
     * 
     * This method creates a visual representation of the field component projected onto a specified direction
     * and saves it as an image file.
     * 
     * @param projection The direction vector along which the field component is to be projected.
     * @param end The end point of the line segment along which the field is drawn.
     * @param start The start point of the line segment along which the field is drawn (default is the origin).
     * @param title The title of the plot (default is "Field projection;Position [um];Field strength [V/um]").
     * @param filename The name of the file to save the plot (default is "vector_field_component.png").
     * @return TF1* A pointer to the TF1 object representing the field component.
     */
    virtual TF1* drawFieldComponent(const TVector3& projection, const TVector3& end, const TVector3& start = TVector3(0, 0, 0),
                                    const std::string& title = "Field projection;Position [um];Field strength [V/um]",
                                    const std::string& filename = "vector_field_component.png") const;

protected:
    std::function<TVector3(const TVector3&)> fieldFunction; ///< The function defining the vector field.
};

#endif // VECTOR_FIELD_H

