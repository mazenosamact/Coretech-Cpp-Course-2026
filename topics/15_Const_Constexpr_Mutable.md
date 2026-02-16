# const vs constexpr vs mutable

## Summary
`const`, `constexpr`, and `mutable` are keywords that control how variables and member variables can be modified. `const` creates read-only variables, `constexpr` enables compile-time evaluation, and `mutable` allows modification in const functions.

## Key Concepts
- **const**: Runtime constant, cannot be modified
- **constexpr**: Compile-time constant, optimized evaluation
- **mutable**: Allows modification even in const member functions
- **const member**function: Cannot modify object state
- **const correctness**: Proper use prevents accidental modifications

## Code Examples

### Basic const Variables
```cpp
#include <iostream>
using namespace std;

int main() {
    // const variable - runtime constant
    const int MAX_SIZE = 100;
    const float PI = 3.14159f;
    
    cout << "MAX_SIZE: " << MAX_SIZE << endl;
    cout << "PI: " << PI << endl;
    
    // MAX_SIZE = 200;  // ERROR: cannot modify const
    
    // const with pointers
    const int *ptr1;        // Pointer to const int
    int *const ptr2;        // const pointer to int
    const int *const ptr3;  // const pointer to const int
    
    return 0;
}
```

### const Member Functions
```cpp
#include <iostream>
using namespace std;

class Rectangle {
private:
    double length, width;
    
public:
    Rectangle(double l, double w) : length(l), width(w) {}
    
    // const member function - cannot modify member variables
    double getArea() const {
        return length * width;  // OK: reading
        // length = 10;  // ERROR: modifying in const function
    }
    
    // Non-const member function
    void resize(double l, double w) {
        length = l;
        width = w;
    }
    
    // const reference cannot call non-const functions
    void display() const {
        cout << "Length: " << length << ", Width: " << width << endl;
    }
};

int main() {
    const Rectangle r(5.0, 3.0);
    
    cout << "Area: " << r.getArea() << endl;      // OK: const function
    r.display();                                   // OK: const function
    // r.resize(10, 8);  // ERROR: cannot call non-const function
    
    return 0;
}
```

### constexpr for Compile-time Constants
```cpp
#include <iostream>
using namespace std;

// constexpr function - can be evaluated at compile time
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr float circleArea(float radius) {
    return 3.14159f * radius * radius;
}

int main() {
    // Evaluated at compile time
    constexpr int fact5 = factorial(5);
    constexpr float area = circleArea(3.0f);
    
    cout << "5! = " << fact5 << endl;
    cout << "Area of radius 3: " << area << endl;
    
    // Can also be evaluated at runtime
    int n = 4;
    cout << "4! = " << factorial(n) << endl;
    
    return 0;
}
```

### constexpr Variables
```cpp
#include <iostream>
#include <array>
using namespace std;

// constexpr variable
constexpr int SIZE = 10;
constexpr double E = 2.71828;

// Can use constexpr in compile-time contexts
array<int, SIZE> arr;  // SIZE known at compile time

constexpr int square(int x) {
    return x * x;
}

constexpr int AREA = square(5);  // Evaluated at compile time

int main() {
    cout << "SIZE: " << SIZE << endl;
    cout << "5 squared: " << AREA << endl;
    
    // Arrays and runtime initialization
    constexpr int arr_size = 20;
    int runtime_arr[arr_size];
    
    return 0;
}
```

### mutable Member Variables
```cpp
#include <iostream>
using namespace std;

class Cache {
private:
    int value;
    mutable int cached_value;
    mutable bool cached;
    
public:
    Cache(int v) : value(v), cached_value(0), cached(false) {}
    
    // const function that modifies mutable members
    int getValue() const {
        if (!cached) {
            // Can modify mutable members even in const function
            cached_value = value * 2;
            cached = true;
            cout << "Computing value..." << endl;
        }
        return cached_value;
    }
    
    void setValue(int v) {
        value = v;
        cached = false;  // Invalidate cache
    }
};

int main() {
    const Cache c(10);
    
    cout << "First call: " << c.getValue() << endl;   // Computes
    cout << "Second call: " << c.getValue() << endl;  // Uses cache
    
    return 0;
}
```

