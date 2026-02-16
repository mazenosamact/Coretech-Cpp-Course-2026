# References vs Pointers - Practical Exercises

## Exercise 1: Function Parameters (Backend Development)
**Context:** Choosing between references and pointers for function arguments.

**Problem:**
```cpp
// Implement functions showing when to use each:
// 1. Swap values using reference
// 2. Optional output using pointer
// 3. Modify structure using reference
// 4. Deep copy vs shallow operations
```

**Solution:**
```cpp
#include <iostream>
using namespace std;

struct Point {
    int x, y;
    
    Point() : x(0), y(0) {}
    Point(int x_, int y_) : x(x_), y(y_) {}
};

// Using reference - cannot be null, must be initialized
void swapValues(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    cout << "Swapped: a=" << a << ", b=" << b << endl;
}

// Using pointer - can be null, optional
bool movePoint(Point &p, int dx, int dy) {
    p.x += dx;
    p.y += dy;
    cout << "Moved to: (" << p.x << ", " << p.y << ")" << endl;
    return true;
}

// Using pointer for optional output
int divide(int a, int b, int *remainder = nullptr) {
    int result = a / b;
    if (remainder != nullptr) {
        *remainder = a % b;
    }
    return result;
}

int main() {
    cout << "=== References vs Pointers ===" << endl;
    
    cout << "\n--- Swap using reference ---" << endl;
    int x = 10, y = 20;
    cout << "Before: x=" << x << ", y=" << y << endl;
    swapValues(x, y);
    
    cout << "\n--- Modify object using reference ---" << endl;
    Point p(5, 5);
    movePoint(p, 3, 4);
    
    cout << "\n--- Optional output using pointer ---" << endl;
    int remainder;
    int result = divide(17, 5, &remainder);
    cout << "17 / 5 = " << result << " remainder " << remainder << endl;
    
    int result2 = divide(20, 4);  // No remainder needed
    cout << "20 / 4 = " << result2 << endl;
    
    cout << "\n✓ Different use cases demonstrated" << endl;
    
    return 0;
}
```

---

## Exercise 2: Pointer vs Reference Safety (System Programming)
**Context:** Different safety considerations for each.

**Problem:**
```cpp
// Demonstrate:
// 1. References cannot be null (safer)
// 2. Pointers can be null (flexible)
// 3. References cannot be reassigned
// 4. Pointers can be reassigned
```

**Solution:**
```cpp
#include <iostream>
using namespace std;

class Resource {
private:
    int id;
    
public:
    Resource(int id_) : id(id_) {
        cout << "Resource " << id << " created" << endl;
    }
    
    ~Resource() {
        cout << "Resource " << id << " destroyed" << endl;
    }
    
    void use() {
        cout << "Using resource " << id << endl;
    }
};

int main() {
    cout << "=== Reference vs Pointer Safety ===" << endl;
    
    Resource r1(1);
    Resource r2(2);
    
    cout << "\n--- Pointer: Can be null ---" << endl;
    Resource *ptr = &r1;
    ptr->use();
    
    ptr = &r2;  // Can reassign
    ptr->use();
    
    ptr = nullptr;  // Can be null!
    if (ptr != nullptr) {
        ptr->use();
    } else {
        cout << "Pointer is null, cannot use" << endl;
    }
    
    cout << "\n--- Reference: Cannot be null ---" << endl;
    Resource &ref = r1;
    ref.use();
    
    ref = r2;  // This is an assignment operation, not reassignment!
    cout << "ref still refers to r1 (assignment copied value)" << endl;
    r1.use();
    
    cout << "\n✓ Reference is safer (no null check needed)" << endl;
    
    return 0;
}
```

---

## Exercise 3: Iterators and References (STL Programming)
**Context:** Working with container iterators and references.

**Problem:**
```cpp
// Demonstrate:
// 1. Pointer-like iterator behavior
// 2. Reference to container elements
// 3. Range-based for with references
// 4. Iterator dereferencing
```

**Solution:**
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "=== Iterators and References ===" << endl;
    
    vector<int> data = {10, 20, 30, 40, 50};
    
    cout << "\n--- Iterators (pointer-like) ---" << endl;
    for (auto it = data.begin(); it != data.end(); ++it) {
        cout << "Value: " << *it << ", Address: " << it << endl;
    }
    
    cout << "\n--- Iterator reassignment ---" << endl;
    auto it = data.begin();
    cout << "First element: " << *it << endl;
    ++it;
    cout << "Second element: " << *it << endl;
    
    cout << "\n--- Modifying through pointer iterator ---" << endl;
    *it = 25;  // Modify second element
    cout << "Modified second element to: " << *it << endl;
    
    cout << "\n--- Range-based for with reference ---" << endl;
    for (int &value : data) {
        value *= 2;  // Double all values
    }
    
    cout << "After doubling: ";
    for (int v : data) {
        cout << v << " ";
    }
    cout << endl;
    
    cout << "\n--- Const reference (read-only) ---" << endl;
    for (const int &value : data) {
        cout << value << " ";
    }
    cout << endl;
    
    return 0;
}
```
