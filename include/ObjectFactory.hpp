#pragma once
#include "GeometricObject.hpp"
#include <map>
#include <functional>
#include <string>

/**
 * Factory for creating geometric objects by name.
 * Uses a registry pattern for easy extensibility.
 */
class ObjectFactory {
public:
    using Creator = std::function<ObjectPtr()>;
    
    static ObjectFactory& instance() {
        static ObjectFactory factory;
        return factory;
    }
    
    /**
     * Register a new object type with the factory.
     */
    void registerObject(const std::string& name, Creator creator) {
        registry_[name] = creator;
    }
    
    /**
     * Create an object by name.
     */
    ObjectPtr create(const std::string& name) const {
        auto it = registry_.find(name);
        if (it != registry_.end()) {
            return it->second();
        }
        return nullptr;
    }
    
    /**
     * Check if an object type is registered.
     */
    bool hasObject(const std::string& name) const {
        return registry_.find(name) != registry_.end();
    }
    
private:
    ObjectFactory() = default;
    std::map<std::string, Creator> registry_;
};

/**
 * Helper class for auto-registration of objects.
 */
template<typename T>
class ObjectRegistrar {
public:
    ObjectRegistrar(const std::string& name) {
        ObjectFactory::instance().registerObject(name, []() {
            return std::make_unique<T>();
        });
    }
};

#define REGISTER_OBJECT(Class, name) \
    static ObjectRegistrar<Class> registrar_##Class(name);

