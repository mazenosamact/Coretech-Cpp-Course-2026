# Inheritance in C++

Inheritance is a core pillar of Object-Oriented Programming (OOP) that allows a derived class (child class) to inherit properties and methods from a base class (parent class). This promotes code reuse, hierarchical relationships, and polymorphism.

## Basic Syntax

### Class Inheritance

The basic syntax for inheritance in C++ is:

```cpp
class DerivedClass : accessSpecifier BaseClass {
    // Derived class members
};
```

Where `accessSpecifier` can be:
- **`public`**: Base class public members become public in derived class, protected members stay protected
- **`protected`**: Base class public and protected members become protected in derived class
- **`private`** (default): All base class members become private in derived class

### Example: Basic Inheritance

```cpp
#include <iostream>
using namespace std;

// Base class
class Animal {
protected:  // Accessible in derived classes
    string species;
    
public:
    Animal(string s) : species(s) {}
    
    void describe() {
        cout << "This is a " << species << endl;
    }
};

// Derived class
class Dog : public Animal {  // Public inheritance
private:
    string breed;
    
public:
    Dog(string s, string b) : Animal(s), breed(b) {}
    
    void showBreed() {
        cout << "Breed: " << breed << endl;
    }
};

int main() {
    Dog myDog("Canine", "Golden Retriever");
    myDog.describe();      // Inherited method
    myDog.showBreed();     // Derived class method
    return 0;
}
// Output:
// This is a Canine
// Breed: Golden Retriever
```

## Method Overriding

Overriding allows a derived class to provide a specific implementation of a method that is already defined in the base class. However, overriding alone doesn't enable runtime polymorphism—you need the `virtual` keyword for that.

### Overriding Without Virtual (Static Binding)

```cpp
class Animal {
public:
    void speak() {
        cout << "Some generic sound" << endl;
    }
};

class Dog : public Animal {
public:
    void speak() {  // This overrides the base class method
        cout << "Woof!" << endl;
    }
};

int main() {
    Animal* animalPtr;
    Dog dog;
    
    animalPtr = &dog;
    animalPtr->speak();  // Calls Animal::speak(), not Dog::speak()
    // Output: Some generic sound
    
    dog.speak();         // Calls Dog::speak()
    // Output: Woof!
    
    return 0;
}
```

## The `virtual` Keyword

The `virtual` keyword enables **runtime polymorphism** (dynamic binding). When a method is declared as `virtual` in the base class, the compiler determines which version to call at runtime based on the actual object type, not the pointer/reference type.

### Example: Virtual Overriding

```cpp
class Animal {
public:
    virtual void speak() {  // Virtual method
        cout << "Some generic sound" << endl;
    }
    
    virtual ~Animal() {}    // Virtual destructor (important!)
};

class Dog : public Animal {
public:
    void speak() override {  // Overrides virtual method
        cout << "Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        cout << "Meow!" << endl;
    }
};

int main() {
    Animal* animals[2];
    animals[0] = new Dog();
    animals[1] = new Cat();
    
    for (int i = 0; i < 2; i++) {
        animals[i]->speak();  // Correct version called at runtime!
    }
    
    delete animals[0];
    delete animals[1];
    
    return 0;
}
// Output:
// Woof!
// Meow!
```

### Key Points About `virtual`:
- Enables runtime polymorphism
- Declared in the base class
- Can be overridden in derived classes
- Has a small performance cost due to dynamic dispatch
- **Always use virtual destructors** if a class will be inherited
- A `virtual` method can still have an implementation (default behavior)



## The `override` Keyword (C++11)

The `override` keyword helps prevent bugs by explicitly stating that a method overrides a virtual method from the base class. The compiler will generate an error if:
- The method doesn't override any base class method
- The signature doesn't match exactly

```cpp
class Animal {
public:
    virtual void speak() {}
    virtual void move(int distance) {}
};

class Dog : public Animal {
public:
    void speak() override {}              // ✓ Correct
    void move(int distance) override {}   // ✓ Correct
    
    // void speak(int x) override {}      // ✗ Error: doesn't match signature
    // void run() override {}             // ✗ Error: no virtual run() in base
};
```

