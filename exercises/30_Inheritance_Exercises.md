# Inheritance - Practical Exercises

## Exercise 1: Base Class and Derived Class (Code Reuse)
**Context:** Create an inheritance hierarchy for different animal types.

**Problem:**
```cpp
// Implement inheritance:
// 1. Base class with common functionality
// 2. Derived classes with specialization
// 3. Constructor/destructor chaining
// 4. Method override
// 5. Access control (public/protected/private)
```

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(const string &n, int a) : name(n), age(a) {
        cout << "✓ Animal constructor: " << name << endl;
    }
    
    virtual ~Animal() {
        cout << "✓ Animal destructor: " << name << endl;
    }
    
    virtual void speak() const {
        cout << name << " makes generic sound" << endl;
    }
    
    virtual void move() const {
        cout << name << " is moving" << endl;
    }
    
    void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

class Dog : public Animal {  // Public inheritance
public:
    Dog(const string &n, int a) : Animal(n, a) {
        cout << "  ✓ Dog constructor" << endl;
    }
    
    ~Dog() {
        cout << "  ✓ Dog destructor" << endl;
    }
    
    void speak() const override {
        cout << name << " barks: WOOF!" << endl;
    }
    
    void move() const override {
        cout << name << " runs on four legs" << endl;
    }
    
    void fetch() {
        cout << name << " fetches the ball" << endl;
    }
};

class Bird : public Animal {
public:
    Bird(const string &n, int a) : Animal(n, a) {
        cout << "  ✓ Bird constructor" << endl;
    }
    
    ~Bird() {
        cout << "  ✓ Bird destructor" << endl;
    }
    
    void speak() const override {
        cout << name << " chirps: TWEET TWEET!" << endl;
    }
    
    void move() const override {
        cout << name << " flies through the air" << endl;
    }
};

int main() {
    cout << "=== Inheritance: Base and Derived Classes ===" << endl;
    
    cout << "\n--- Creating Dog ---" << endl;
    Dog dog("Buddy", 5);
    dog.displayInfo();
    dog.speak();
    dog.move();
    dog.fetch();
    
    cout << "\n--- Creating Bird ---" << endl;
    Bird bird("Tweety", 2);
    bird.displayInfo();
    bird.speak();
    bird.move();
    
    cout << "\n--- Using through base class pointer ---" << endl;
    Animal *animals[] = {&dog, &bird};
    
    for (Animal *animal : animals) {
        animal->speak();
        animal->move();
        cout << endl;
    }
    
    cout << "\n--- Destructors called ---" << endl;
    
    return 0;
}
```

---

## Exercise 2: Multiple Inheritance (Complex Hierarchies)
**Context:** Class inheriting from multiple base classes.

**Problem:**
```cpp
// Multiple inheritance:
// 1. Multiple base classes
// 2. Method resolution order
// 3. Diamond problem
// 4. Virtual inheritance
// 5. Interface design
```

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Drawable {
public:
    virtual void draw() const {
        cout << "Drawing shape" << endl;
    }
};

class Resizable {
public:
    virtual void resize(double factor) {
        cout << "Resizing by factor " << factor << endl;
    }
};

class Shape : public Drawable, public Resizable {
protected:
    string name;
    
public:
    Shape(const string &n) : name(n) {
        cout << "✓ Shape created: " << name << endl;
    }
    
    virtual ~Shape() {
        cout << "✓ Shape destroyed" << endl;
    }
    
    virtual double getArea() const = 0;  // Pure virtual
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : Shape("Circle"), radius(r) {
        cout << "  ✓ Circle created with radius " << r << endl;
    }
    
    void draw() const override {
        cout << "Drawing circle with radius " << radius << endl;
    }
    
    void resize(double factor) override {
        radius *= factor;
        cout << "Circle resized to radius " << radius << endl;
    }
    
    double getArea() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : Shape("Rectangle"), width(w), height(h) {
        cout << "  ✓ Rectangle created: " << w << "x" << h << endl;
    }
    
    void draw() const override {
        cout << "Drawing rectangle " << width << "x" << height << endl;
    }
    
    void resize(double factor) override {
        width *= factor;
        height *= factor;
        cout << "Rectangle resized to " << width << "x" << height << endl;
    }
    
    double getArea() const override {
        return width * height;
    }
};

int main() {
    cout << "=== Inheritance: Multiple Inheritance ===" << endl;
    
    cout << "\n--- Creating shapes ---" << endl;
    Circle c(5.0);
    Rectangle r(4.0, 3.0);
    
    cout << "\n--- Using through Shape interface ---" << endl;
    Shape *shapes[] = {&c, &r};
    
    for (Shape *shape : shapes) {
        shape->draw();
        cout << "Area: " << shape->getArea() << endl;
        shape->resize(2.0);
        cout << endl;
    }
    
    cout << "\n✓ Multiple inheritance complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Polymorphism (Virtual Functions)
**Context:** Implement data processor with different strategies.

**Problem:**
```cpp
// Polymorphic design:
// 1. Pure virtual functions
// 2. Virtual function overrides
// 3. Runtime dispatch
// 4. Factory pattern
// 5. Strategy pattern
```

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// Abstract base class
class DataProcessor {
public:
    virtual ~DataProcessor() = default;
    
    virtual string getName() const = 0;
    virtual string process(const string &input) = 0;
};

class JSONProcessor : public DataProcessor {
public:
    string getName() const override {
        return "JSON Processor";
    }
    
    string process(const string &input) override {
        cout << "Processing as JSON..." << endl;
        return "{\"processed\": \"" + input + "\"}";
    }
};

class XMLProcessor : public DataProcessor {
public:
    string getName() const override {
        return "XML Processor";
    }
    
    string process(const string &input) override {
        cout << "Processing as XML..." << endl;
        return "<root><data>" + input + "</data></root>";
    }
};

class CSVProcessor : public DataProcessor {
public:
    string getName() const override {
        return "CSV Processor";
    }
    
    string process(const string &input) override {
        cout << "Processing as CSV..." << endl;
        return "col1,col2,col3\n" + input;
    }
};

// Factory function
unique_ptr<DataProcessor> createProcessor(const string &type) {
    if (type == "json") {
        return make_unique<JSONProcessor>();
    } else if (type == "xml") {
        return make_unique<XMLProcessor>();
    } else if (type == "csv") {
        return make_unique<CSVProcessor>();
    }
    return nullptr;
}

int main() {
    cout << "=== Inheritance: Polymorphism ===" << endl;
    
    cout << "\n--- Creating processors ---" << endl;
    vector<unique_ptr<DataProcessor>> processors;
    
    processors.push_back(createProcessor("json"));
    processors.push_back(createProcessor("xml"));
    processors.push_back(createProcessor("csv"));
    
    cout << "\n--- Processing data polymorphically ---" << endl;
    string data = "Hello World";
    
    for (auto &processor : processors) {
        cout << "\nUsing: " << processor->getName() << endl;
        string result = processor->process(data);
        cout << "Result: " << result << endl;
    }
    
    cout << "\n--- Single responsibility ---" << endl;
    cout << "Each processor handles only its format" << endl;
    cout << "Client code doesn't know implementation details" << endl;
    cout << "Easy to add new processor types" << endl;
    
    cout << "\n✓ Polymorphism complete" << endl;
    
    return 0;
}
```
