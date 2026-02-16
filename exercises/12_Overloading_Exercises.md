# Function and Operator Overloading - Practical Exercises

## Exercise 1: Function Overloading (Embedded Systems Math)
**Context:** Create flexible mathematical operations that work with different data types.

**Problem:**
```cpp
// Implement overloaded functions:
// 1. abs() - absolute value for int, float, double
// 2. max() - maximum of int, float, double
// 3. min() - minimum for different types
// 4. show compile-time resolution
```

**Solution:**
```cpp
#include <iostream>
#include <cmath>
using namespace std;

// Overloaded abs function
int abs(int x) {
    return (x < 0) ? -x : x;
}

float abs(float x) {
    return (x < 0.0f) ? -x : x;
}

double abs(double x) {
    return (x < 0.0) ? -x : x;
}

// Overloaded max function
int max(int a, int b) {
    return (a > b) ? a : b;
}

float max(float a, float b) {
    return (a > b) ? a : b;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}

// Overloaded min function
int min(int a, int b) {
    return (a < b) ? a : b;
}

float min(float a, float b) {
    return (a < b) ? a : b;
}

int main() {
    cout << "=== Function Overloading ===" << endl;
    
    cout << "\n--- Absolute values ---" << endl;
    cout << "abs(-42): " << abs(-42) << endl;
    cout << "abs(-3.14f): " << abs(-3.14f) << endl;
    cout << "abs(-2.718): " << abs(-2.718) << endl;
    
    cout << "\n--- Maximum values ---" << endl;
    cout << "max(10, 20): " << max(10, 20) << endl;
    cout << "max(3.5f, 2.5f): " << max(3.5f, 2.5f) << endl;
    cout << "max(1.1, 2.2): " << max(1.1, 2.2) << endl;
    
    cout << "\n--- Minimum values ---" << endl;
    cout << "min(100, 50): " << min(100, 50) << endl;
    cout << "min(5.5f, 4.5f): " << min(5.5f, 4.5f) << endl;
    
    cout << "\n✓ Compiler chose correct overloaded function" << endl;
    
    return 0;
}
```

---

## Exercise 2: Operator Overloading (Vector Operations)
**Context:** Implement vector math with intuitive operators.

**Problem:**
```cpp
// Vector class with:
// 1. operator+ (addition)
// 2. operator- (subtraction)
// 3. operator* (scalar multiplication)
// 4. operator== (comparison)
// 5. operator<< (output)
```

**Solution:**
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Vector {
private:
    float x, y, z;
    
public:
    Vector(float x_ = 0, float y_ = 0, float z_ = 0) 
        : x(x_), y(y_), z(z_) {}
    
    // Vector addition
    Vector operator+(const Vector &v) const {
        return Vector(x + v.x, y + v.y, z + v.z);
    }
    
    // Vector subtraction
    Vector operator-(const Vector &v) const {
        return Vector(x - v.x, y - v.y, z - v.z);
    }
    
    // Scalar multiplication
    Vector operator*(float scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }
    
    // Dot product
    float operator*(const Vector &v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    
    // Equality comparison
    bool operator==(const Vector &v) const {
        return (x == v.x && y == v.y && z == v.z);
    }
    
    // Magnitude
    float magnitude() const {
        return sqrt(x*x + y*y + z*z);
    }
    
    // Stream output
    friend ostream &operator<<(ostream &os, const Vector &v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

// Helper for scalar * Vector
Vector operator*(float scalar, const Vector &v) {
    return v * scalar;
}

int main() {
    cout << "=== Operator Overloading ===" << endl;
    
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);
    
    cout << "\n--- Vector operations ---" << endl;
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    
    Vector v3 = v1 + v2;
    cout << "v1 + v2 = " << v3 << endl;
    
    Vector v4 = v2 - v1;
    cout << "v2 - v1 = " << v4 << endl;
    
    Vector v5 = v1 * 2.0f;
    cout << "v1 * 2 = " << v5 << endl;
    
    float dot = v1 * v2;
    cout << "v1 · v2 = " << dot << endl;
    
    cout << "\n--- Comparison ---" << endl;
    cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << endl;
    Vector v1_copy = v1;
    cout << "v1 == v1_copy: " << (v1 == v1_copy ? "true" : "false") << endl;
    
    cout << "\n--- Magnitude ---" << endl;
    cout << "Magnitude of v1: " << v1.magnitude() << endl;
    
    return 0;
}
```

---

## Exercise 3: Complex Stream Operations (I/O Overloading)
**Context:** Read and write custom objects from/to files.

**Problem:**
```cpp
// Overload operators for:
// 1. Stream input (>>)
// 2. Stream output (<<)
// 3. Handle formatting
// 4. File I/O integration
```

**Solution:**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;
    string email;
    
public:
    Person() : age(0) {}
    Person(const string &n, int a, const string &e) 
        : name(n), age(a), email(e) {}
    
    // Stream output operator
    friend ostream &operator<<(ostream &os, const Person &p) {
        os << p.name << " (" << p.age << ") - " << p.email;
        return os;
    }
    
    // Stream input operator
    friend istream &operator>>(istream &is, Person &p) {
        cout << "Enter name: ";
        getline(is, p.name);
        cout << "Enter age: ";
        is >> p.age;
        is.ignore();  // Clear newline
        cout << "Enter email: ";
        getline(is, p.email);
        return is;
    }
    
    string getName() const { return name; }
};

int main() {
    cout << "=== Stream Operator Overloading ===" << endl;
    
    cout << "\n--- Creating objects and writing to file ---" << endl;
    Person p1("Alice Smith", 30, "alice@example.com");
    Person p2("Bob Johnson", 28, "bob@example.com");
    
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    
    // Write to file
    ofstream outfile("people.txt");
    outfile << p1 << endl;
    outfile << p2 << endl;
    outfile.close();
    cout << "\n✓ Data written to people.txt" << endl;
    
    cout << "\n--- Reading from file ---" << endl;
    ifstream infile("people.txt");
    string line;
    while (getline(infile, line)) {
        cout << "From file: " << line << endl;
    }
    infile.close();
    
    cout << "\n✓ File I/O with operators complete" << endl;
    
    return 0;
}
```
