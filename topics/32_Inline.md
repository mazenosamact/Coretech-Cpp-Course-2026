# Inline Keyword

## Summary
The `inline` keyword is a compiler hint suggesting that a function's code be substituted directly at the call site rather than using a function call. Modern compilers usually ignore the keyword and decide automatically, but it's useful for templates and documentation. Overuse can increase code size.

## Key Concepts
- **Compiler Hint**: Not a mandatory directive
- **Code Substitution**: Replaces function call with function body
- **Reduce Overhead**: Eliminates function call stack operations
- **Increase Binary Size**: Multiple copies of function code
- **Template Functions**: Implicitly inline
- **Modern Compilers**: Auto-inline optimization

## Code Examples

### Basic inline Function
```cpp
#include <iostream>
using namespace std;

// Inline function definition
inline int add(int a, int b) {
    return a + b;
}

int main() {
    // Compiler may substitute: result = 5 + 3
    int result = add(5, 3);
    cout << "5 + 3 = " << result << endl;
    
    return 0;
}
```

### Without inline (For Comparison)
```cpp
#include <iostream>
using namespace std;

// Regular function
int multiply(int a, int b) {
    return a * b;
}

int main() {
    // Compiler generates function call
    int result = multiply(5, 3);
    cout << "5 * 3 = " << result << endl;
    
    return 0;
}
```

### Inline Member Functions
```cpp
#include <iostream>
using namespace std;

class Point {
private:
    double x, y;
    
public:
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    
    // Inline function (defined in class)
    double getX() const {
        return x;
    }
    
    double getY() const {
        return y;
    }
    
    // Inline function (explicit keyword)
    inline double distance() const {
        return sqrt(x * x + y * y);
    }
};

int main() {
    Point p(3, 4);
    cout << "X: " << p.getX() << ", Y: " << p.getY() << endl;
    
    return 0;
}
```

### Inline Class Methods (Separate Definition)
```cpp
#include <iostream>
using namespace std;

class Rectangle {
private:
    double width, height;
    
public:
    Rectangle(double w, double h);
    
    inline double area() const;  // Declaration
};

// Definition marked inline
inline double Rectangle::area() const {
    return width * height;
}

Rectangle::Rectangle(double w, double h) : width(w), height(h) {}

int main() {
    Rectangle r(5, 3);
    cout << "Area: " << r.area() << endl;
    
    return 0;
}
```

### Template Functions (Implicitly inline)
```cpp
#include <iostream>
#include <string>
using namespace std;

// Template functions are implicitly inline
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    cout << "Max of 5 and 3: " << maximum(5, 3) << endl;
    cout << "Max of 3.14 and 2.71: " << maximum(3.14, 2.71) << endl;
    cout << "Max of 'apple' and 'zebra': " 
         << maximum("apple", "zebra") << endl;
    
    return 0;
}
```

### Inline with Default Arguments
```cpp
#include <iostream>
using namespace std;

inline int power(int base, int exp = 2) {
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

int main() {
    cout << "2^2: " << power(2) << endl;
    cout << "2^3: " << power(2, 3) << endl;
    cout << "2^5: " << power(2, 5) << endl;
    
    return 0;
}
```

### Inline Getter/Setter Pattern
```cpp
#include <iostream>
using namespace std;

class Temperature {
private:
    double celsius;
    
public:
    Temperature(double c = 0) : celsius(c) {}
    
    // Inline getters/setters
    inline double getCelsius() const {
        return celsius;
    }
    
    inline void setCelsius(double c) {
        celsius = c;
    }
    
    inline double getFahrenheit() const {
        return celsius * 9.0 / 5.0 + 32.0;
    }
    
    inline void setFahrenheit(double f) {
        celsius = (f - 32.0) * 5.0 / 9.0;
    }
};

int main() {
    Temperature t(25);
    cout << "Celsius: " << t.getCelsius() << endl;
    cout << "Fahrenheit: " << t.getFahrenheit() << endl;
    
    t.setFahrenheit(98.6);
    cout << "Set to 98.6F: " << t.getCelsius() << "C" << endl;
    
    return 0;
}
```

