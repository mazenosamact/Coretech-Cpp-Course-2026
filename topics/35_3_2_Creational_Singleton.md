# Creational Patterns: Singleton Pattern in C++

## Introduction to Singleton Pattern

The **Singleton pattern** is a creational design pattern that ensures a class has only one instance and provides a global point of access to it.

### Real-World Analogy

Think of a printer in an office:
- There's only one printer shared by everyone
- Everyone accesses the same printer through a standard interface
- You don't create a new printer; you use the existing one
- If someone tries to create another printer, they get the same one

### Key Characteristics

- **Single Instance**: Only one object of the class exists
- **Global Access**: Easy to access from anywhere
- **Lazy Initialization**: Created when first needed
- **Thread-Safe**: Should handle multi-threaded access
- **Private Constructor**: Prevents direct instantiation

### When to Use Singleton Pattern

✓ Need exactly one instance of a class
✓ Centralized control of a shared resource
✓ Database connections
✓ Logger objects
✓ Configuration managers
✓ Thread pools
✓ Caches

---

## Basic C++ Implementation

### Simple Singleton

```cpp
#include <iostream>
using namespace std;

class Logger {
private:
    static Logger* instance;
    
    // Private constructor prevents instantiation
    Logger() {
        cout << "Logger instance created" << endl;
    }
    
public:
    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    // Get the singleton instance
    static Logger* getInstance() {
        if (instance == nullptr) {
            instance = new Logger();
        }
        return instance;
    }
    
    void log(const string& message) {
        cout << "[LOG] " << message << endl;
    }
};

// Initialize static member
Logger* Logger::instance = nullptr;

// Usage
int main() {
    Logger* logger1 = Logger::getInstance();
    logger1->log("First access");
    
    Logger* logger2 = Logger::getInstance();
    logger2->log("Second access");
    
    // Both are the same instance
    cout << "Same instance? " << (logger1 == logger2 ? "Yes" : "No") << endl;
    
    return 0;
}

// Output:
// Logger instance created
// [LOG] First access
// [LOG] Second access
// Same instance? Yes
```

---

## Modern C++ Implementation (C++11 and Later)

### Meyer's Singleton (Thread-Safe, Easiest)

```cpp
#include <iostream>
using namespace std;

class Configuration {
private:
    // Private constructor
    Configuration() {
        cout << "Configuration loaded" << endl;
    }
    
public:
    // Delete copy and move operations
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;
    
    // Static method returning reference
    static Configuration& getInstance() {
        static Configuration instance;  // Created once, thread-safe
        return instance;
    }
    
    void setParameter(const string& key, const string& value) {
        cout << "Setting " << key << " = " << value << endl;
    }
    
    string getParameter(const string& key) const {
        return "value";
    }
};

// Usage
int main() {
    Configuration& config1 = Configuration::getInstance();
    config1.setParameter("hostname", "localhost");
    
    Configuration& config2 = Configuration::getInstance();
    config2.setParameter("port", "8080");
    
    cout << "Same instance? " 
         << (&config1 == &config2 ? "Yes" : "No") << endl;
    
    return 0;
}

// Output:
// Configuration loaded
// Setting hostname = localhost
// Setting port = 8080
// Same instance? Yes
```

---

## Embedded Systems Example: System Resources

### Scenario

An embedded system that manages hardware resources (GPIO, timers) through a singleton manager.

```cpp
#include <iostream>
#include <map>
using namespace std;

class HardwareManager {
private:
    int gpioCount = 0;
    int timerCount = 0;
    map<int, bool> gpioStates;
    
    // Private constructor
    HardwareManager() {
        cout << "[System] Hardware Manager initialized" << endl;
        gpioCount = 32;
        timerCount = 4;
    }
    
public:
    HardwareManager(const HardwareManager&) = delete;
    HardwareManager& operator=(const HardwareManager&) = delete;
    
    static HardwareManager& getInstance() {
        static HardwareManager instance;
        return instance;
    }
    
    void setGPIO(int pin, bool state) {
        if (pin < gpioCount) {
            gpioStates[pin] = state;
            cout << "[GPIO] Pin " << pin << " set to " 
                 << (state ? "HIGH" : "LOW") << endl;
        }
    }
    
    bool getGPIO(int pin) const {
        auto it = gpioStates.find(pin);
        return (it != gpioStates.end()) ? it->second : false;
    }
    
    void startTimer(int timerID, int milliseconds) {
        if (timerID < timerCount) {
            cout << "[Timer] Timer " << timerID << " started for " 
                 << milliseconds << "ms" << endl;
        }
    }
    
    int getAvailableGPIOs() const {
        return gpioCount;
    }
};

// Usage
int main() {
    // Access hardware manager from different parts of code
    HardwareManager& hw1 = HardwareManager::getInstance();
    hw1.setGPIO(5, true);
    hw1.startTimer(0, 1000);
    
    // Later in another function
    HardwareManager& hw2 = HardwareManager::getInstance();
    hw2.setGPIO(10, false);
    cout << "Available GPIOs: " << hw2.getAvailableGPIOs() << endl;
    
    cout << "Same instance? " 
         << (&hw1 == &hw2 ? "Yes" : "No") << endl;
    
    return 0;
}

// Output:
// [System] Hardware Manager initialized
// [GPIO] Pin 5 set to HIGH
// [Timer] Timer 0 started for 1000ms
// [GPIO] Pin 10 set to LOW
// Available GPIOs: 32
// Same instance? Yes
```

---

## Advantages and Disadvantages

### Advantages

- ✓ **Single Instance**: Guarantees one object exists
- ✓ **Global Access**: Easy to access from anywhere
- ✓ **Lazy Loading**: Created only when needed
- ✓ **Resource Control**: Manages shared resources efficiently
- ✓ **Thread-Safe**: Modern implementations are thread-safe

### Disadvantages

- ✗ **Global State**: Can make code harder to test
- ✗ **Hidden Dependencies**: Dependencies not explicit
- ✗ **Harder to Mock**: Difficult to replace in unit tests
- ✗ **Can Be Overused**: Not everything needs to be a singleton

---

## Best Practices

1. **Prefer Meyers' Singleton** (C++11+) - most elegant and thread-safe
2. **Use references** instead of pointers when possible
3. **Avoid global state** - use dependency injection when applicable
4. **Document the reasoning** for making something a singleton
5. **Make constructors private** and copy/move operations deleted
6. **Consider if it really needs to be a singleton** - often overused
7. **Use sparingly** - prefer passing objects as parameters

---

## When NOT to Use Singleton

- When you need multiple instances with different configurations
- When testing is critical (harder to mock)
- When dependency injection is available
- For classes that might need to be instantiated multiple times in future

---

## Summary

The **Singleton pattern** ensures a class has only one instance and provides global access to it. It's useful for:
- Resource managers (databases, file systems)
- Logger implementations
- Configuration managers
- Hardware/platform abstractions

Use **Meyers' Singleton** in modern C++ for the simplest, most thread-safe implementation.
