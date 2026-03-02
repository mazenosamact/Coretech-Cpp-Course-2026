# Creational Patterns: Factory Pattern in C++

## Introduction to Factory Pattern

The **Factory pattern** is a creational design pattern that provides a way to create objects without specifying their exact classes. Instead of using `new` directly, you use a factory function or class that handles object creation.

### Real-World Analogy

Think of a car factory:
- **Without Factory**: You build each car component yourself (engine, wheels, chassis) and assemble them
- **With Factory**: You order a car type, and the factory handles all the building and assembly details

### Key Characteristics

- **Encapsulates object creation** logic in one place
- **Hides implementation details** of which class to instantiate
- **Centralizes** where objects are created
- **Makes code more flexible** when adding new types
- **Separates creation** from usage

### When to Use Factory Pattern

✓ Creating different types of objects with common interface
✓ Object creation logic is complex
✓ Want to avoid scattered `new` statements throughout code
✓ Need to easily add new object types
✓ Object type depends on configuration or parameters
✓ Want to decouple creation from client code

---

## Basic Factory Pattern Architecture

```
┌─────────────────────┐
│  Factory Class      │
│  + create(type)     │
└────────────┬────────┘
             │
             │ creates
             ▼
      ┌──────────────────┐
      │   Base Class     │ (interface)
      │  (abstract/pure) │
      └────────┬─────────┘
               │
      ┌────────┴─────────┐
      │                  │
  ┌───────────┐    ┌───────────┐
  │ProductA   │    │ProductB   │
  │(concrete) │    │(concrete) │
  └───────────┘    └───────────┘
```

---

## Simple C++ Implementation

### Basic Factory Example

```cpp
#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Abstract product
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual string getType() const = 0;
};

// Concrete products
class Circle : public Shape {
public:
    void draw() const override {
        cout << "Drawing Circle" << endl;
    }
    
    string getType() const override {
        return "Circle";
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        cout << "Drawing Rectangle" << endl;
    }
    
    string getType() const override {
        return "Rectangle";
    }
};

class Triangle : public Shape {
public:
    void draw() const override {
        cout << "Drawing Triangle" << endl;
    }
    
    string getType() const override {
        return "Triangle";
    }
};

// Factory class
class ShapeFactory {
public:
    static unique_ptr<Shape> createShape(const string& shapeType) {
        if (shapeType == "circle") {
            return make_unique<Circle>();
        } 
        else if (shapeType == "rectangle") {
            return make_unique<Rectangle>();
        }
        else if (shapeType == "triangle") {
            return make_unique<Triangle>(); 
        }
        return nullptr;  // Unknown type
    }
};

// Client code
int main() {
    // Create shapes using factory
    auto shape1 = ShapeFactory::createShape("circle");
    auto shape2 = ShapeFactory::createShape("rectangle");
    auto shape3 = ShapeFactory::createShape("triangle");
    
    // Use objects
    if (shape1) {
        cout << "Type: " << shape1->getType() << " - ";
        shape1->draw();
    }
    
    if (shape2) {
        cout << "Type: " << shape2->getType() << " - ";
        shape2->draw();
    }
    
    if (shape3) {
        cout << "Type: " << shape3->getType() << " - ";
        shape3->draw();
    }
    
    return 0;
}

// Output:
// Type: Circle - Drawing Circle
// Type: Rectangle - Drawing Rectangle
// Type: Triangle - Drawing Triangle
```

---

## Embedded Systems Example: Device Factory

### Scenario

An embedded Linux system that creates different types of communication devices (UART, I2C, SPI) based on configuration.

