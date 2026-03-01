#ifndef TEST_INHERITANCE_H
#define TEST_INHERITANCE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <array>
#include <variant>

using namespace std;


#if 0

// Abstract class (Interface)
class SerialInterface
{
public:
    // Serialization
    virtual void send(uint8_t* arr, int size ) =0;
    virtual void setRawData(uint8_t* arr, int size ) =0;
    virtual int  recv(uint8_t* arr, int size ) =0;
    virtual void init() =0;

};

struct CUartConfig{};

class CUart : public SerialInterface
{
    const CUartConfig& m_config;
public:
    CUart(const CUartConfig& config  ):m_config(config){}

    
    // 1. send(..., 10);
    // 2. arr[10] = {...};
    //    setRawData(arr, 10);
    //    send();
    virtual void send(uint8_t* arr=nullptr, int size=0 ) override
    {

    }
    virtual void setRawData(uint8_t* arr, int size ) override
    {

    }

    virtual int  recv(uint8_t* arr, int size ) override
    {

    }

    virtual void init() override
    {

    }
};



class Sensor
{
    int m_unit;
    double* m_readings;
    SerialInterface* m_communication;
public: 
    Sensor(int unit, double* readings_arr):
    m_unit(unit), m_readings(readings_arr)
    {

    }

    int setCommInterface(SerialInterface* comm)
    {
        if(comm != nullptr)
        {
            m_communication = comm ;
        }
    }
};

class TemperatureSensor : public Sensor
{
    std::array<double, 10> m_tempReadings;
public:
    TemperatureSensor(int unit):Sensor(unit, m_tempReadings.data()){}
};


class LightSensor : public Sensor
{
public:
};




#endif



// ============================================================================
// 1. Basic Inheritance Example
// ============================================================================
#if 0

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

int test_inheritance_main() {
    Dog myDog("Canine", "Golden Retriever");
    myDog.describe();      // Inherited method
    myDog.showBreed();     // Derived class method
    return 0;
}
// Output:
// This is a Canine
// Breed: Golden Retriever

#endif

// ============================================================================
// 2. Overriding Without Virtual (Static Binding)
// ============================================================================
#if 0

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

int test_inheritance_main() {
    Animal* animalPtr;
    Dog dog;
    
    animalPtr = &dog;
    animalPtr->speak();  // Calls Animal::speak(), not Dog::speak()
    // Output: Some generic sound
    
    dog.speak();         // Calls Dog::speak()
    // Output: Woof!
    
    return 0;
}

#endif

// ============================================================================
// 3. Virtual Overriding Example
// ============================================================================
#if 0

class Animal {
public:
    virtual void speak() {  // Virtual method
        cout << "Some generic sound" << endl;
    }
    
    virtual ~Animal() {}    // Virtual destructor (important!)
};