### Inline Recursive Function
```cpp
#include <iostream>
using namespace std;

// Inline recursive function (small base case)
inline int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    for (int i = 0; i <= 10; ++i) {
        cout << "F(" << i << ") = " << fibonacci(i) << endl;
    }
    
    return 0;
}
```

### Inline vs Non-inline (Simulation)
```cpp
#include <iostream>
using namespace std;

// Non-inline version
int addNormal(int a, int b) {
    return a + b;
}

// Inline version
inline int addInline(int a, int b) {
    return a + b;
}

int main() {
    // With non-inline: function call overhead
    int result1 = addNormal(5, 3);
    
    // With inline: code substituted directly
    int result2 = addInline(5, 3);
    
    // Compiler optimization determines actual outcome
    cout << result1 + result2 << endl;
    
    return 0;
}
```

### Inline Function in Header
```cpp
// math_utils.h
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

inline int square(int x) {
    return x * x;
}

inline double cube(double x) {
    return x * x * x;
}

inline int absolute(int x) {
    return (x < 0) ? -x : x;
}

#endif
```

Used in multiple files:
```cpp
#include "math_utils.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Square of 5: " << square(5) << endl;
    cout << "Cube of 2.5: " << cube(2.5) << endl;
    cout << "Absolute of -7: " << absolute(-7) << endl;
    
    return 0;
}
```

### When NOT to Use inline
```cpp
#include <iostream>
using namespace std;

// BAD: Don't inline complex functions
inline void complexAlgorithm(int *arr, int size) {
    // 100+ lines of code
    // Sorting algorithm
    // Inline would increase binary size significantly
}

// GOOD: Inline simple operations
inline int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int arr[5] = {3, 1, 4, 1, 5};
    complexAlgorithm(arr, 5);
    
    cout << "Min(10, 20): " << min(10, 20) << endl;
    
    return 0;
}
```

### Inline Lambdas (Implicitly inline)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    
    // Lambdas are implicitly inline
    auto print = [](int x) { cout << x << " "; };
    
    cout << "Vector: ";
    for_each(v.begin(), v.end(), print);
    cout << endl;
    
    return 0;
}
```

### Inline Functions in Classes
```cpp
#include <iostream>
using namespace std;

class Vector3D {
private:
    double x, y, z;
    
public:
    // Defined in class (implicitly inline)
    Vector3D(double x_ = 0, double y_ = 0, double z_ = 0)
        : x(x_), y(y_), z(z_) {}
    
    // Inline methods
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    
    double dotProduct(const Vector3D &other) const {
        return x * other.x + y * other.y + z * other.z;
    }
};

int main() {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    
    cout << "Dot product: " << v1.dotProduct(v2) << endl;
    
    return 0;
}
```

## Performance Considerations
```
Benefits:
- Eliminates function call overhead
- Enables compiler optimizations
- Better for small functions

Drawbacks:
- Increases binary size
- Can hurt code cache
- Limits separate compilation
```

## When to inline
| Scenario | Decision |
|----------|----------|
| Small getter | ✓ Inline |
| Large algorithm | ✗ Don't inline |
| Simple math | ✓ Inline |
| I/O operations | ✗ Don't inline |
| Frequently called | ? Case-by-case |
| Template methods | ✓ Inline (required) |

## Modern C++ Notes
1. **Compilers are smart**: Modern compilers often inline better than manual hints
2. **Profile first**: Measure before optimizing with inline
3. **Templates are inline**: Template definitions must be in headers
4. **constexpr implies inline**: constexpr functions are implicitly inline
5. **Link-time optimization**: LTO can inline across translation units

## Best Practices
1. Let compiler decide (trust `-O2`/`-O3`)
2. Only inline simple, small functions
3. Inline getters/setters in headers
4. Use for templates and header-only libraries
5. Avoid recursive functions
6. Measure performance impact
7. Document why inline is used
8. Don't over-optimize prematurely