**Best Practice**: Always use `override` when implementing virtual methods—it catches mistakes at compile time.

### The Problem: Non-Virtual Destructors and Memory Leaks

When a base class pointer pointing to a derived object is deleted without a virtual destructor, **only the base class destructor is called**. This leaves derived class resources unclean, causing memory leaks.

**Problem Example: Without Virtual Destructor**

```cpp
#include <iostream>
using namespace std;

class Animal {
protected:
    int* memory;
    
public:
    Animal() {
        memory = new int[100];
        cout << "Animal constructor - allocated memory" << endl;
    }
    
    ~Animal() {  // ✗ NOT virtual - this is the problem!
        cout << "Animal destructor - freeing memory" << endl;
        delete[] memory;
    }
};

class Dog : public Animal {
private:
    char* breed_name;
    
public:
    Dog() : Animal() {
        breed_name = new char[50];
        cout << "Dog constructor - allocated breed_name" << endl;
    }
    
    ~Dog() {
        cout << "Dog destructor - freeing breed_name" << endl;
        delete[] breed_name;  // This will NEVER be called!
    }
};

int main() {
    // Create Dog but treat it as Animal pointer
    Animal* ptr = new Dog();
    
    cout << "\n--- Deleting Dog via Animal pointer ---\n";
    delete ptr;  // Only calls Animal::~Animal(), NOT Dog::~Dog()!
    
    return 0;
}
// Output:
// Animal constructor - allocated memory
// Dog constructor - allocated breed_name
//
// --- Deleting Dog via Animal pointer ---
// Animal destructor - freeing memory
// ✗ Dog destructor - freeing breed_name  [NEVER CALLED - MEMORY LEAK!]
```

In this example, `breed_name` is never freed because the Dog destructor is never called!

**Solution: With Virtual Destructor**

```cpp
#include <iostream>
using namespace std;

class Animal {
protected:
    int* memory;
    
public:
    Animal() {
        memory = new int[100];
        cout << "Animal constructor - allocated memory" << endl;
    }
    
    virtual ~Animal() {  // ✓ Virtual destructor
        cout << "Animal destructor - freeing memory" << endl;
        delete[] memory;
    }
};

class Dog : public Animal {
private:
    char* breed_name;
    
public:
    Dog() : Animal() {
        breed_name = new char[50];
        cout << "Dog constructor - allocated breed_name" << endl;
    }
    
    ~Dog() override {  // ✓ Destructor is properly called
        cout << "Dog destructor - freeing breed_name" << endl;
        delete[] breed_name;
    }
};

int main() {
    // Create Dog but treat it as Animal pointer
    Animal* ptr = new Dog();
    
    cout << "\n--- Deleting Dog via Animal pointer ---\n";
    delete ptr;  // Correctly calls Dog::~Dog(), then Animal::~Animal()
    
    return 0;
}
// Output:
// Animal constructor - allocated memory
// Dog constructor - allocated breed_name
//
// --- Deleting Dog via Animal pointer ---
// Dog destructor - freeing breed_name      [CALLED! ✓]
// Animal destructor - freeing memory       [CALLED! ✓]
```

With the virtual destructor, both destructors are properly called in the correct order (derived first, then base), ensuring all resources are cleaned up.

**Key Takeaway:**
```cpp
// Rule of thumb: If a class will be inherited, use virtual destructor
class Base {
public:
    virtual ~Base() = default;  // Always do this!
};

class Derived : public Base {
public:
    ~Derived() override {}  // Override destructor if you have resources
};
```


## Static vs. Dynamic Polymorphism

Polymorphism means "many forms." C++ supports two main types of polymorphism: **static (compile-time)** and **dynamic (runtime)**. Understanding the differences is crucial for writing efficient and flexible code.

### Static Polymorphism (Compile-Time)

Static polymorphism is resolved at **compile time**. The compiler determines which function to call based on the types of arguments and the context. There is **no runtime overhead**.

#### Function Overloading

