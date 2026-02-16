# new and delete Operators

## Summary
`new` and `delete` are C++ operators for dynamic memory allocation and deallocation on the heap. They are the modern C++ replacements for `malloc()` and `free()`, offering better integration with constructors and destructors.

## Key Concepts
- **`new`**: Allocates memory and calls constructor
- **`delete`**: Calls destructor and deallocates memory
- **Arrays**: Use `new[]` and `delete[]`
- **Type Safety**: More type-safe than malloc/free
- **RAII**: Resource Acquisition Is Initialization pattern

## Code Examples

### Basic new and delete
```cpp
#include <iostream>
using namespace std;

int main() {
    // Allocate integer
    int *ptr = new int;
    *ptr = 42;
    
    cout << "Value: " << *ptr << endl;
    
    delete ptr;
    ptr = nullptr;  // Good practice to set to nullptr
    
    return 0;
}
```

### new with Initialization
```cpp
#include <iostream>
using namespace std;

int main() {
    // Different initialization methods
    int *p1 = new int;         // Uninitialized
    int *p2 = new int(10);     // Initialize to 10
    int *p3 = new int{20};     // Uniform initialization
    
    cout << "p2: " << *p2 << endl;
    cout << "p3: " << *p3 << endl;
    
    delete p1;
    delete p2;
    delete p3;
    
    return 0;
}
```

### Dynamic Array Allocation
```cpp
#include <iostream>
using namespace std;

int main() {
    int n = 5;
    
    // Allocate array
    int *arr = new int[n];
    
    // Initialize array
    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
    }
    
    // Display array
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;  // Note: delete[] for arrays
    arr = nullptr;
    
    return 0;
}
```

### new and delete with Objects
```cpp
#include <iostream>
using namespace std;

class Person {
private:
    string name;
    
public:
    Person(string n) : name(n) {
        cout << "Constructor: " << name << " created" << endl;
    }
    
    ~Person() {
        cout << "Destructor: " << name << " destroyed" << endl;
    }
    
    void display() {
        cout << "Name: " << name << endl;
    }
};

int main() {
    // Create object on heap
    Person *p = new Person("John");
    p->display();
    
    // Destructor is called when delete is executed
    delete p;
    p = nullptr;
    
    return 0;
}
```

### Returning Dynamically Allocated Memory
```cpp
#include <iostream>
using namespace std;

class Point {
public:
    int x, y;
    
    Point(int px, int py) : x(px), y(py) {
        cout << "Point created at (" << x << ", " << y << ")" << endl;
    }
    
    ~Point() {
        cout << "Point destroyed" << endl;
    }
};

// Function returning dynamically allocated object
Point* createPoint(int x, int y) {
    return new Point(x, y);
}

int main() {
    Point *p = createPoint(5, 10);
    
    cout << "Point coordinates: (" << p->x << ", " << p->y << ")" << endl;
    
    delete p;
    
    return 0;
}
```

### Array of Objects
```cpp
#include <iostream>
using namespace std;

class Car {
private:
    string brand;
    
public:
    Car(string b) : brand(b) {
        cout << "Car " << brand << " created" << endl;
    }
    
    ~Car() {
        cout << "Car " << brand << " destroyed" << endl;
    }
    
    void show() {
        cout << "Brand: " << brand << endl;
    }
};

int main() {
    // Create array of objects
    Car *cars = new Car[3]{
        Car("Honda"),
        Car("Toyota"),
        Car("Ford")
    };
    
    // Use objects
    cars[0].show();
    
    // Deallocate array
    delete[] cars;
    
    return 0;
}
```

### 2D Dynamic Array
```cpp
#include <iostream>
using namespace std;

int main() {
    int rows = 3, cols = 4;
    
    // Allocate rows
    int **matrix = new int*[rows];
    
    // Allocate columns
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    
    // Initialize
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value++;
        }
    }
    
    // Display
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    // Deallocate columns first, then rows
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    
    return 0;
}
```

### Struct with Dynamic Members
```cpp
#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int *grades;
    int numGrades;
    
    // Constructor
    Student(string n, int num) : name(n), numGrades(num) {
        grades = new int[num];
        cout << "Student " << name << " data allocated" << endl;
    }
    
    // Destructor
    ~Student() {
        delete[] grades;
        cout << "Student " << name << " data deallocated" << endl;
    }
};

int main() {
    {
        Student s1("Alice", 5);
        
        // Set grades
        for (int i = 0; i < s1.numGrades; i++) {
            s1.grades[i] = 90 + i;
        }
        
        // Destructor called when going out of scope
    }
    
    return 0;
}
```

### Pointer Arithmetic with new
```cpp
#include <iostream>
using namespace std;

int main() {
    int *arr = new int[5];
    
    // Using pointer arithmetic
    for (int i = 0; i < 5; i++) {
        *(arr + i) = (i + 1) * 10;
    }
    
    // Display using pointer arithmetic
    cout << "Array elements: ";
    for (int i = 0; i < 5; i++) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
    
    delete[] arr;
    
    return 0;
}
```

## new vs new[] vs delete vs delete[]
```cpp
#include <iostream>
using namespace std;

int main() {
    // Single object
    int *single = new int(42);
    delete single;  // Use delete
    
    // Array
    int *array = new int[10];
    delete[] array;  // Use delete[]
    
    // Class object
    class Obj {
    public:
        Obj() { cout << "Constructor" << endl; }
        ~Obj() { cout << "Destructor" << endl; }
    };
    
    Obj *obj = new Obj();
    delete obj;  // Calls destructor
    
    Obj *objs = new Obj[3];
    delete[] objs;  // Calls destructors for all 3
    
    return 0;
}
```

## Key Differences: new vs malloc
| Aspect | new | malloc |
|--------|-----|--------|
| Calls Constructor | Yes | No |
| Calls Destructor | Yes (with delete) | No |
| Type Safety | Safe | Not type-safe |
| Return Type | Pointer | void* (requires cast) |
| RAII Integration | Yes | No |

## Best Practices
1. Always match `new` with `delete` and `new[]` with `delete[]`
2. Set pointers to `nullptr` after deleting
3. Use smart pointers (unique_ptr, shared_ptr) instead when possible
4. Avoid raw `new`/`delete` in large applications
5. Consider RAII patterns for resource management
