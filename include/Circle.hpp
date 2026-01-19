#pragma once
#include "GeometricObject.hpp"
#include "ObjectFactory.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>

class Circle : public GeometricObject {
public:
    std::string getDescription() const override {
        return "A circle has a radius.  If the user provides the radius:\n\n"
               "    ./describe_object circle <radius>\n\n"
               "The program can calculate: perimeter, circumference, area";
    }
    
    size_t getRequiredParams() const override {
        return 1;
    }
    
    std::string calculate(const std::vector<double>& params) const override {
        double radius = params[0];
        double circumference = 2 * M_PI * radius;
        double area = M_PI * radius * radius;
        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "Circle with radius " << radius << ":\n";
        oss << "  Circumference: " << circumference << "\n";
        oss << "  Perimeter: " << circumference << "\n";
        oss << "  Area: " << area;
        
        return oss.str();
    }
};

REGISTER_OBJECT(Circle, "circle")

