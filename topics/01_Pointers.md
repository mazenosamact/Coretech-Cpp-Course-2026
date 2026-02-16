# Pointers

## Summary
A pointer is a variable that stores a memory address. Pointers allow you to work with memory locations directly, enabling dynamic memory allocation, reference passing to functions, and complex data structures like linked lists.

## Key Concepts
- **Address operator (`&`)**: Gets the address of a variable
- **Dereference operator (`*`)**: Accesses the value at a pointer's address
- **Null pointer**: A pointer that points to nothing

## Code Examples

### Basic Pointer Declaration and Usage
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    int *ptr = &x;  // Pointer to x, ptr stores the address of x
    
    cout << "Value of x: " << x << endl;           // Output: 10
    cout << "Address of x: " << &x << endl;        // Address
    cout << "Value of ptr: " << ptr << endl;       // Same address
    cout << "Value pointed by ptr: " << *ptr << endl; // 10
    
    *ptr = 20;  // Change value through pointer
    cout << "New value of x: " << x << endl;       // Output: 20
    
    return 0;
}
```

### Pointer Arithmetic
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // Points to first element
    
    cout << "First element: " << *ptr << endl;     // 10
    cout << "Second element: " << *(ptr + 1) << endl; // 20
    cout << "Third element: " << *(ptr + 2) << endl;  // 30
    
    ptr++;  // Move to next element
    cout << "After ptr++: " << *ptr << endl;       // 20
    
    return 0;
}
```

### Pointer to Pointer
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 100;
    int *ptr1 = &x;
    int **ptr2 = &ptr1;  // Pointer to pointer
    
    cout << "Value of x: " << x << endl;           // 100
    cout << "*ptr1: " << *ptr1 << endl;            // 100
    cout << "**ptr2: " << **ptr2 << endl;          // 100
    
    **ptr2 = 200;
    cout << "New value of x: " << x << endl;       // 200
    
    return 0;
}
```

### Function with Pointers
```cpp
#include <iostream>
using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    
    swap(&x, &y);
    
    cout << "After swap: x = " << x << ", y = " << y << endl;
    
    return 0;
}
```

## Common Pitfalls
- **Dangling pointers**: Pointing to deallocated memory
- **Uninitialized pointers**: Using pointers without initialization
- **Memory leaks**: Allocating memory without freeing it
