// field_functions.cpp

#include "field_functions.h"

// Function definition
TVector3 diodElectricFieldZ(const TVector3& position, double thickness, double depletionVoltage, double biasVoltage) {
    auto fieldFunction = [&](double z) -> double {
        // Calculate the electric field at position z
        double e_at_z = biasVoltage + depletionVoltage * (1 - 2 * z / thickness);
        e_at_z /= thickness;
        
        // Ensure the field is always positive
        if (e_at_z < 0) e_at_z = 0;
        
        // Ensure the field is zero outside the detector
        if (z < 0 || z > thickness) e_at_z = 0;
        
        return e_at_z;
    };           
    
    // Calculate the electric field at the Z component of the position vector
    double e_at_z = fieldFunction(position.Z());
    
    // Return the electric field vector (only Z component is non-zero)
    return TVector3(0, 0, e_at_z);
}

