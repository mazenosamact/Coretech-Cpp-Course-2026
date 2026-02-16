# Dynamic Memory Allocation

## Summary
Dynamic memory allocation allows you to allocate memory at runtime using `malloc()` and `free()`. This enables flexible memory management for data structures whose size isn't known at compile time, such as dynamic arrays, linked lists, and trees.

## Key Concepts
- **Heap Memory**: Memory allocated at runtime persists until explicitly freed
- **`malloc()`**: Allocates memory and returns void pointer (needs casting)
- **`free()`**: Deallocates memory to prevent memory leaks
- **Memory Leak**: Failure to free allocated memory
- **Dangling Pointer**: Pointer to deallocated memory

## Code Examples

### Basic malloc and free
```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    // Allocate memory for an integer
    int *ptr = (int *)malloc(sizeof(int));
    
    *ptr = 42;
    cout << "Value: " << *ptr << endl;           // 42
    cout << "Address: " << ptr << endl;
    
    free(ptr);  // Deallocate memory
    ptr = NULL;  // Good practice to set to NULL
    
    return 0;
}
```

### Dynamic Array Allocation
```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int n = 5;
    
    // Allocate array for 5 integers
    int *arr = (int *)malloc(n * sizeof(int));
    
    // Initialize array
    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
    }
    
    // Display array
    cout << "Array elements: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    free(arr);
    arr = NULL;
    
    return 0;
}
```

### 2D Dynamic Array
```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int rows = 3, cols = 4;
    
    // Allocate rows
    int **matrix = (int **)malloc(rows * sizeof(int *));
    
    // Allocate columns for each row
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    
    // Initialize and display
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value++;
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    // Free columns first, then rows
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}
```

### Dynamic String
```cpp
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

int main() {
    const char *source = "Hello, World!";
    
    // Allocate memory for the string
    char *str = (char *)malloc((strlen(source) + 1) * sizeof(char));
    
    // Copy string
    strcpy(str, source);
    
    cout << "String: " << str << endl;
    cout << "Length: " << strlen(str) << endl;
    
    free(str);
    str = NULL;
    
    return 0;
}
```

### Memory Reallocation
```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int *arr = (int *)malloc(5 * sizeof(int));
    
    // Initialize first 5 elements
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }
    
    cout << "Original array (5 elements): ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Reallocate to larger size
    arr = (int *)realloc(arr, 10 * sizeof(int));
    
    // Initialize new elements
    for (int i = 5; i < 10; i++) {
        arr[i] = i + 1;
    }
    
    cout << "Expanded array (10 elements): ";
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    free(arr);
    arr = NULL;
    
    return 0;
}
```

### Struct with Dynamic Members
```cpp
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

struct Person {
    char *name;
    int age;
    float height;
};

int main() {
    Person p;
    
    // Allocate memory for name
    p.name = (char *)malloc(50 * sizeof(char));
    
    strcpy(p.name, "John Doe");
    p.age = 25;
    p.height = 5.8f;
    
    cout << "Name: " << p.name << endl;
    cout << "Age: " << p.age << endl;
    cout << "Height: " << p.height << endl;
    
    free(p.name);
    p.name = NULL;
    
    return 0;
}
```

### Common Allocation Patterns
```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    // Single value allocation
    int *single = (int *)malloc(sizeof(int));
    *single = 100;
    
    // Array allocation
    int *array = (int *)malloc(5 * sizeof(int));
    
    // Structure allocation
    struct Point {
        int x, y;
    };
    Point *p = (Point *)malloc(sizeof(Point));
    p->x = 10;
    p->y = 20;
    
    cout << "Single: " << *single << endl;
    cout << "Point: (" << p->x << ", " << p->y << ")" << endl;
    
    free(single);
    free(array);
    free(p);
    
    return 0;
}
```

## Memory Management Best Practices
1. Always check allocation success (in production code)
2. Match every `malloc()` with a `free()`
3. Set pointer to NULL after freeing
4. Use `sizeof()` operator to avoid hardcoding sizes
5. Free in reverse order of allocation (for nested allocations)
6. Watch for memory leaks using tools like Valgrind

## Common Issues
| Issue | Solution |
|-------|----------|
| Memory leak | Always pair malloc with free |
| Double free | Check before freeing, set to NULL |
| Wrong size | Use sizeof() to calculate correct size |
| Type mismatch | Cast malloc return value correctly |