```cpp
#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Abstract device interface
class CommunicationDevice {
public:
    virtual ~CommunicationDevice() = default;
    virtual void initialize() = 0;
    virtual void send(const string& data) = 0;
    virtual void shutdown() = 0;
    virtual string getType() const = 0;
};

// Concrete devices
class UARTDevice : public CommunicationDevice {
public:
    void initialize() override {
        cout << "[UART] Initializing UART device on /dev/ttyS0" << endl;
    }
    
    void send(const string& data) override {
        cout << "[UART] Sending: " << data << endl;
    }
    
    void shutdown() override {
        cout << "[UART] Shutting down UART device" << endl;
    }
    
    string getType() const override {
        return "UART";
    }
};

class I2CDevice : public CommunicationDevice {
public:
    void initialize() override {
        cout << "[I2C] Initializing I2C device on bus 1" << endl;
    }
    
    void send(const string& data) override {
        cout << "[I2C] Sending: " << data << endl;
    }
    
    void shutdown() override {
        cout << "[I2C] Shutting down I2C device" << endl;
    }
    
    string getType() const override {
        return "I2C";
    }
};

class SPIDevice : public CommunicationDevice {
public:
    void initialize() override {
        cout << "[SPI] Initializing SPI device (clock: 10MHz)" << endl;
    }
    
    void send(const string& data) override {
        cout << "[SPI] Sending: " << data << endl;
    }
    
    void shutdown() override {
        cout << "[SPI] Shutting down SPI device" << endl;
    }
    
    string getType() const override {
        return "SPI";
    }
};

// Device factory
class DeviceFactory {
public:
    static unique_ptr<CommunicationDevice> createDevice(const string& deviceType) {
        if (deviceType == "uart") {
            return make_unique<UARTDevice>();
        }
        else if (deviceType == "i2c") {
            return make_unique<I2CDevice>();
        }
        else if (deviceType == "spi") {
            return make_unique<SPIDevice>();
        }
        return nullptr;
    }
};

// Usage
int main() {
    cout << "=== Creating Devices ===\n";
    auto uartDev = DeviceFactory::createDevice("uart");
    auto i2cDev = DeviceFactory::createDevice("i2c");
    auto spiDev = DeviceFactory::createDevice("spi");
    
    cout << "\n=== Initializing Devices ===\n";
    if (uartDev) {
        uartDev->initialize();
        uartDev->send("Hello from UART");
        uartDev->shutdown();
    }
    
    cout << "\n";
    if (i2cDev) {
        i2cDev->initialize();
        i2cDev->send("Hello from I2C");
        i2cDev->shutdown();
    }
    
    cout << "\n";
    if (spiDev) {
        spiDev->initialize();
        spiDev->send("Hello from SPI");
        spiDev->shutdown();
    }
    
    return 0;
}

// Output:
// === Creating Devices ===
//
// === Initializing Devices ===
// [UART] Initializing UART device on /dev/ttyS0
// [UART] Sending: Hello from UART
// [UART] Shutting down UART device
//
// [I2C] Initializing I2C device on bus 1
// [I2C] Sending: Hello from I2C
// [I2C] Shutting down I2C device
//
// [SPI] Initializing SPI device (clock: 10MHz)
// [SPI] Sending: Hello from SPI
// [SPI] Shutting down SPI device
```

---

## Benefits

### Advantages

- ✓ **Centralized creation logic** - all object creation in one place
- ✓ **Easy to extend** - add new types without changing client code
- ✓ **Reduces code duplication** - `new` statements scattered everywhere becomes single method
- ✓ **Decouples client** from concrete classes
- ✓ **Easier testing** - can mock factory in unit tests
- ✓ **Configuration-driven** - type can come from config files

### Disadvantages

- ✗ Adding new types requires modifying factory
- ✗ Adds one extra layer of indirection
- ✗ Can lead to large factory methods if many types

---

## Key Differences from Factory Method

**Simple Factory** (what we covered):
- Single factory class/function
- Static creation method
- Simple and straightforward
- Limited extensibility without modification

**Factory Method** (NOT covered here):
- Multiple factory classes (one per type)
- Inheritance-based creation
- More complex but highly extensible
- Follows Open/Closed Principle strictly

---

## Best Practices

1. **Use shared_ptr/unique_ptr** instead of raw pointers
2. **Return nullptr** for invalid types
3. **Keep factory logic simple** - if too complex, consider parameterization
4. **Document supported types** clearly
5. **Add logging** to track object creation
6. **Validate input** before creating objects
7. **Use string or enum** for type parameter (enum is safer)

---

## Summary

The **Factory pattern** is a simple, practical way to:
- Centralize object creation
- Hide implementation details
- Make code more maintainable
- Add new types easily

Use it when you have multiple related objects that clients need to create without knowing their concrete types.
