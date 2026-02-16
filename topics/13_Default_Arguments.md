# Default Function Arguments

## Summary
Default arguments allow you to define default values for function parameters. If a caller doesn't provide a value for a parameter with a default, the default value is used automatically.

## Key Concepts
- **Default Value**: Specified in function declaration
- **From Right to Left**: Parameters with defaults must be on the right
- **Override**: Caller can override default values
- **Single Definition**: Defaults specified once (usually in declaration)
- **Type Safety**: Default values must match parameter type

## Code Examples

### Basic Default Arguments
```cpp
#include <iostream>
using namespace std;

void greet(string name = "Guest", string greeting = "Hello") {
    cout << greeting << ", " << name << "!" << endl;
}

int main() {
    greet();                           // Both defaults
    greet("Alice");                    // Override first
    greet("Bob", "Hi");                // Override both
    
    return 0;
}
```

### Default Arguments in Functions
```cpp
#include <iostream>
using namespace std;

// Power function with default exponent
int power(int base, int exp = 2) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int main() {
    cout << "5^2 = " << power(5) << endl;        // Uses default exp=2
    cout << "5^3 = " << power(5, 3) << endl;     // Override default
    cout << "5^4 = " << power(5, 4) << endl;
    
    return 0;
}
```

### Default Arguments with Different Types
```cpp
#include <iostream>
#include <string>
using namespace std;

class Point {
public:
    int x, y;
    
    // Constructor with defaults
    Point(int px = 0, int py = 0) : x(px), y(py) {}
    
    void display() {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    Point p1;           // Both defaults (0, 0)
    Point p2(3);        // Only y defaults to 0
    Point p3(3, 4);     // No defaults
    
    p1.display();
    p2.display();
    p3.display();
    
    return 0;
}
```

### Default Arguments Order Rules
```cpp
#include <iostream>
using namespace std;

// CORRECT: Defaults from right to left
void func1(int a, int b = 10, int c = 20) {
    cout << "a=" << a << ", b=" << b << ", c=" << c << endl;
}

// ERROR: Cannot have non-default after default
// void func2(int a, int b = 10, int c) {}  // WRONG!

// One default can depend on another's position
void func3(int x, int y = 5, int z = y + 10) {
    cout << "x=" << x << ", y=" << y << ", z=" << z << endl;
}

int main() {
    func1(1);           // b=10, c=20
    func1(1, 2);        // c=20
    func1(1, 2, 3);     // No defaults
    
    func3(100);
    func3(100, 15);
    
    return 0;
}
```

### Default Arguments in File Operations
```cpp
#include <iostream>
#include <fstream>
using namespace std;

void writeToFile(const string &filename, const string &content, bool append = false) {
    ios_base::openmode mode = (append) ? ios::app : ios::out;
    ofstream file(filename, mode);
    
    if (file.is_open()) {
        file << content << endl;
        file.close();
        cout << "File '" << filename << "' written successfully" << endl;
    } else {
        cout << "Error opening file" << endl;
    }
}

int main() {
    writeToFile("data.txt", "First line");      // Overwrite (append=false)
    writeToFile("data.txt", "Second line", true); // Append (append=true)
    
    return 0;
}
```

### Default Arguments in Class Methods
```cpp
#include <iostream>
using namespace std;

class Rectangle {
private:
    double length, width;
    
public:
    // Constructor with defaults
    Rectangle(double l = 1.0, double w = 1.0) 
        : length(l), width(w) {}
    
    // Member function with default parameter
    double getArea(bool rounded = false) {
        double area = length * width;
        return rounded ? (int)area : area;
    }
    
    void setDimensions(double l = 1.0, double w = 1.0) {
        length = l;
        width = w;
    }
    
    void display() {
        cout << "Length: " << length << ", Width: " << width << endl;
    }
};

int main() {
    Rectangle r;                       // All defaults
    r.display();
    
    cout << "Area (normal): " << r.getArea() << endl;
    cout << "Area (rounded): " << r.getArea(true) << endl;
    
    r.setDimensions(5, 3);
    r.display();
    
    return 0;
}
```

### Default Arguments with Complex Types
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void printVector(const vector<int> &v, string prefix = "Elements: ") {
    cout << prefix;
    for (int val : v) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    
    printVector(nums);                          // Default prefix
    printVector(nums, "Numbers: ");             // Custom prefix
    
    return 0;
}
```

### Optional Output Parameter
```cpp
#include <iostream>
using namespace std;

// Function with optional output parameter
void divide(int numerator, int denominator, int &result, bool &success = true) {
    if (denominator != 0) {
        result = numerator / denominator;
        success = true;
    } else {
        result = 0;
        success = false;
    }
}

int main() {
    int answer;
    bool ok;
    
    divide(10, 2, answer);              // Uses default success=true
    cout << "10/2 = " << answer << ", Success: " << ok << endl;
    
    divide(10, 0, answer, ok);          // Explicit error check
    cout << "10/0 = " << answer << ", Success: " << ok << endl;
    
    return 0;
}
```

### Default Function Pointer Argument
```cpp
#include <iostream>
using namespace std;

// Default callback function
void defaultCallback(int value) {
    cout << "Default callback: " << value << endl;
}

void processData(int data, void (*callback)(int) = defaultCallback) {
    cout << "Processing: " << data << endl;
    callback(data * 2);
}

void customCallback(int value) {
    cout << "Custom callback: " << value << " (squared)" << endl;
}

int main() {
    processData(5);                          // Uses default callback
    processData(5, customCallback);          // Custom callback
    
    return 0;
}
```

### Declaration vs Definition
```cpp
#include <iostream>
using namespace std;

// Function declaration with defaults
void configure(int timeout = 5000, bool verbose = false);

// Later, definition without repeating defaults
void configure(int timeout, bool verbose) {
    cout << "Timeout: " << timeout << "ms" << endl;
    cout << "Verbose: " << (verbose ? "enabled" : "disabled") << endl;
}

int main() {
    configure();
    configure(3000);
    configure(3000, true);
    
    return 0;
}
```

### Using Constants as Defaults
```cpp
#include <iostream>
#include <string>
using namespace std;

const int DEFAULT_SIZE = 10;
const string DEFAULT_NAME = "Default";
const float DEFAULT_RATE = 5.5f;

class Account {
private:
    string name;
    float rate;
    
public:
    Account(string n = DEFAULT_NAME, float r = DEFAULT_RATE) 
        : name(n), rate(r) {}
    
    void display() {
        cout << "Account: " << name << ", Rate: " << rate << "%" << endl;
    }
};

int main() {
    Account a1;
    Account a2("Premium", 7.5f);
    
    a1.display();
    a2.display();
    
    return 0;
}
```

## Rules for Default Arguments
1. Must be from right to left (no non-default after default)
2. Defaults specified in declaration, not redefined in definition
3. Must be compile-time constants or global variables
4. Cannot be local variables
5. Can be expressions but evaluated at call time

## Common Patterns
| Pattern | Example |
|---------|---------|
| Optional feature | `bool enabled = false` |
| Sensible default | `int retries = 3` |
| Format control | `bool formatted = true` |
| Callback | `void (*func)() = nullptr` |
| Size | `int capacity = 100` |

## Best Practices
- Use defaults for truly optional parameters
- Document default values in comments
- Keep defaults meaningful and intuitive
- Avoid confusing parameter order
- Use constants for default values (improves maintainability)
