# Function and Operator Overloading

## Summary
Overloading allows you to define multiple functions with the same name but different parameter lists, or multiple operator definitions. The compiler selects the appropriate function based on the arguments provided.

## Key Concepts
- **Function Overloading**: Same name, different parameters
- **Operator Overloading**: Redefine operators for custom types
- **Signature**: Name + parameters (not return type)
- **Ambiguity**: Compiler must find unique match
- **const Overloading**: Different behavior for const/non-const

## Code Examples

### Function Overloading
```cpp
#include <iostream>
using namespace std;

// Overload by parameter count and type
void print(int x) {
    cout << "Integer: " << x << endl;
}

void print(double x) {
    cout << "Double: " << x << endl;
}

void print(string x) {
    cout << "String: " << x << endl;
}

void print(int x, double y) {
    cout << "Int and Double: " << x << ", " << y << endl;
}

int main() {
    print(42);
    print(3.14);
    print("Hello");
    print(10, 2.5);
    
    return 0;
}
```

### Overloading by Parameter Type
```cpp
#include <iostream>
using namespace std;

// Different implementations for different types
int add(int a, int b) {
    cout << "Adding integers" << endl;
    return a + b;
}

double add(double a, double b) {
    cout << "Adding doubles" << endl;
    return a + b;
}

string add(string a, string b) {
    cout << "Concatenating strings" << endl;
    return a + b;
}

int main() {
    cout << "Result: " << add(5, 3) << endl;
    cout << "Result: " << add(2.5, 1.5) << endl;
    cout << "Result: " << add("Hello", " World") << endl;
    
    return 0;
}
```

### Overloading Constructor
```cpp
#include <iostream>
using namespace std;

class Point {
public:
    int x, y;
    
    // Default constructor
    Point() : x(0), y(0) {
        cout << "Default constructor" << endl;
    }
    
    // Constructor with one parameter
    Point(int val) : x(val), y(val) {
        cout << "Single parameter constructor" << endl;
    }
    
    // Constructor with two parameters
    Point(int px, int py) : x(px), y(py) {
        cout << "Two parameter constructor" << endl;
    }
    
    void display() {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    Point p1;           // Default
    Point p2(5);        // Single parameter
    Point p3(3, 4);     // Two parameters
    
    p1.display();
    p2.display();
    p3.display();
    
    return 0;
}
```

### Operator Overloading: Arithmetic
```cpp
#include <iostream>
using namespace std;

class Vector {
public:
    int x, y;
    
    Vector(int px = 0, int py = 0) : x(px), y(py) {}
    
    // Overload + operator
    Vector operator+(const Vector &other) const {
        return Vector(x + other.x, y + other.y);
    }
    
    // Overload - operator
    Vector operator-(const Vector &other) const {
        return Vector(x - other.x, y - other.y);
    }
    
    // Overload * operator (scalar multiplication)
    Vector operator*(int scalar) const {
        return Vector(x * scalar, y * scalar);
    }
    
    void display() {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    Vector v1(3, 4);
    Vector v2(1, 2);
    
    Vector v3 = v1 + v2;
    cout << "v1 + v2: ";
    v3.display();
    
    Vector v4 = v1 - v2;
    cout << "v1 - v2: ";
    v4.display();
    
    Vector v5 = v1 * 2;
    cout << "v1 * 2: ";
    v5.display();
    
    return 0;
}
```

### Operator Overloading: Comparison
```cpp
#include <iostream>
using namespace std;

class Person {
public:
    string name;
    int age;
    
    Person(string n, int a) : name(n), age(a) {}
    
    // Overload == operator
    bool operator==(const Person &other) const {
        return name == other.name && age == other.age;
    }
    
    // Overload != operator
    bool operator!=(const Person &other) const {
        return !(*this == other);
    }
    
    // Overload < operator
    bool operator<(const Person &other) const {
        return age < other.age;
    }
    
    // Overload > operator
    bool operator>(const Person &other) const {
        return age > other.age;
    }
};

int main() {
    Person p1("Alice", 25);
    Person p2("Bob", 25);
    Person p3("Charlie", 30);
    
    cout << "(p1 == p2): " << (p1 == p2) << endl;
    cout << "(p1 != p3): " << (p1 != p3) << endl;
    cout << "(p1 < p3): " << (p1 < p3) << endl;
    cout << "(p3 > p1): " << (p3 > p1) << endl;
    
    return 0;
}
```