class Dog : public Animal {
public:
    virtual void speak() override {  // Overrides virtual method
        cout << "Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        cout << "Meow!" << endl;
    }
};
// address-sanitizer (asan), valgrind
int test_inheritance_main() {
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

#endif

// ============================================================================
// 4. Override Keyword Example
// ============================================================================
#if 0

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

#endif

// ============================================================================
// 5. Non-Virtual Destructors and Memory Leaks (Problem)
// ============================================================================
#if 0

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

int test_inheritance_main() {
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

#endif

// ============================================================================
// 6. Virtual Destructors (Solution)
// ============================================================================
#if 0

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
    
    virtual ~Dog() override {  // ✓ Destructor is properly called
        cout << "Dog destructor - freeing breed_name" << endl;
        delete[] breed_name;
    }
};

int test_inheritance_main() {
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

#endif

// ============================================================================
// 7. Function Overloading (Static Polymorphism)
// ============================================================================
#if 0

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

int test_inheritance_main() {
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

#endif

// ============================================================================
// 8. Template Polymorphism (Static Polymorphism)
// ============================================================================
#if 0

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

int test_inheritance_main() {
    Container<int> intContainer;
    intContainer.set(42);
    cout << intContainer.get() << endl;  // Output: 42
    
    Container<string> strContainer;
    strContainer.set("Hello");
    cout << strContainer.get() << endl;  // Output: Hello
    
    return 0;
}

#endif

// ============================================================================
// 9. Virtual Functions (Dynamic Polymorphism)
// ============================================================================
#if 0

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

int test_inheritance_main() {
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

#endif

// ============================================================================
// 10. CRTP Basic Pattern
// ============================================================================
#if 0

template<typename T>
class Base {
public:
    void operation() {
        // Call the derived class's implementation at compile time
        static_cast<T*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        cout << "Derived implementation" << endl;
    }
};

int test_inheritance_main() {
    Derived obj;
    obj.operation();  // Calls Derived::implementation() at compile time
    return 0;
}
// Output: Derived implementation

#endif

// ============================================================================
// 11. CRTP Practical Example: Data Processing
// ============================================================================
#if 0

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

int test_inheritance_main() {
    IntProcessor intProc;
    StringProcessor strProc;
    
    executeProcessor(intProc);   // Output: Processing integers
    executeProcessor(strProc);   // Output: Processing strings
    
    return 0;
}

#endif

// ============================================================================
// 12. CRTP Embedded Systems: Sensor Interface
// ============================================================================
#if 0

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

int test_inheritance_main() {
    TemperatureSensor tempSensor(0, 0.5f);  // Using 0 instead of A0
    PressureSensor pressureSensor(1, 1.0f); // Using 1 instead of A1
    
    // using ComplexSensorType = std::variant<TemperatureSensor,PressureSensor> ;

    // std::vector<ComplexSensorType> sensorList ;
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

#endif

// ============================================================================
// 13. Hybrid Approach: Template Base Class
// ============================================================================
#if 0

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

#endif

// ============================================================================
// 14. Hybrid Approach: Virtual Interface
// ============================================================================
#if 0

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

#endif

// ============================================================================
// 15. Friend Class Example
// ============================================================================
#if 0
class Base {
private:
    int secret = 42;
    
    friend class MyFriend;  // MyFriend can access private members
};

class MyFriend {
public:
    void revealSecret(Base& b) {
        cout << "Base's secret: " << b.secret << endl;
    }
    void revealSecret(DerivedClass& d) {
        cout << "Base's secret: " << d.secret << endl;
    }
};

class DerivedClass : public Base {
    // MyFriend is NOT a friend here!
    // This would be an error: cout << b.secret;
};

int test_inheritance_main() {
    Base b;
    MyFriend fc;
    fc.revealSecret(b);  // ✓ Works
    return 0;
}

#endif

// ============================================================================
// 16. Friend Function Example
// ============================================================================
#if 1

class MyClass {
private:
    int data = 100;
    
    friend void printData(MyClass& obj);  // Friend function
};

void printData(MyClass& obj) {
    cout << "Data: " << obj.data << endl;  // Can access private members
}

int test_inheritance_main() {
    MyClass obj;
    printData(obj);  // ✓ Works
    return 0;
}
// Output: Data: 100

#endif

// ============================================================================
// 17. Friend Operator Overloading: Stream Insertion
// ============================================================================
#if 0

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

int test_inheritance_main() {
    Point p1(3.5, 4.2);
    Point p2(-1.0, 2.5);
    
    cout << "Point 1: " << p1 << endl;  // Uses overloaded <<
    cout << "Point 2: " << p2 << endl;
    
    return 0;
}
// Output:
// Point 1: (3.5, 4.2)
// Point 2: (-1, 2.5)

#endif

// ============================================================================
// 18. Friend Operator Overloading: Stream Extraction
// ============================================================================
#if 0

class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    friend ostream& operator<<(ostream& out, const Point& p);
    friend istream& operator>>(istream& in, Point& p);
};

ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;  // Access private members
    return in;
}

#endif

// ============================================================================
// 19. Friends and Inheritance
// ============================================================================
#if 0

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
    
    void accessDerived(Base& d) {
        // cout << d.x << endl;  // ✗ Error! Not a friend of Derived
    }
};

class Derived : public Base {
    // Helper is NOT a friend here
};

#endif

// ============================================================================
// 20. Diamond Problem Illustration
// ============================================================================
#if 1

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

int test_inheritance_main() {
    Pet pet;
    
    // Ambiguous! Use scope resolution to resolve:
    pet.Dog::describe();    // Output: I'm a dog
    pet.Cat::describe();    // Output: I'm a cat
    
    // Ambiguous! Multiple copies of Animal::age exist
    // pet.age = 5;          // ✗ Error: ambiguous
    
    return 0;
}

#endif

// ============================================================================
// 21. Virtual Inheritance Solution
// ============================================================================
#if 0

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

int test_inheritance_main() {
    Pet pet;
    pet.describe();  // Output: I'm a pet!
    pet.age = 5;     // ✓ Works! Only one copy of age exists
    
    // Both Dog and Cat use the same Animal::age
    cout << "Age: " << pet.age << endl;  // Output: Age: 5
    
    return 0;
}

#endif

// ============================================================================
// 22. Composition Over Inheritance Solution
// ============================================================================
#if 0

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

int test_inheritance_main() {
    Pet pet;
    pet.dogAction();   // Output: I'm a dog
    pet.catAction();   // Output: I'm a cat
    
    return 0;
}

#endif

#endif // TEST_INHERITANCE_H
