#include "../include/GeometricObject.hpp"
#include "../include/ObjectFactory.hpp"
#include "../include/Circle.hpp"
#include "../include/Square.hpp"
#include "../include/Rectangle.hpp"
#include "../include/Triangle.hpp"
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>

// Simple test framework
int tests_passed = 0;
int tests_failed = 0;

#define TEST(name) void name()
#define ASSERT(condition) \
    if (!(condition)) { \
        std::cerr << "FAIL: " << __FUNCTION__ << " at line " << __LINE__ << "\n"; \
        tests_failed++; \
        return; \
    }
#define RUN_TEST(test) \
    std::cout << "Running " << #test << "... "; \
    test(); \
    tests_passed++; \
    std::cout << "PASS\n";

// Helper to check floating point equality
bool approx_equal(double a, double b, double epsilon = 0.01) {
    return std::abs(a - b) < epsilon;
}

// Test: Factory can create registered objects
TEST(test_factory_creates_circle) {
    auto obj = ObjectFactory::instance().create("circle");
    ASSERT(obj != nullptr);
    ASSERT(obj->getRequiredParams() == 1);
}

TEST(test_factory_creates_square) {
    auto obj = ObjectFactory::instance().create("square");
    ASSERT(obj != nullptr);
    ASSERT(obj->getRequiredParams() == 1);
}

TEST(test_factory_creates_rectangle) {
    auto obj = ObjectFactory::instance().create("rect");
    ASSERT(obj != nullptr);
    ASSERT(obj->getRequiredParams() == 2);
}

TEST(test_factory_creates_triangle) {
    auto obj = ObjectFactory::instance().create("triangle");
    ASSERT(obj != nullptr);
    ASSERT(obj->getRequiredParams() == 3);
}

// Test: Factory returns nullptr for unknown objects
TEST(test_factory_unknown_object) {
    auto obj = ObjectFactory::instance().create("unknown_shape");
    ASSERT(obj == nullptr);
}

// Test: Circle calculations
TEST(test_circle_calculations) {
    auto circle = ObjectFactory::instance().create("circle");
    std::vector<double> params = {5.0};
    
    // Calculate results
    std::string result = circle->calculate(params);
    
    // Expected: circumference = 2 * PI * 5 = 31.42
    //          area = PI * 5^2 = 78.54
    ASSERT(result.find("31.42") != std::string::npos);
    ASSERT(result.find("78.54") != std::string::npos);
}

// Test: Square calculations
TEST(test_square_calculations) {
    auto square = ObjectFactory::instance().create("square");
    std::vector<double> params = {10.0};
    
    std::string result = square->calculate(params);
    
    // Expected: perimeter = 4 * 10 = 40
    //          area = 10 * 10 = 100
    ASSERT(result.find("40.00") != std::string::npos);
    ASSERT(result.find("100.00") != std::string::npos);
}

// Test: Rectangle calculations
TEST(test_rectangle_calculations) {
    auto rect = ObjectFactory::instance().create("rect");
    std::vector<double> params = {5.0, 8.0};
    
    std::string result = rect->calculate(params);
    
    // Expected: perimeter = 2 * (5 + 8) = 26
    //          area = 5 * 8 = 40
    ASSERT(result.find("26.00") != std::string::npos);
    ASSERT(result.find("40.00") != std::string::npos);
}

// Test: Triangle calculations
TEST(test_triangle_calculations) {
    auto triangle = ObjectFactory::instance().create("triangle");
    std::vector<double> params = {3.0, 4.0, 5.0};  // Right triangle
    
    std::string result = triangle->calculate(params);
    
    // Expected: perimeter = 3 + 4 + 5 = 12
    //          area = 6 (using Heron's formula)
    ASSERT(result.find("12.00") != std::string::npos);
    ASSERT(result.find("6.00") != std::string::npos);
}

// Test: Object descriptions are not empty
TEST(test_circle_description) {
    auto circle = ObjectFactory::instance().create("circle");
    std::string desc = circle->getDescription();
    ASSERT(!desc.empty());
    ASSERT(desc.find("radius") != std::string::npos);
}

TEST(test_square_description) {
    auto square = ObjectFactory::instance().create("square");
    std::string desc = square->getDescription();
    ASSERT(!desc.empty());
    ASSERT(desc.find("square") != std::string::npos || desc.find("equal length") != std::string::npos);
}

// Test: Parameter requirements
TEST(test_parameter_requirements) {
    auto circle = ObjectFactory::instance().create("circle");
    auto rect = ObjectFactory::instance().create("rect");
    auto triangle = ObjectFactory::instance().create("triangle");
    
    ASSERT(circle->getRequiredParams() == 1);
    ASSERT(rect->getRequiredParams() == 2);
    ASSERT(triangle->getRequiredParams() == 3);
}

// Test: Multiple object creation doesn't interfere
TEST(test_multiple_objects) {
    auto circle1 = ObjectFactory::instance().create("circle");
    auto square1 = ObjectFactory::instance().create("square");
    auto circle2 = ObjectFactory::instance().create("circle");
    
    ASSERT(circle1 != nullptr);
    ASSERT(square1 != nullptr);
    ASSERT(circle2 != nullptr);
    ASSERT(circle1->getRequiredParams() == circle2->getRequiredParams());
}

int main() {
    std::cout << "=================================\n";
    std::cout << "   Geometric Objects Test Suite  \n";
    std::cout << "=================================\n\n";
    
    // Run all tests
    RUN_TEST(test_factory_creates_circle);
    RUN_TEST(test_factory_creates_square);
    RUN_TEST(test_factory_creates_rectangle);
    RUN_TEST(test_factory_creates_triangle);
    RUN_TEST(test_factory_unknown_object);
    RUN_TEST(test_circle_calculations);
    RUN_TEST(test_square_calculations);
    RUN_TEST(test_rectangle_calculations);
    RUN_TEST(test_triangle_calculations);
    RUN_TEST(test_circle_description);
    RUN_TEST(test_square_description);
    RUN_TEST(test_parameter_requirements);
    RUN_TEST(test_multiple_objects);
    
    // Summary
    std::cout << "\n=================================\n";
    std::cout << "Tests passed: " << tests_passed << "\n";
    std::cout << "Tests failed: " << tests_failed << "\n";
    std::cout << "=================================\n";
    
    return tests_failed > 0 ? 1 : 0;
}