```cpp
class Calculator {
public:
    // Same function name, different parameter types
    int add(int a, int b) {
        return a + b;
    }
    
    double add(double a, double b) {
        return a + b;
    }
    
    int add(int a, int b, int c) {
        return a + b + c;
    }
};

int main() {
    Calculator calc;
    
    cout << calc.add(5, 10) << endl;           // Calls int add(int, int)
    cout << calc.add(5.5, 10.5) << endl;       // Calls double add(double, double)
    cout << calc.add(1, 2, 3) << endl;         // Calls int add(int, int, int)
    
    return 0;
}
// Output:
// 15
// 16
// 6
```

#### Template Polymorphism (Generic Programming)

```cpp
template<typename T>
class Container {
private:
    T data;
    
public:
    void set(T value) {
        data = value;
    }
    
    T get() const {
        return data;
    }
};

int main() {
    Container<int> intContainer;
    intContainer.set(42);
    cout << intContainer.get() << endl;  // Output: 42
    
    Container<string> strContainer;
    strContainer.set("Hello");
    cout << strContainer.get() << endl;  // Output: Hello
    
    return 0;
}
```

**Characteristics of Static Polymorphism:**
- Resolved at compile time
- No runtime overhead
- Compiler generates separate code for each type/signature
- Compile time may increase slightly (code bloat from instantiation)
- Type-safe and predictable performance
- Error messages can be unclear for templates

### Dynamic Polymorphism (Runtime)

Dynamic polymorphism is resolved at **runtime**. The compiler generates code that determines which function to call based on the actual object type, using mechanisms like virtual functions. This provides flexibility but adds a small runtime cost.

#### Virtual Functions

```cpp
class Shape {
public:
    virtual void draw() const {
        cout << "Drawing a shape" << endl;
    }
    
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void draw() const override {
        cout << "Drawing a circle" << endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        cout << "Drawing a rectangle" << endl;
    }
};

int main() {
    Shape* shapes[2];
    shapes[0] = new Circle();
    shapes[1] = new Rectangle();
    
    for (int i = 0; i < 2; i++) {
        shapes[i]->draw();  // Which draw()? Determined at runtime!
    }
    
    delete shapes[0];
    delete shapes[1];
    
    return 0;
}
// Output:
// Drawing a circle
// Drawing a rectangle
```

**Characteristics of Dynamic Polymorphism:**
- Resolved at runtime using virtual function tables (vtables)
- Small runtime overhead (vtable lookup)
- Single compiled code for base class and all derived classes
- Flexible—can work with objects not known at compile time
- Requires pointers or references to base class
- Clear and simple error messages

### Comparison Table

| Aspect | Static Polymorphism | Dynamic Polymorphism |
|--------|---------------------|-----------------------|
| **Timing** | Compile-time | Runtime |
| **Mechanism** | Function/operator overloading, templates | Virtual functions, vtables |
| **Performance** | Zero overhead | Small overhead (vtable lookup) |
| **Code Bloat** | Yes (template instantiation) | No (single code) |
| **Flexibility** | Type-safe but rigid | Flexible, extensible |
| **Error Messages** | Can be complex (templates) | Clear and straightforward |
| **Use Case** | Performance-critical, type safety | Plugin systems, frameworks |

### When to Use Each

**Use Static Polymorphism:**
- When you need maximum performance
- When all types are known at compile time
- When you want compile-time type safety
- For container classes (like `std::vector<T>`)
- For mathematical operations

**Use Dynamic Polymorphism:**
- When you need runtime flexibility
- When working with unknown derived types
- When building extensible frameworks
- When the type is determined at runtime (e.g., user input)
- For game engines, GUI frameworks, etc.

### Hybrid Approach

Modern C++ often combines both approaches:

#### CRTP: Curiously Recurring Template Pattern

The CRTP is an advanced C++ idiom that allows you to achieve static polymorphism with inheritance. A derived class passes itself as a template parameter to the base class, enabling the base class to call derived-class methods without using virtual functions.

**Basic Pattern:**

```cpp
template<typename Derived>
class Base {
public:
    void operation() {
        // Call the derived class's implementation at compile time
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        cout << "Derived implementation" << endl;
    }
};

int main() {
    Derived obj;
    obj.operation();  // Calls Derived::implementation() at compile time
    return 0;
}
// Output: Derived implementation
```

**Practical Example: Processing Different Data Types**

