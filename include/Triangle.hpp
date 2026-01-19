/*
 * Example: Adding a new geometric object
 * 
 * This demonstrates how easy it is to extend the system.
 * Simply include this header in main.cpp and rebuild!
 */

#pragma once
#include "GeometricObject.hpp"
#include "ObjectFactory.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>

class Triangle : public GeometricObject {
public:
    std::string getDescription() const override {
        return "A triangle has three sides.  If the user provides the three side lengths:\n\n"
               "    ./describe_object triangle <side1> <side2> <side3>\n\n"
               "The program can calculate: perimeter, area (using Heron's formula)";
    }
    
    size_t getRequiredParams() const override {
        return 3;
    }
    
    std::string calculate(const std::vector<double>& params) const override {
        double a = params[0];
        double b = params[1];
        double c = params[2];
        
        double perimeter = a + b + c;
        double s = perimeter / 2; // semi-perimeter
        double area = std::sqrt(s * (s - a) * (s - b) * (s - c));
        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "Triangle with sides " << a << ", " << b << ", and " << c << ":\n";
        oss << "  Perimeter: " << perimeter << "\n";
        oss << "  Area: " << area;
        
        return oss.str();
    }
};

REGISTER_OBJECT(Triangle, "triangle")

