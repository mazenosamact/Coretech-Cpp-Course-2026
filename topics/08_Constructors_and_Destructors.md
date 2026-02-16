# Constructor and Destructor Syntax

## Summary
Constructors and destructors are special member functions that control object creation and destruction. Constructors initialize member variables and resources, while destructors clean up resources to prevent memory leaks.

## Key Concepts
- **Constructor**: Called when object is created
- **Destructor**: Called when object is destroyed
- **Initialization List**: Efficiently initialize members
- **Default Constructor**: No parameters
- **Parameterized Constructor**: Takes parameters
- **Copy Constructor**: Creates copy of another object

## Code Examples

### Basic Constructor
```cpp
#include <iostream>
using namespace std;

class Student {
private:
    string name;
    int age;
    
public:
    // Default constructor
    Student() {
        name = "Unknown";
        age = 0;
        cout << "Default constructor called" << endl;
    }
    
    // Parameterized constructor
    Student(string n, int a) {
        name = n;
        age = a;
        cout << "Parameterized constructor called" << endl;
    }
    
    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

int main() {
    Student s1;              // Calls default constructor
    Student s2("John", 20);  // Calls parameterized constructor
    
    s1.display();
    s2.display();
    
    return 0;
}
```

### Initialization List
```cpp
#include <iostream>
using namespace std;

class Rectangle {
private:
    double length;
    double width;
    
public:
    // Using initialization list (more efficient)
    Rectangle(double l, double w) : length(l), width(w) {
        cout << "Rectangle created with dimensions " 
             << length << "x" << width << endl;
    }
    
    double getArea() { return length * width; }
};

int main() {
    Rectangle r(5.0, 3.0);
    cout << "Area: " << r.getArea() << endl;
    
    return 0;
}
```

### Basic Destructor
```cpp
#include <iostream>
using namespace std;

class FileHandler {
private:
    string fileName;
    
public:
    FileHandler(string name) : fileName(name) {
        cout << "Opening file: " << fileName << endl;
    }
    
    ~FileHandler() {  // Destructor
        cout << "Closing file: " << fileName << endl;
    }
    
    void display() {
        cout << "File: " << fileName << " is open" << endl;
    }
};

int main() {
    {
        FileHandler fh("data.txt");
        fh.display();
    }  // Destructor called here when fh goes out of scope
    
    cout << "Program ending" << endl;
    
    return 0;
}
```

### Constructor with Dynamic Memory
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char *str;
    
public:
    // Constructor: allocate memory
    String(const char *s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
        cout << "String created: " << str << endl;
    }
    
    // Destructor: free memory
    ~String() {
        cout << "String destroyed: " << str << endl;
        delete[] str;
    }
    
    void display() {
        cout << "Content: " << str << endl;
    }
};

int main() {
    {
        String s1("Hello");
        s1.display();
    }  // Destructor called, memory freed
    
    {
        String s2("World");
        s2.display();
    }  // Destructor called, memory freed
    
    return 0;
}
```

### Multiple Constructors (Overloading)
```cpp
#include <iostream>
using namespace std;

class Circle {
private:
    double radius;
    
public:
    // Default constructor
    Circle() : radius(1.0) {
        cout << "Circle with default radius created" << endl;
    }
    
    // Constructor with radius
    Circle(double r) : radius(r) {
        cout << "Circle with radius " << radius << " created" << endl;
    }
    
    // Copy constructor
    Circle(const Circle &other) : radius(other.radius) {
        cout << "Circle copied" << endl;
    }
    
    double getArea() {
        return 3.14159 * radius * radius;
    }
};

int main() {
    Circle c1;              // Default: 1.0
    Circle c2(5.0);         // Custom: 5.0
    Circle c3(c2);          // Copy: 5.0
    
    cout << "c1 area: " << c1.getArea() << endl;
    cout << "c2 area: " << c2.getArea() << endl;
    cout << "c3 area: " << c3.getArea() << endl;
    
    return 0;
}
```

### Delegating Constructors
```cpp
#include <iostream>
using namespace std;

class Point {
private:
    int x, y;
    
public:
    // Primary constructor
    Point(int px, int py) : x(px), y(py) {
        cout << "Point created at (" << x << ", " << y << ")" << endl;
    }
    
    // Delegating constructor
    Point() : Point(0, 0) {
        cout << "Default point at origin" << endl;
    }
    
    void display() {
        cout << "Position: (" << x << ", " << y << ")" << endl;
    }
};

int main() {
    Point p1;
    Point p2(3, 4);
    
    p1.display();
    p2.display();
    
    return 0;
}
```

### Destructor with Resource Cleanup
```cpp
#include <iostream>
#include <vector>
using namespace std;

class ArrayHandler {
private:
    int *data;
    int size;
    
public:
    ArrayHandler(int s) : size(s) {
        data = new int[size];
        cout << "Array of size " << size << " allocated" << endl;
    }
    
    ~ArrayHandler() {
        delete[] data;
        cout << "Array deallocated" << endl;
    }
    
    void setValue(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }
    
    int getValue(int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return -1;
    }
};

int main() {
    {
        ArrayHandler arr(5);
        arr.setValue(0, 10);
        arr.setValue(1, 20);
        
        cout << "First element: " << arr.getValue(0) << endl;
    }  // Destructor called, memory freed
    
    return 0;
}
```

### Constructor Chaining
```cpp
#include <iostream>
using namespace std;

class Base {
protected:
    string name;
    
public:
    Base(string n) : name(n) {
        cout << "Base constructor: " << name << endl;
    }
};

class Derived : public Base {
private:
    int id;
    
public:
    Derived(string n, int i) : Base(n), id(i) {
        cout << "Derived constructor with id: " << id << endl;
    }
    
    ~Derived() {
        cout << "Derived destructor" << endl;
    }
};

int main() {
    {
        Derived obj("Object", 123);
    }  // Destructors called in reverse order
    
    return 0;
}
```

## Constructor Types
| Type | Purpose |
|------|---------|
| Default | No parameters |
| Parameterized | Takes parameters |
| Copy | Creates copy |
| Move | Moves resources |
| Delegate | Calls another constructor |

## Destructor Rules
- Called automatically when object destroyed
- Called in reverse order of construction for inheritance
- Should free all allocated resources
- Should not be called explicitly (usually)
- Only one destructor per class

## Best Practices
- Always allocate and deallocate in pairs
- Use initialization lists (more efficient)
- Follow RAII (Resource Acquisition Is Initialization)
- Implement destructors when managing resources