```cpp
// CRTP base class
template<typename Derived>
class DataProcessor {
public:
    void process() {
        static_cast<Derived*>(this)->doProcess();
    }
};

// Derived classes
class IntProcessor : public DataProcessor<IntProcessor> {
public:
    void doProcess() {
        cout << "Processing integers" << endl;
    }
};

class StringProcessor : public DataProcessor<StringProcessor> {
public:
    void doProcess() {
        cout << "Processing strings" << endl;
    }
};

template<typename Processor>
void executeProcessor(Processor& processor) {
    processor.process();  // Works with any CRTP-based processor
}

int main() {
    IntProcessor intProc;
    StringProcessor strProc;
    
    executeProcessor(intProc);   // Output: Processing integers
    executeProcessor(strProc);   // Output: Processing strings
    
    return 0;
}
```

**Advantages of CRTP:**
- Zero runtime overhead (no virtual function lookups)
- Compile-time polymorphism with interface-like behavior
- Type-safe—compiler catches mismatches at compile time
- Allows code reuse through inheritance without virtual functions
- Perfect for performance-critical code

**When to Use CRTP:**
- When you need polymorphism without virtual function overhead
- In performance-critical code (e.g., game engines, numerical computing)
- When you want compile-time type safety with extensibility
- Combined with templates for maximum flexibility

**Embedded Systems Example: Sensor Interface with CRTP**

CRTP is particularly valuable in embedded systems where memory is limited and performance is critical. Here's a practical example of a sensor abstraction layer:

```cpp
// CRTP base class for sensors
template<typename SensorType>
class Sensor {
public:
    // Read value with compile-time polymorphism
    int readValue() {
        return static_cast<SensorType*>(this)->readRaw();
    }
    
    // Apply calibration
    float getCalibrated() {
        int rawValue = readValue();
        return static_cast<SensorType*>(this)->calibrate(rawValue);
    }
    
    virtual ~Sensor() = default;
};

// Concrete temperature sensor
class TemperatureSensor : public Sensor<TemperatureSensor> {
private:
    int adcPin;
    float calibrationOffset;
    
public:
    TemperatureSensor(int pin, float offset) 
        : adcPin(pin), calibrationOffset(offset) {}
    
    int readRaw() {
        // Read from ADC (simulated)
        return 500 + (rand() % 50);
    }
    
    float calibrate(int rawValue) {
        // Convert ADC reading to temperature (Celsius)
        return (rawValue / 10.24f) - 40.0f + calibrationOffset;
    }
};

// Concrete pressure sensor
class PressureSensor : public Sensor<PressureSensor> {
private:
    int adcPin;
    float calibrationFactor;
    
public:
    PressureSensor(int pin, float factor) 
        : adcPin(pin), calibrationFactor(factor) {}
    
    int readRaw() {
        // Read from ADC (simulated)
        return 2048 + (rand() % 100);
    }
    
    float calibrate(int rawValue) {
        // Convert to pressure in hPa
        return (rawValue / 4096.0f) * 1013.25f * calibrationFactor;
    }
};

// Generic sensor reader - works with any CRTP-based sensor
template<typename SensorType>
class SensorReader {
public:
    void displayReading(Sensor<SensorType>& sensor) {
        cout << "Raw: " << sensor.readValue() 
             << " | Calibrated: " << sensor.getCalibrated() << endl;
    }
};

int main() {
    TemperatureSensor tempSensor(A0, 0.5f);
    PressureSensor pressureSensor(A1, 1.0f);
    
    SensorReader<TemperatureSensor> tempReader;
    SensorReader<PressureSensor> pressReader;
    
    cout << "Temperature: ";
    tempReader.displayReading(tempSensor);
    
    cout << "Pressure: ";
    pressReader.displayReading(pressureSensor);
    
    return 0;
}
// Output (example):
// Temperature: Raw: 523 | Calibrated: 21.3
// Pressure: Raw: 2053 | Calibrated: 1014.2
```

**Why CRTP for Embedded Systems:**
- **Zero Virtual Function Overhead**: No vtable memory wasted on microcontrollers with limited RAM
- **Compile-Time Specialization**: Compiler generates optimized code for each sensor type
- **Type Safety**: Incorrect sensor usage caught at compile time
- **Inlining**: Smaller, faster code—critical for energy-constrained devices
- **No Runtime Polymorphism Costs**: Every CPU cycle counts in real-time embedded systems

