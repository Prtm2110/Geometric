# Geometric Object Description System

A highly extensible C++ program demonstrating proper object-oriented design and following LLD principles with zero coupling between the main program and specific object implementations.

## Quick Start

### Build
```bash
make                # Build main program
make test           # Build and run tests
make clean          # Clean build artifacts
```

### Usage Examples

**Get help for any object:**
```bash
$ ./describe_object circle
A circle has a radius.  If the user provides the radius:

    "describe_object circle <radius>"

The program can calculate: perimeter, circumference, area
```

**Calculate circle properties:**
```bash
$ ./describe_object circle 5
Circle with radius 5.00:
  Circumference: 31.42
  Perimeter: 31.42
  Area: 78.54
```

**Calculate square properties:**
```bash
$ ./describe_object square 10
Square with side length 10.00:
  Perimeter: 40.00
  Area: 100.00
```

**Calculate rectangle properties:**
```bash
$ ./describe_object rect 5 8
Rectangle with sides 5.00 and 8.00:
  Perimeter: 26.00
  Area: 40.00
```

**Calculate triangle properties:**
```bash
$ ./describe_object triangle 3 4 5
Triangle with sides 3.00, 4.00, and 5.00:
  Perimeter: 12.00
  Area: 6.00
```

## Design Highlights

**Main program has zero knowledge of specific shapes**  
Uses abstract interface + factory pattern + auto-registration

**Architecture**:
```
Main → Factory → GeometricObject Interface
                      ↑
         Circle | Square | Rectangle | Triangle
              (auto-register at startup)
```

**Key Principles**:
- Open-Closed: Add shapes without modifying main
- Dependency Inversion: Main depends only on abstractions
- Single Responsibility: Each class has one clear purpose

## Extensibility

Add a new shape in 3 steps:

1. Create `include/NewShape.hpp`:
```cpp
class NewShape : public GeometricObject {
    // Implement: getDescription(), getRequiredParams(), calculate()
};
REGISTER_OBJECT(NewShape, "newshape")
```

2. Include in `src/main.cpp`: `#include "NewShape.hpp"`
3. Rebuild: `make`

No changes to factory, main logic, or other shapes required.

## Project Structure
```
Geometric/
├── include/          # Header files (interfaces & shapes)
├── src/              # Source files (main.cpp)
├── tests/            # Test suite
├── Makefile
├── README.md         # This file
└── LLD.md           # Complete low-level design doc
```

## Documentation

This is a C++ program that exemplifies proper object-oriented design principles and adheres to Low-Level Design (LLD) best practices. The architecture is designed with zero coupling between the main program and specific object implementations, allowing for high extensibility and maintainability. This approach enables easy addition of new features and modifications without affecting the core application logic.

**Key Features:**
- Object-oriented design patterns
- Low-Level Design (LLD) principles
- Loose coupling architecture
- High extensibility
- Dependency inversion
- **[LLD.md](LLD.md)**: Complete architecture, design patterns, data flow, and extensibility mechanisms

## Testing
```bash
make test            # Run all tests
```

Tests cover: object creation, calculations, parameter validation, and error handling.

---

## Quick Reference

### Available Objects
- `circle <radius>`
- `square <length>`
- `rect <length1> <length2>`
- `triangle <side1> <side2> <side3>`

### Common Commands
```bash
./describe_object <name>              # Show object description
./describe_object <name> <params...>  # Calculate properties
make                                   # Build program
make test                              # Run tests
make clean                             # Clean build
```

### Project Files
- **README.md** - This file (quick start & reference)
- **LLD.md** - Complete architecture documentation
- **include/** - All header files
- **src/** - Main program
- **tests/** - Test suite

