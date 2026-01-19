#pragma once
#include <string>
#include <vector>
#include <memory>

/**
 * Abstract base class for all geometric objects.
 * Defines the interface that all objects must implement.
 */
class GeometricObject {
public:
    virtual ~GeometricObject() = default;
    
    /**
     * Returns a description of the object and how to use it.
     */
    virtual std::string getDescription() const = 0;
    
    /**
     * Returns the number of parameters this object requires.
     */
    virtual size_t getRequiredParams() const = 0;
    
    /**
     * Calculate and return formatted results based on provided parameters.
     * @param params Vector of numeric parameters
     * @return Formatted string with calculations
     */
    virtual std::string calculate(const std::vector<double>& params) const = 0;
};

using ObjectPtr = std::unique_ptr<GeometricObject>;

