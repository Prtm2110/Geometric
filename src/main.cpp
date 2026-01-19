#include "ObjectFactory.hpp"
#include "Circle.hpp"
#include "Square.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <object_name> [parameters...]\n";
        return 1;
    }
    
    std::string objectName = argv[1];
    
    // Create object using factory - main knows nothing about specific types
    auto object = ObjectFactory::instance().create(objectName);
    
    if (!object) {
        std::cerr << "Unknown object: " << objectName << "\n";
        return 1;
    }
    
    // If no parameters provided, show description
    if (argc == 2) {
        std::cout << object->getDescription() << "\n";
        return 0;
    }
    
    // Parse numeric parameters
    std::vector<double> params;
    for (int i = 2; i < argc; ++i) {
        try {
            params.push_back(std::stod(argv[i]));
        } catch (...) {
            std::cerr << "Invalid parameter: " << argv[i] << "\n";
            return 1;
        }
    }
    
    // Validate parameter count
    if (params.size() < object->getRequiredParams()) {
        std::cerr << "Error: Expected " << object->getRequiredParams() 
                  << " parameters, got " << params.size() << "\n\n";
        std::cout << object->getDescription() << "\n";
        return 1;
    }
    
    // Calculate and display results
    std::cout << object->calculate(params) << "\n";
    
    return 0;
}

