#pragma once
#include "GeometricObject.hpp"
#include "ObjectFactory.hpp"
#include <sstream>
#include <iomanip>

class Rectangle : public GeometricObject {
public:
    std::string getDescription() const override {
        return "A rectangle has 4 sides broken into 2 side pairs of equal length and are parallel.  If the user provides the length of each pair:\n\n"
               "    ./describe_object rect <length side 1> <length side 2>\n\n"
               "The program can calculate: perimeter, area";
    }
    
    size_t getRequiredParams() const override {
        return 2;
    }
    
    std::string calculate(const std::vector<double>& params) const override {
        double length1 = params[0];
        double length2 = params[1];
        double perimeter = 2 * (length1 + length2);
        double area = length1 * length2;
        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "Rectangle with sides " << length1 << " and " << length2 << ":\n";
        oss << "  Perimeter: " << perimeter << "\n";
        oss << "  Area: " << area;
        
        return oss.str();
    }
};

REGISTER_OBJECT(Rectangle, "rect")