### Operator Overloading: Stream Output
```cpp
#include <iostream>
using namespace std;

class Point {
public:
    int x, y;
    
    Point(int px = 0, int py = 0) : x(px), y(py) {}
    
    // Friend function for operator overloading
    friend ostream& operator<<(ostream &out, const Point &p);
    friend istream& operator>>(istream &in, Point &p);
};

// Overload << operator
ostream& operator<<(ostream &out, const Point &p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

// Overload >> operator
istream& operator>>(istream &in, Point &p) {
    cout << "Enter x and y: ";
    in >> p.x >> p.y;
    return in;
}

int main() {
    Point p1(3, 4);
    cout << "Point: " << p1 << endl;
    
    Point p2;
    cin >> p2;
    cout << "You entered: " << p2 << endl;
    
    return 0;
}
```

### Operator Overloading: Increment/Decrement
```cpp
#include <iostream>
using namespace std;

class Counter {
private:
    int value;
    
public:
    Counter(int v = 0) : value(v) {}
    
    // Pre-increment (++counter)
    Counter& operator++() {
        ++value;
        return *this;
    }
    
    // Post-increment (counter++)
    Counter operator++(int) {
        Counter temp = *this;
        value++;
        return temp;
    }
    
    // Pre-decrement (--counter)
    Counter& operator--() {
        --value;
        return *this;
    }
    
    int getValue() const { return value; }
};

int main() {
    Counter c(5);
    
    cout << "Original: " << c.getValue() << endl;
    
    ++c;  // Pre-increment
    cout << "After ++c: " << c.getValue() << endl;
    
    c++;  // Post-increment
    cout << "After c++: " << c.getValue() << endl;
    
    return 0;
}
```

### Operator Overloading: Assignment
```cpp
#include <iostream>
using namespace std;

class Array {
private:
    int *data;
    int size;
    
public:
    Array(int s) : size(s) {
        data = new int[size];
    }
    
    ~Array() {
        delete[] data;
    }
    
    // Overload assignment operator
    Array& operator=(const Array &other) {
        if (this == &other) return *this;  // Self-assignment check
        
        delete[] data;
        size = other.size;
        data = new int[size];
        
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        
        return *this;
    }
    
    int& operator[](int index) {
        return data[index];
    }
};

int main() {
    Array arr1(5);
    arr1[0] = 10;
    arr1[1] = 20;
    
    Array arr2(5);
    arr2 = arr1;  // Uses overloaded assignment
    
    return 0;
}
```

### Operator Overloading: Function Call
```cpp
#include <iostream>
using namespace std;

class Multiplier {
private:
    int factor;
    
public:
    Multiplier(int f) : factor(f) {}
    
    // Overload function call operator
    int operator()(int x) const {
        return x * factor;
    }
};

int main() {
    Multiplier mult2(2);
    Multiplier mult3(3);
    
    cout << "mult2(5) = " << mult2(5) << endl;  // 10
    cout << "mult3(5) = " << mult3(5) << endl;  // 15
    
    return 0;
}
```

### Operator Overloading: Subscript
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
    vector<vector<int>> data;
    int rows, cols;
    
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data.resize(r, vector<int>(c, 0));
    }
    
    // Overload subscript operator
    int& operator[](int index) {
        return data[0][index];
    }
};

int main() {
    Matrix m(2, 3);
    
    m[0] = 10;
    m[1] = 20;
    m[2] = 30;
    
    cout << "m[0]: " << m[0] << endl;
    cout << "m[1]: " << m[1] << endl;
    
    return 0;
}
```

## Operators That Cannot Be Overloaded
- `::` (Scope resolution)
- `.` (Member access)
- `.*` (Pointer to member)
- `?:` (Ternary)
- `sizeof` (Size of)

## Best Practices
1. Overload operators that make semantic sense
2. Maintain expected behavior (e.g., `+` should not subtract)
3. Use const references for parameters when appropriate
4. Implement `return *this` for chaining operations
5. Check for self-assignment in assignment operators
6. Use friend functions for binary operators
