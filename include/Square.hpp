#pragma once
#include "GeometricObject.hpp"
#include "ObjectFactory.hpp"
#include <sstream>
#include <iomanip>

class Square : public GeometricObject {
public:
    std::string getDescription() const override {
        return "A square has four sides that are of equal length.  If the user provides the length:\n\n"
               "    ./describe_object square <length>\n\n"
               "The program can calculate: perimeter, area";
    }
    
    size_t getRequiredParams() const override {
        return 1;
    }
    
    std::string calculate(const std::vector<double>& params) const override {
        double length = params[0];
        double perimeter = 4 * length;
        double area = length * length;
        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "Square with side length " << length << ":\n";
        oss << "  Perimeter: " << perimeter << "\n";
        oss << "  Area: " << area;
        
        return oss.str();
    }
};

REGISTER_OBJECT(Square, "square")