**CRTP vs. Virtual Functions:**

| Aspect | CRTP | Virtual Functions |
|--------|------|-------------------|
| **Overhead** | Zero | Small (vtable lookup) |
| **Compile Time** | Longer (template instantiation) | Shorter |
| **Extensibility** | Requires recompilation | Can extend at runtime |
| **Syntax** | More complex | Simpler and intuitive |
| **Type Safety** | Compile-time checked | Runtime checked |
```cpp
// Template base class (static polymorphism)
template<typename Renderer>
class Game {
public:
    void render() {
        renderer.draw();  // Compile-time polymorphism
    }
    
private:
    Renderer renderer;
};

// Virtual interface (dynamic polymorphism)
class Renderer {
public:
    virtual void draw() = 0;
    virtual ~Renderer() = default;
};

class OpenGLRenderer : public Renderer {
public:
    void draw() override {
        cout << "Drawing with OpenGL" << endl;
    }
};

class VulkanRenderer : public Renderer {
public:
    void draw() override {
        cout << "Drawing with Vulkan" << endl;
    }
};
```

## The `friend` Keyword

The `friend` keyword allows a class or function to access the `private` and `protected` members of another class. However, `friend` is **NOT inherited**—a friend of a base class is not automatically a friend of derived classes.

### Friend Class

```cpp
class Base {
private:
    int secret = 42;
    
    friend class FriendClass;  // FriendClass can access private members
};

class FriendClass {
public:
    void revealSecret(Base& b) {
        cout << "Base's secret: " << b.secret << endl;
    }
};

class DerivedClass : public Base {
    // FriendClass is NOT a friend here!
    // This would be an error: cout << b.secret;
};

int main() {
    Base b;
    FriendClass fc;
    fc.revealSecret(b);  // ✓ Works
    return 0;
}
```

### Friend Function

```cpp
class MyClass {
private:
    int data = 100;
    
    friend void printData(MyClass& obj);  // Friend function
};

void printData(MyClass& obj) {
    cout << "Data: " << obj.data << endl;  // Can access private members
}

int main() {
    MyClass obj;
    printData(obj);  // ✓ Works
    return 0;
}
// Output: Data: 100
```

### Friend Operator Overloading: Stream Insertion

A common and practical use of friend functions is to overload the stream insertion operator (`<<`) for printing custom classes. This allows the object to be printed directly to `cout`.

```cpp
#include <iostream>
using namespace std;

class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    // Friend function for stream insertion operator
    friend ostream& operator<<(ostream& out, const Point& p);
};

// Implementation of the friend operator
ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

int main() {
    Point p1(3.5, 4.2);
    Point p2(-1.0, 2.5);
    
    cout << "Point 1: " << p1 << endl;  // Uses overloaded <<
    cout << "Point 2: " << p2 << endl;
    
    return 0;
}
// Output:
// Point 1: (3.5, 4.2)
// Point 2: (-1, 2.5)
```

**Why use `friend` for operator overloading?**
- The `<<` operator needs to be called as `cout << object`, not `object.operator<<(cout)`
- A friend function allows access to private members (x and y) without making them public
- It provides cleaner, more intuitive syntax for printing custom types

**Note**: You can also overload the extraction operator (`>>`) using friend functions in the same way:

```cpp
class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    friend ostream& operator<<(ostream& out, const Point& p);
    friend istream& operator>>(istream& in, Point& p);
};

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;  // Access private members
    return in;
}

// ... rest of implementation
```

### Important Note on Friends and Inheritance

```cpp
class Base {
private:
    int x = 10;
    friend class Helper;
};

class Helper {
public:
    void accessBase(Base& b) {
        cout << b.x << endl;  // ✓ OK
    }
    
    void accessDerived(Derived& d) {
        // cout << d.x << endl;  // ✗ Error! Not a friend of Derived
    }
};

class Derived : public Base {
    // Helper is NOT a friend here
};
```

## The Diamond Problem

