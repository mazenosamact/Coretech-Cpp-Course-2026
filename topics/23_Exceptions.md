# Exceptions

## Summary
Exceptions provide a structured way to handle errors using try-catch blocks. They allow functions to signal errors by throwing exceptions, which are caught by exception handlers, making error handling clearer than return codes.

## Key Concepts
- **try-catch**: Execute code and handle exceptions
- **throw**: Signal an error
- **Exception Types**: Standard and custom exceptions
- **Stack Unwinding**: Automatic cleanup when exception thrown
- **RAII**: Resources cleaned up even with exceptions

## Code Examples

### Basic try-catch
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    try {
        int x = 10, y = 0;
        if (y == 0) {
            throw invalid_argument("Division by zero");
        }
        cout << "Result: " << x / y << endl;
    }
    catch (const invalid_argument &e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    
    return 0;
}
```

### Multiple catch Blocks
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

void process(int type) {
    if (type == 0) {
        throw invalid_argument("Invalid argument");
    } else if (type == 1) {
        throw out_of_range("Out of range");
    } else if (type == 2) {
        throw runtime_error("Runtime error");
    }
}

int main() {
    try {
        process(1);
    }
    catch (const invalid_argument &e) {
        cout << "Invalid arg: " << e.what() << endl;
    }
    catch (const out_of_range &e) {
        cout << "Out of range: " << e.what() << endl;
    }
    catch (const runtime_error &e) {
        cout << "Runtime error: " << e.what() << endl;
    }
    catch (const exception &e) {
        cout << "Generic exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown exception caught" << endl;
    }
    
    return 0;
}
```

### Exception Hierarchy
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    try {
        // All standard exceptions inherit from exception
        throw out_of_range("Invalid index");
    }
    catch (const logic_error &e) {
        cout << "Logic error: " << e.what() << endl;
    }
    catch (const exception &e) {
        cout << "Standard exception: " << e.what() << endl;
    }
    
    return 0;
}
```

### Custom Exception Class
```cpp
#include <iostream>
#include <exception>
using namespace std;

class FileException : public exception {
private:
    string message;
    
public:
    FileException(const string &filename) 
        : message("Cannot open file: " + filename) {}
    
    const char *what() const noexcept override {
        return message.c_str();
    }
};

void openFile(const string &filename) {
    if (filename.empty()) {
        throw FileException(filename);
    }
    cout << "File opened: " << filename << endl;
}

int main() {
    try {
        openFile("");
    }
    catch (const FileException &e) {
        cout << "File error: " << e.what() << endl;
    }
    
    return 0;
}
```

### Stack Unwinding
```cpp
#include <iostream>
using namespace std;

class Resource {
public:
    Resource(const string &name) : name(name) {
        cout << "  Creating: " << name << endl;
    }
    
    ~Resource() {
        cout << "  Destroying: " << name << endl;
    }
    
private:
    string name;
};

void function3() {
    Resource r3("Resource3");
    throw runtime_error("Error in function3");
}

void function2() {
    Resource r2("Resource2");
    function3();
}

void function1() {
    Resource r1("Resource1");
    function2();
}

int main() {
    try {
        function1();
    }
    catch (const exception &e) {
        cout << "Caught: " << e.what() << endl;
    }
    // All resources destroyed in reverse order
    
    return 0;
}
```

### Exception Safety with RAII
```cpp
#include <iostream>
#include <memory>
#include <fstream>
using namespace std;

class FileHandler {
private:
    ofstream file;
    
public:
    FileHandler(const string &filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file");
        }
    }
    
    ~FileHandler() {
        if (file.is_open()) {
            file.close();
            cout << "File closed automatically" << endl;
        }
    }
    
    void write(const string &data) {
        file << data << endl;
    }
};

int main() {
    try {
        FileHandler handler("output.txt");
        handler.write("Line 1");
        handler.write("Line 2");
        
        // throw runtime_error("Error mid-operation");
        
        handler.write("Line 3");
    }
    catch (const exception &e) {
        cout << "Exception: " << e.what() << endl;
    }
    // File automatically closed even if exception thrown
    
    return 0;
}
```

### Re-throwing Exceptions
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

void logAndRethrow(const exception &e) {
    cout << "Logging error: " << e.what() << endl;
    throw;  // Re-throw the same exception
}

int main() {
    try {
        try {
            throw invalid_argument("Original error");
        }
        catch (const invalid_argument &e) {
            logAndRethrow(e);
        }
    }
    catch (const invalid_argument &e) {
        cout << "Caught re-thrown: " << e.what() << endl;
    }
    
    return 0;
}
```

### noexcept Specification
```cpp
#include <iostream>
using namespace std;

// Function that guarantees not to throw
void safeFunction() noexcept {
    cout << "Safe operation" << endl;
    // throw runtime_error("Error");  // Would cause terminate()
}

// Function that may throw
void mayThrow() {
    throw runtime_error("Error!");
}

int main() {
    safeFunction();
    
    try {
        mayThrow();
    }
    catch (const exception &e) {
        cout << "Caught: " << e.what() << endl;
    }
    
    return 0;
}
```

### Standard Exception Types
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    // logic_error exceptions
    try {
        throw invalid_argument("Bad argument");
    } catch (const exception &e) {
        cout << "1. " << e.what() << endl;
    }
    
    // runtime_error exceptions
    try {
        throw runtime_error("Runtime problem");
    } catch (const exception &e) {
        cout << "2. " << e.what() << endl;
    }
    
    // out_of_range
    try {
        vector<int> v = {1, 2, 3};
        v.at(10);  // Throws out_of_range
    } catch (const out_of_range &e) {
        cout << "3. " << e.what() << endl;
    }
    
    return 0;
}
```

### Function try-catch
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

class MyClass {
public:
    MyClass(int val) try : value(val) {
        if (val < 0) {
            throw invalid_argument("Negative value");
        }
    }
    catch (const invalid_argument &e) {
        cout << "Constructor failed: " << e.what() << endl;
        value = 0;
    }
    
private:
    int value;
};

int main() {
    MyClass obj(-5);
    return 0;
}
```

### Exception in Destructor (Dangerous!)
```cpp
#include <iostream>
using namespace std;

class Resource {
public:
    ~Resource() {
        // DANGEROUS: Never throw in destructor
        // cout << (1 / 0);  // Would call terminate()
        
        // Instead, handle errors gracefully
        cout << "Resource cleanup" << endl;
    }
};

int main() {
    try {
        Resource r;
        throw runtime_error("Error");
    }
    catch (const exception &e) {
        cout << "Caught: " << e.what() << endl;
    }
    
    return 0;
}
```

## Standard Exception Hierarchy
```
exception
├── logic_error
│   ├── invalid_argument
│   ├── length_error
│   ├── out_of_range
│   └── ...
└── runtime_error
    ├── overflow_error
    ├── underflow_error
    └── ...
```

## Exception Best Practices
1. Throw by value, catch by const reference
2. Use standard exceptions when possible
3. Never throw in destructors
4. Use `noexcept` when function doesn't throw
5. Provide meaningful error messages
6. Clean up with RAII, not try-finally
7. Catch specific exceptions first
8. Avoid throwing exceptions in destructors

## Common Standard Exceptions
| Exception | When |
|-----------|------|
| `invalid_argument` | Bad parameter value |
| `out_of_range` | Index out of bounds |
| `runtime_error` | Runtime failure |
| `logic_error` | Logic violation |
| `bad_alloc` | Memory allocation failed |
