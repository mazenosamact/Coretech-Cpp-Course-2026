# Constexpr Keyword - Practical Exercises

## Exercise 1: Compile-Time Constants (Performance)
**Context:** Evaluate computations at compile time instead of runtime.

**Problem:**
```cpp
// Use constexpr for:
// 1. Compile-time constants
// 2. Constant expressions
// 3. Array sizes
// 4. Template arguments
// 5. Performance optimization
```

**Solution:**
```cpp
#include <iostream>
#include <array>
using namespace std;

// Compile-time constant - no runtime cost
constexpr int BUFFER_SIZE = 1024;
constexpr float PI = 3.14159f;

// Constexpr function - can be evaluated at compile time
constexpr int square(int x) {
    return x * x;
}

constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr float circleArea(float radius) {
    return PI * radius * radius;
}

constexpr int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    cout << "=== Constexpr: Compile-Time Evaluation ===" << endl;
    
    cout << "\n--- Using constexpr as compile-time constants ---" << endl;
    cout << "Buffer size: " << BUFFER_SIZE << " bytes" << endl;
    cout << "PI value: " << PI << endl;
    
    // These are computed at compile time, not runtime
    constexpr int sq_3 = square(3);
    constexpr int sq_10 = square(10);
    
    cout << "Squares (compile-time): 3²=" << sq_3 << ", 10²=" << sq_10 << endl;
    
    cout << "\n--- Compile-time factorial ---" << endl;
    constexpr int fact_0 = factorial(0);
    constexpr int fact_5 = factorial(5);
    constexpr int fact_10 = factorial(10);
    
    cout << "0! = " << fact_0 << endl;
    cout << "5! = " << fact_5 << endl;
    cout << "10! = " << fact_10 << endl;
    
    cout << "\n--- Array sizes from constexpr ---" << endl;
    // This is only possible with constexpr!
    array<int, BUFFER_SIZE / 4> buffer;
    cout << "Array size: " << buffer.size() << " elements" << endl;
    
    array<int, factorial(5)> fib_array;
    cout << "Fibonacci array size: " << fib_array.size() << endl;
    
    cout << "\n--- Compile-time geometry ---" << endl;
    constexpr float area_r2 = circleArea(2.0f);
    constexpr float area_r5 = circleArea(5.0f);
    
    cout << "Circle area (r=2): " << area_r2 << endl;
    cout << "Circle area (r=5): " << area_r5 << endl;
    
    cout << "\n--- Runtime evaluation (if needed) ---" << endl;
    int user_input = 15;
    int runtime_fib = fibonacci(user_input);
    cout << "Fibonacci(" << user_input << ") = " << runtime_fib << endl;
    
    cout << "\n✓ Constexpr evaluation complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Constexpr Classes and Methods
**Context:** Use constexpr for type-safe compile-time operations.

**Problem:**
```cpp
// Constexpr in classes:
// 1. Constexpr constructors
// 2. Constexpr member functions
// 3. Compile-time objects
// 4. Validation
// 5. Type safety
```

**Solution:**
```cpp
#include <iostream>
#include <array>
using namespace std;

class Point {
private:
    int x, y;
    
public:
    // Constexpr constructor
    constexpr Point(int x_val = 0, int y_val = 0) : x(x_val), y(y_val) {}
    
    // Constexpr getter
    constexpr int getX() const { return x; }
    constexpr int getY() const { return y; }
    
    // Constexpr computation
    constexpr int distanceSquared(const Point &other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return dx*dx + dy*dy;
    }
    
    // Regular method
    void display() const {
        cout << "Point(" << x << ", " << y << ")";
    }
};

class Temperature {
private:
    float celsius;
    
public:
    constexpr Temperature(float c) : celsius(c) {}
    
    constexpr float getCelsius() const { return celsius; }
    
    constexpr float getFahrenheit() const {
        return celsius * 9.0f / 5.0f + 32.0f;
    }
    
    // Constexpr validation
    constexpr bool isFreezingPoint() const {
        return celsius == 0.0f;
    }
};

