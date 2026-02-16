# static Keyword

## Summary
The `static` keyword controls variable visibility and lifetime. For global variables, it limits visibility to the current file. For function-local variables, it makes them persist across function calls. For class members, it makes them shared by all instances.

## Key Concepts
- **Static Variables**: Persist for entire program duration
- **Static Functions**: File scope only (at file level)
- **Static Members**: Shared by all instances of a class
- **Initialization**: Initialized once at program start
- **Scope**: Global static = file scope, local static = function scope

## Code Examples

### Static Local Variables
```cpp
#include <iostream>
using namespace std;

void counter() {
    static int count = 0;  // Initialized once
    count++;
    cout << "Call count: " << count << endl;
}

int main() {
    counter();  // Count: 1
    counter();  // Count: 2
    counter();  // Count: 3
    counter();  // Count: 4
    
    return 0;
}
```

### Static Global Variables
```cpp
// file1.cpp
static int globalVar = 100;  // Visible only in file1.cpp

void printGlobal() {
    cout << "Global: " << globalVar << endl;
}

// file2.cpp - cannot access globalVar from file1
// The following would NOT work if in different file:
// extern int globalVar;  // Would cause linker error
// cout << globalVar;     // Cannot access file1's static variable
```

### Static Member Variables
```cpp
#include <iostream>
using namespace std;

class Student {
private:
    string name;
    static int totalStudents;  // Shared by all instances
    
public:
    Student(string n) : name(n) {
        totalStudents++;
    }
    
    ~Student() {
        totalStudents--;
    }
    
    static int getTotalStudents() {
        return totalStudents;
    }
    
    string getName() { return name; }
};

// Define and initialize static member
int Student::totalStudents = 0;

int main() {
    cout << "Initial: " << Student::getTotalStudents() << endl;  // 0
    
    Student s1("Alice");
    cout << "After s1: " << Student::getTotalStudents() << endl; // 1
    
    Student s2("Bob");
    cout << "After s2: " << Student::getTotalStudents() << endl; // 2
    
    {
        Student s3("Charlie");
        cout << "Inside block: " << Student::getTotalStudents() << endl; // 3
    }
    
    cout << "After block: " << Student::getTotalStudents() << endl;     // 2
    
    return 0;
}
```

### Static Member Function
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Configuration {
private:
    static Configuration *instance;
    string configData;
    
public:
    // Static member function
    static Configuration* getInstance() {
        if (instance == nullptr) {
            instance = new Configuration();
        }
        return instance;
    }
    
    void setData(string data) {
        configData = data;
    }
    
    string getData() {
        return configData;
    }
};

// Initialize static member
Configuration* Configuration::instance = nullptr;

int main() {
    Configuration *config1 = Configuration::getInstance();
    config1->setData("Setting1");
    
    Configuration *config2 = Configuration::getInstance();
    cout << "config2 data: " << config2->getData() << endl;  // Same as config1
    
    return 0;
}
```

### Static Constants in Classes
```cpp
#include <iostream>
#include <array>
using namespace std;

class Matrix {
public:
    static const int SIZE = 3;
    static constexpr double PI = 3.14159;
    
private:
    double data[SIZE][SIZE];
    
public:
    void display() {
        cout << "Matrix size: " << SIZE << "x" << SIZE << endl;
    }
};

int main() {
    cout << "Matrix::SIZE: " << Matrix::SIZE << endl;
    cout << "Matrix::PI: " << Matrix::PI << endl;
    
    // Can use in array declaration
    array<int, Matrix::SIZE> arr;
    cout << "Array size: " << arr.size() << endl;
    
    Matrix m;
    m.display();
    
    return 0;
}
```

### Static Function in Class
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Math {
public:
    // Static member function - no 'this' pointer
    static int power(int base, int exp) {
        int result = 1;
        for (int i = 0; i < exp; i++) {
            result *= base;
        }
        return result;
    }
    
    static double average(const vector<double> &values) {
        double sum = 0;
        for (double val : values) {
            sum += val;
        }
        return values.empty() ? 0 : sum / values.size();
    }
};

int main() {
    // Call static function without object
    cout << "2^4 = " << Math::power(2, 4) << endl;
    
    vector<double> grades = {95.0, 87.5, 92.0};
    cout << "Average: " << Math::average(grades) << endl;
    
    return 0;
}
```

### Static Variables in Functions
```cpp
#include <iostream>
using namespace std;

class Logger {
public:
    static void log(const string &message) {
        static int logCount = 0;
        static ofstream logFile("log.txt");
        
        logCount++;
        logFile << "[" << logCount << "] " << message << endl;
        cout << "Logged: " << message << endl;
    }
};

int main() {
    Logger::log("Starting application");
    Logger::log("Processing data");
    Logger::log("Completing task");
    
    return 0;
}
```

### Static Data Across Calls
```cpp
#include <iostream>
using namespace std;

class FileManager {
public:
    static FILE* openFile(const string &filename) {
        static map<string, FILE*> openFiles;
        
        if (openFiles.find(filename) == openFiles.end()) {
            openFiles[filename] = fopen(filename.c_str(), "r");
            cout << "Opening: " << filename << endl;
        } else {
            cout << "File already open: " << filename << endl;
        }
        
        return openFiles[filename];
    }
};
```

### Static Constructor Pattern
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Registry {
private:
    static vector<string> registered;
    
    // Static initialization helper
    static bool initialize() {
        registered.push_back("Default Item");
        cout << "Registry initialized" << endl;
        return true;
    }
    
    static bool initialized;
    
public:
    static void add(const string &item) {
        registered.push_back(item);
    }
    
    static void display() {
        for (const auto &item : registered) {
            cout << item << endl;
        }
    }
};

// Initialize static members
vector<string> Registry::registered;
bool Registry::initialized = Registry::initialize();

int main() {
    Registry::add("Item1");
    Registry::add("Item2");
    Registry::display();
    
    return 0;
}
```

### Static vs Global Scope
```cpp
// example.cpp

// Global - visible from other files (external linkage)
int globalVar = 100;

// Static global - visible only in this file (internal linkage)
static int staticVar = 200;

void printVars() {
    cout << "Global: " << globalVar << endl;
    cout << "Static: " << staticVar << endl;
}

int main() {
    printVars();
    return 0;
}

// Other files can access globalVar with 'extern int globalVar;'
// But cannot access staticVar
```

### Static in Inheritance
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    static int count;
    
    Base() { count++; }
};

int Base::count = 0;

class Derived : public Base {
    // Inherits static count from Base
};

int main() {
    Base b;
    cout << "After b: " << Base::count << endl;  // 1
    
    Derived d;
    cout << "After d: " << Base::count << endl;  // 2
    
    cout << "Derived::count: " << Derived::count << endl;  // Same as Base
    
    return 0;
}
```

## Static Keyword Summary
| Context | Meaning |
|---------|---------|
| Local variable | Persists across calls |
| Global variable | File-local visibility |
| Member variable | Shared by all instances |
| Member function | No `this` pointer, file-local |

## Lifetime and Initialization
- Static variables initialized once at program start
- Destroyed when program ends
- Thread-safe initialization (C++11)

## Best Practices
1. Use static local variables for persistent state
2. Use static members for shared class state
3. Avoid global static variables (use namespaces)
4. Initialize static members outside class
5. Use static member functions for utilities
6. Remember static members are not polymorphic
