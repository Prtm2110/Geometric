# Low-Level Design (LLD)

## System Overview
Extensible geometric object system with zero coupling between main program and shape implementations using OOP principles.

---

## Architecture

```
Main Program (knows nothing about shapes)
    ↓ uses
ObjectFactory (Singleton + Registry)
    ↓ creates
GeometricObject (Abstract Interface)
    ↓ implemented by
Circle | Square | Rectangle | Triangle
(auto-register at startup)
```

---

## Core Components

### 1. GeometricObject (Abstract Base)
Defines contract for all shapes:
```cpp
class GeometricObject {
    virtual string getDescription() const = 0;
    virtual size_t getRequiredParams() const = 0;
    virtual string calculate(vector<double>&) const = 0;
}
```

### 2. ObjectFactory (Singleton + Registry)
Creates objects by name without knowing concrete types:
```cpp
class ObjectFactory {
    map<string, Creator> registry_;
    + static instance(): ObjectFactory&
    + create(name): ObjectPtr
    + registerObject(name, creator)
}
```

**Key Flow:**
1. Static registrars execute before `main()`
2. Each shape auto-registers its creator function
3. Runtime: `factory.create("circle")` → lookup → create → return

### 3. ObjectRegistrar (Auto-Registration)
Handles automatic registration via static initialization:
```cpp
#define REGISTER_OBJECT(Class, name) \
    static ObjectRegistrar<Class> registrar_##Class(name);
```

### 4. Concrete Shapes
All follow same pattern:
```cpp
class Circle : public GeometricObject {
    // Implement 3 virtual methods
};
REGISTER_OBJECT(Circle, "circle")
```

---

## Design Patterns

- **Factory Pattern**: Create objects without exposing concrete classes
- **Registry Pattern**: Map names to creator functions
- **Singleton**: Single global factory instance
- **Template Method**: Abstract interface with concrete implementations

---

## OOP Principles Applied

✅ **Encapsulation**: Main has zero knowledge of specific shapes  
✅ **Polymorphism**: All shapes used through base interface  
✅ **Abstraction**: GeometricObject defines contract  
✅ **Open-Closed**: Add shapes without modifying main  
✅ **Dependency Inversion**: Main depends on abstractions, not concrete classes  
✅ **Single Responsibility**: Each class has one clear purpose  
✅ **Liskov Substitution**: Any shape can replace another through interface

---

## Data Flow

**Describe Object:**
```
User input → Main parses → Factory creates → Get description → Output
```

**Calculate Properties:**
```
User input → Main parses → Factory creates → Validate params → Calculate → Output
```

---

## Extensibility

**Add new shape (3 steps):**
1. Create `include/NewShape.hpp` implementing `GeometricObject` + `REGISTER_OBJECT` macro
2. Include in `src/main.cpp`
3. Rebuild

Result: Zero changes to main logic, factory, or other shapes.

---

## File Organization
```
lfx/
├── include/          # Headers (interfaces + shapes)
├── src/              # main.cpp
├── tests/            # test_main.cpp
├── Makefile
├── README.md
└── LLD.md
```

---

## Memory & Error Handling

- Smart pointers (`unique_ptr`) - no manual memory management
- Unknown object → `nullptr` → error message
- Invalid params → exception caught → user-friendly message
- Wrong param count → validation → show usage