int main() {
    cout << "=== Constexpr: Classes and Methods ===" << endl;
    
    cout << "\n--- Compile-time Point objects ---" << endl;
    constexpr Point origin(0, 0);
    constexpr Point p1(3, 4);
    constexpr Point p2(6, 8);
    
    cout << "Origin: ";
    origin.display();
    cout << endl;
    
    cout << "Point 1: ";
    p1.display();
    cout << " - X=" << p1.getX() << ", Y=" << p1.getY() << endl;
    
    cout << "\n--- Compile-time distance calculation ---" << endl;
    constexpr int dist_sq = p1.distanceSquared(origin);
    cout << "Distance² from origin to P1: " << dist_sq << endl;
    
    constexpr int dist_sq_2 = p1.distanceSquared(p2);
    cout << "Distance² from P1 to P2: " << dist_sq_2 << endl;
    
    cout << "\n--- Compile-time temperature conversion ---" << endl;
    constexpr Temperature freezing(0.0f);
    constexpr Temperature room(20.0f);
    constexpr Temperature hot(100.0f);
    
    cout << "Freezing: " << freezing.getCelsius() << "°C = " 
         << freezing.getFahrenheit() << "°F" << endl;
    cout << "Room: " << room.getCelsius() << "°C = " 
         << room.getFahrenheit() << "°F" << endl;
    cout << "Hot: " << hot.getCelsius() << "°C = " 
         << hot.getFahrenheit() << "°F" << endl;
    
    cout << "\n--- Compile-time validation ---" << endl;
    cout << "Is freezing point? " 
         << (freezing.isFreezingPoint() ? "Yes" : "No") << endl;
    cout << "Is room point freezing? " 
         << (room.isFreezingPoint() ? "Yes" : "No") << endl;
    
    cout << "\n✓ Constexpr classes complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Constexpr Meta-Programming (Type-Level Computation)
**Context:** Use constexpr for advanced compile-time meta-programming.

**Problem:**
```cpp
// Advanced constexpr:
// 1. Compile-time arrays
// 2. Meta-functions
// 3. Type computation
// 4. Algorithm optimization
// 5. Lookup tables
```

**Solution:**
```cpp
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

// Generate lookup table at compile time
class SquareTable {
private:
    array<int, 100> squares;
    
    constexpr array<int, 100> generateSquares() const {
        array<int, 100> result = {};
        for (int i = 0; i < 100; i++) {
            result[i] = i * i;
        }
        return result;
    }
    
public:
    constexpr SquareTable() : squares(generateSquares()) {}
    
    constexpr int getSquare(int n) const {
        if (n >= 0 && n < 100) {
            return squares[n];
        }
        return -1;
    }
    
    void displayTable() const {
        cout << "Square table (0-20):" << endl;
        for (int i = 0; i <= 20; i++) {
            cout << i << "² = " << getSquare(i) << endl;
        }
    }
};

// Compile-time prime lookup
constexpr bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

constexpr int countPrimes(int limit) {
    int count = 0;
    for (int i = 2; i <= limit; i++) {
        if (isPrime(i)) count++;
    }
    return count;
}

// Constexpr string-like operations
constexpr int stringLength(const char *str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

int main() {
    cout << "=== Constexpr: Meta-Programming ===" << endl;
    
    cout << "\n--- Compile-time square table ---" << endl;
    constexpr SquareTable table;
    
    table.displayTable();
    
    cout << "\n--- Compile-time prime checking ---" << endl;
    constexpr int prime_count = countPrimes(50);
    cout << "Primes up to 50: " << prime_count << " total" << endl;
    
    cout << "\nCompile-time prime test:" << endl;
    cout << "Is 17 prime? " << (isPrime(17) ? "Yes" : "No") << endl;
    cout << "Is 20 prime? " << (isPrime(20) ? "Yes" : "No") << endl;
    cout << "Is 97 prime? " << (isPrime(97) ? "Yes" : "No") << endl;
    
    cout << "\n--- String operations at compile time ---" << endl;
    constexpr int len1 = stringLength("Hello");
    constexpr int len2 = stringLength("Constexpr");
    
    cout << "Length of 'Hello': " << len1 << endl;
    cout << "Length of 'Constexpr': " << len2 << endl;
    
    cout << "\n--- Using compile-time computed values ---" << endl;
    // This size is determined at compile time
    array<int, countPrimes(100)> primes_array;
    cout << "Array size for primes up to 100: " << primes_array.size() << endl;
    
    cout << "\n✓ Constexpr meta-programming complete" << endl;
    
    return 0;
}
```