### const Pointers and References
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10, y = 20;
    
    // Pointer to const - cannot change pointed value
    const int *ptr1 = &x;
    cout << "*ptr1: " << *ptr1 << endl;
    // *ptr1 = 15;  // ERROR
    ptr1 = &y;  // OK: can change pointer itself
    
    // Const pointer - cannot change pointer, can change value
    int *const ptr2 = &x;
    cout << "*ptr2: " << *ptr2 << endl;
    *ptr2 = 15;  // OK: can change value
    // ptr2 = &y;  // ERROR
    
    // Const pointer to const - cannot change either
    const int *const ptr3 = &x;
    cout << "*ptr3: " << *ptr3 << endl;
    // *ptr3 = 15;  // ERROR
    // ptr3 = &y;   // ERROR
    
    // Const reference - cannot change referred value
    const int &ref = x;
    cout << "ref: " << ref << endl;
    // ref = 15;  // ERROR
    
    return 0;
}
```

### Function Parameters with const
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pass const reference to avoid copying
void printVector(const vector<int> &v) {
    for (int val : v) {
        cout << val << " ";
    }
    cout << endl;
}

// const pointer parameter
void printString(const string *str) {
    if (str) {
        cout << *str << endl;
    }
}

// Non-const reference allows modification
void modifyValue(int &val) {
    val *= 2;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    printVector(nums);
    
    string name = "Alice";
    printString(&name);
    
    int x = 10;
    modifyValue(x);
    cout << "Modified x: " << x << endl;
    
    return 0;
}
```

### Method Overloading with const
```cpp
#include <iostream>
using namespace std;

class Data {
private:
    string value;
    
public:
    Data(string v) : value(v) {}
    
    // const version - for const objects
    const string& getValue() const {
        cout << "const version called" << endl;
        return value;
    }
    
    // non-const version - for mutable objects
    string& getValue() {
        cout << "non-const version called" << endl;
        return value;
    }
};

int main() {
    Data d("Hello");
    d.getValue();  // Calls non-const version
    
    const Data cd("World");
    cd.getValue();  // Calls const version
    
    return 0;
}
```

### constexpr vs const
```cpp
#include <iostream>
using namespace std;

// const - always runtime
const int CONST_VAL = 100;

// constexpr - can be compile-time
constexpr int CONSTEXPR_VAL = 200;

// constexpr function
constexpr int getConst() {
    return 300;
}

// regular function
int getRegular() {
    return 400;
}

int main() {
    // All these are compile-time constants
    int arr1[CONST_VAL];
    int arr2[CONSTEXPR_VAL];
    int arr3[getConst()];
    
    // This requires runtime-evaluated variable
    // int arr4[getRegular()];  // ERROR
    
    cout << "CONST_VAL: " << CONST_VAL << endl;
    cout << "CONSTEXPR_VAL: " << CONSTEXPR_VAL << endl;
    cout << "getConst(): " << getConst() << endl;
    
    return 0;
}
```

### mutable in Lambda Captures
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5;
    
    // Lambda capturing by value is const by default
    auto lambda = [x]() mutable {
        x = x * 2;  // OK with mutable
        cout << "Inside: " << x << endl;
    };
    
    lambda();
    cout << "Outside: " << x << endl;  // x still 5
    
    return 0;
}
```

## const Correctness Rules
```cpp
#include <iostream>
using namespace std;

class Example {
private:
    int data;
    
public:
    Example(int d) : data(d) {}
    
    // Read-only access
    int getData() const {
        return data;
    }
    
    // Modification
    void setData(int d) {
        data = d;
    }
    
    // Const reference parameter
    void copy(const Example &other) {
        data = other.getData();
    }
};

int main() {
    Example e(10);
    e.setData(20);
    cout << "Data: " << e.getData() << endl;
    
    const Example ce(30);
    cout << "Const data: " << ce.getData() << endl;
    // ce.setData(40);  // ERROR: cannot call non-const on const object
    
    return 0;
}
```

## Quick Reference Table
| Keyword | Use Case | Can Modify |
|---------|----------|-----------|
| `const` | Read-only variable | No |
| `constexpr` | Compile-time constant | No |
| `mutable` | Non-static data member modifiable in const functions | Yes |
| `const` member | Function cannot modify object | No |

## Best Practices
1. Mark member functions `const` if they don't modify state
2. Use `const` references to avoid unnecessary copying
3. Use `constexpr` for compile-time optimization
4. Use `mutable` sparingly (for caching, etc.)
5. Apply const-correctness throughout your code
6. Return `const` references from accessor functions