The diamond problem occurs in multiple inheritance when a derived class inherits from two or more base classes that themselves inherit from a common ancestor. This creates ambiguity: which version of the ancestor's members should be used?

### The Problem Illustrated

```cpp
       Animal  (has: age, speak())
      /      \
    Dog      Cat
      \      /
       Pet
```

```cpp
class Animal {
protected:
    int age;
    
public:
    virtual void describe() {
        cout << "I'm an animal" << endl;
    }
};

class Dog : public Animal {
public:
    void describe() override {
        cout << "I'm a dog" << endl;
    }
};

class Cat : public Animal {
public:
    void describe() override {
        cout << "I'm a cat" << endl;
    }
};

// This is the diamond! Pet inherits from both Dog and Cat
class Pet : public Dog, public Cat {
    // Which Animal::age? Which Animal::describe()?
};

int main() {
    Pet pet;
    
    // Ambiguous! Use scope resolution to resolve:
    pet.Dog::describe();    // Output: I'm a dog
    pet.Cat::describe();    // Output: I'm a cat
    
    // Ambiguous! Multiple copies of Animal::age exist
    // pet.age = 5;          // ✗ Error: ambiguous
    
    return 0;
}
```

### Solution 1: Virtual Inheritance

Use **virtual inheritance** to ensure only one copy of the base class exists in the inheritance hierarchy:

```cpp
class Animal {
protected:
    int age;
    
public:
    Animal() : age(0) {}
    
    virtual void describe() {
        cout << "I'm an animal" << endl;
    }
};

class Dog : virtual public Animal {  // Virtual inheritance
public:
    void describe() override {
        cout << "I'm a dog" << endl;
    }
};

class Cat : virtual public Animal {  // Virtual inheritance
public:
    void describe() override {
        cout << "I'm a cat" << endl;
    }
};

class Pet : public Dog, public Cat {
public:
    Pet() : Animal(), Dog(), Cat() {}
    
    void describe() override {
        cout << "I'm a pet!" << endl;
    }
};

int main() {
    Pet pet;
    pet.describe();  // Output: I'm a pet!
    pet.age = 5;     // ✓ Works! Only one copy of age exists
    
    // Both Dog and Cat use the same Animal::age
    cout << "Age: " << pet.age << endl;  // Output: Age: 5
    
    return 0;
}
```

### Solution 2: Composition Over Inheritance

Often, the diamond problem is a sign that you should reconsider your design. **Composition** is frequently a better approach:

```cpp
class Animal {
protected:
    int age;
    
public:
    virtual void describe() {
        cout << "I'm an animal" << endl;
    }
};

class Dog : public Animal {
public:
    void describe() override {
        cout << "I'm a dog" << endl;
    }
};

class Cat : public Animal {
public:
    void describe() override {
        cout << "I'm a cat" << endl;
    }
};

// Instead of inheriting from both, compose them
class Pet {
private:
    Dog myDog;
    Cat myCat;
    
public:
    void dogAction() {
        myDog.describe();  // Output: I'm a dog
    }
    
    void catAction() {
        myCat.describe();  // Output: I'm a cat
    }
};

int main() {
    Pet pet;
    pet.dogAction();   // Output: I'm a dog
    pet.catAction();   // Output: I'm a cat
    
    return 0;
}
```

## Summary

| Concept | Purpose | Key Points |
|---------|---------|-----------|
| **Inheritance** | Code reuse, establish relationships | Derived class inherits from base class |
| **`virtual`** | Enable runtime polymorphism | Allows correct method to be called based on object type |
| **`override`** | Prevent bugs in overriding | Compiler checks for signature match |
| **`friend`** | Access private/protected members | Not inherited by derived classes |
| **Virtual Inheritance** | Solve diamond problem | Ensures single copy of base class in hierarchy |

## Best Practices

1. **Always use `virtual` destructors** in base classes that will be inherited
2. **Prefer `override`** to catch mistakes at compile time
3. **Use composition over inheritance** when possible—it's often simpler and clearer
4. **Avoid multiple inheritance**—virtual inheritance adds complexity
5. **Be cautious with `friend`**—it violates encapsulation
6. **Keep inheritance hierarchies shallow**—deep hierarchies are hard to maintain
