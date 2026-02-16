# References vs Pointers

## Summary
References and pointers are both used to reference objects, but they differ in several ways. References are automatically dereferenced, cannot be null, and cannot be reassigned, while pointers can be reassigned and have explicit dereferencing.

## Key Concepts
- **Reference**: Alias for another variable
- **Pointer**: Stores memory address
- **Auto-dereference**: References are automatically dereferenced
- **Null**: Pointers can be null, references cannot
- **Reassignment**: Pointers can be reassigned, references cannot

## Code Examples

### Basic Reference Declaration
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    int &ref = x;  // ref is a reference to x
    
    cout << "x: " << x << endl;
    cout << "ref: " << ref << endl;
    
    // Changing through reference affects original
    ref = 20;
    cout << "After ref = 20:" << endl;
    cout << "x: " << x << endl;
    cout << "ref: " << ref << endl;
    
    return 0;
}
```

### Reference vs Pointer Comparison
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 100;
    
    // Pointer
    int *ptr = &x;
    cout << "Pointer value: " << *ptr << endl;      // Manual dereference
    cout << "Pointer address: " << ptr << endl;
    
    // Reference
    int &ref = x;
    cout << "Reference value: " << ref << endl;     // Auto-dereference
    cout << "Reference address: " << &ref << endl;  // Same as &x
    
    // Change value
    *ptr = 200;
    cout << "After *ptr = 200: " << x << endl;     // 200
    
    ref = 300;
    cout << "After ref = 300: " << x << endl;       // 300
    
    return 0;
}
```

### Reference Reassignment
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10, y = 20;
    
    // Pointer can be reassigned
    int *ptr = &x;
    cout << "ptr points to x: " << *ptr << endl;
    
    ptr = &y;  // Reassign to point to y
    cout << "ptr now points to y: " << *ptr << endl;
    
    // Reference cannot be reassigned
    int &ref = x;
    cout << "ref refers to x: " << ref << endl;
    
    // This assigns the VALUE, not the reference
    ref = y;   // Sets x to 20, doesn't change what ref refers to
    cout << "After ref = y, x is: " << x << endl;   // 20
    cout << "ref still refers to: " << ref << endl; // x (now 20)
    
    return 0;
}
```

### Null Pointers vs Null References
```cpp
#include <iostream>
using namespace std;

int main() {
    // Pointer can be null
    int *ptr = nullptr;
    
    if (ptr == nullptr) {
        cout << "Pointer is null" << endl;
    }
    
    // This would be undefined behavior:
    // int &ref = *ptr;  // ERROR: reference cannot be null
    
    int x = 10;
    int &ref = x;
    // ref cannot be made null - always refers to something
    
    cout << "Reference always valid: " << ref << endl;
    
    return 0;
}
```

### Function Parameters: References vs Pointers
```cpp
#include <iostream>
using namespace std;

// Using pointer
void modifyByPointer(int *ptr) {
    if (ptr != nullptr) {
        *ptr = 100;
    }
}

// Using reference
void modifyByReference(int &ref) {
    ref = 100;  // No null check needed
}

int main() {
    int x = 10;
    
    cout << "Original: " << x << endl;
    
    modifyByPointer(&x);
    cout << "After pointer function: " << x << endl;
    
    x = 10;
    modifyByReference(x);
    cout << "After reference function: " << x << endl;
    
    return 0;
}
```

### Array Parameters with References
```cpp
#include <iostream>
using namespace std;

// Reference to array (size must be known)
void printArrayRef(const int (&arr)[5]) {
    cout << "Array elements: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Pointer to array
void printArrayPtr(const int *arr, int size) {
    cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    
    printArrayRef(arr);
    printArrayPtr(arr, 5);
    
    return 0;
}
```

### References in Return Values
```cpp
#include <iostream>
using namespace std;

class Container {
private:
    int value;
    
public:
    Container(int v) : value(v) {}
    
    // Return by reference (efficient)
    int& getValue() {
        return value;
    }
    
    // Return by pointer (can check null)
    int* getValuePtr() {
        return &value;
    }
};

int main() {
    Container c(42);
    
    // Reference - directly modify
    int &ref = c.getValue();
    ref = 100;
    
    // Pointer - deref and modify
    int *ptr = c.getValuePtr();
    if (ptr != nullptr) {
        *ptr = 50;
    }
    
    return 0;
}
```

### Const References
```cpp
#include <iostream>
using namespace std;

void printByConstRef(const string &str) {
    cout << "String: " << str << endl;
    // str cannot be modified
}

int main() {
    string s = "Hello";
    
    printByConstRef(s);  // Safe, no copy needed
    
    // Const reference binds to temporaries
    const string &ref = string("World");
    cout << "Temporary: " << ref << endl;
    
    return 0;
}
```

### Pointer to Pointer vs Reference
```cpp
#include <iostream>
using namespace std;

void changePointer(int **pptr) {
    *pptr = new int(100);
}

// Cannot have reference to reference
// void changeReference(int& &ref) {}  // ERROR

int main() {
    int x = 10;
    int *ptr = &x;
    
    ptr = new int(50);
    change Pointer(&ptr);  // Pass pointer to pointer
    
    cout << "Value: " << **pptr << endl;
    
    return 0;
}
```

### Performance Comparison
```cpp
#include <iostream>
#include <string>
using namespace std;

// Pass by value - makes a copy
void byValue(string str) {
    cout << str << endl;
}

// Pass by pointer - efficient
void byPointer(const string *ptr) {
    if (ptr) cout << *ptr << endl;
}

// Pass by reference - efficient
void byReference(const string &ref) {
    cout << ref << endl;
}

int main() {
    string s = "Hello, World!";
    
    byValue(s);          // 1 copy
    byPointer(&s);       // No copy
    byReference(s);      // No copy (preferred)
    
    return 0;
}
```

## Quick Reference Table
| Aspect | Pointer | Reference |
|--------|---------|-----------|
| Null | Can be null | Cannot be null |
| Reassignment | Can be reassigned | Cannot be reassigned |
| Dereference | Manual `*` | Automatic |
| Memory address | Stores address | Alias (same address) |
| Syntax | `*ptr` | `&ref` |
| Default param | Pass address | Pass directly |


## why still use pointer if reference exists ? (when reference can not solve the problem)

1. `this` pointer: to achieve what we want by the `this` syntax, it has to be a pointer. A reference can not be used here simply bec. of how it is defined.
2. dynamic memory allocation: pointers are still a low level concept on the CPU and OS level, So there is no way to reference memory from the OS other than with pointers.
3. Low Level register access: think memory mapped io in embedded.
4. Callbacks and function pointers: there is no reference to function.


## Best Practices
- Use references for function parameters when you need to modify or avoid copying
- Use const references to prevent copying large objects
- Use pointers when null handling is needed
- Prefer references for cleaner syntax
- Use pointers for polymorphism (virtual functions)
