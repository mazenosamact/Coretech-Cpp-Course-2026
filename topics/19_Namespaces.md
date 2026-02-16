# Namespaces

## Summary
Namespaces organize code into logical groups to avoid naming conflicts. They allow multiple libraries to be used without identifier collisions by providing scope for names.

## Key Concepts
- **Scope**: Avoid name collisions
- **Organization**: Group related code
- **Qualification**: Access using `::`
- **Using**: Bring names into scope
- **Nesting**: Namespaces within namespaces

## Code Examples

### Basic Namespace Declaration
```cpp
#include <iostream>
using namespace std;

namespace Math {
    int add(int a, int b) {
        return a + b;
    }
    
    int multiply(int a, int b) {
        return a * b;
    }
}

namespace String {
    string concatenate(const string &a, const string &b) {
        return a + b;
    }
}

int main() {
    cout << "Sum: " << Math::add(5, 3) << endl;
    cout << "Product: " << Math::multiply(5, 3) << endl;
    cout << "Concatenate: " << String::concatenate("Hello", "World") << endl;
    
    return 0;
}
```

### using Directive
```cpp
#include <iostream>
using namespace std;

namespace Graphics {
    class Shape { };
    class Circle : public Shape { };
    class Rectangle : public Shape { };
}

int main() {
    // Method 1: Qualify each use
    Graphics::Shape s1;
    Graphics::Circle c1;
    
    // Method 2: using directive brings all names into scope
    using namespace Graphics;
    Shape s2;
    Circle c2;
    Rectangle r2;
    
    return 0;
}
```

### using Declaration (Preferred)
```cpp
#include <iostream>
using namespace std;

namespace Math {
    int square(int x) { return x * x; }
    int cube(int x) { return x * x * x; }
}

int main() {
    // Only brings specific names into scope
    using Math::square;
    
    cout << "Square of 5: " << square(5) << endl;
    cout << "Cube of 5: " << Math::cube(5) << endl;  // Must qualify
    
    return 0;
}
```

### Nested Namespaces
```cpp
#include <iostream>
using namespace std;

namespace Company {
    namespace Graphics {
        class Image { };
    }
    
    namespace Audio {
        class Sound { };
    }
}

int main() {
    Company::Graphics::Image img;
    Company::Audio::Sound snd;
    
    cout << "Created image and sound objects" << endl;
    
    return 0;
}
```

### Nested Namespace Access (C++17)
```cpp
#include <iostream>
using namespace std;

// C++17 syntax for nested namespaces
namespace Company::Graphics::Shapes {
    class Circle { };
    class Square { };
}

int main() {
    Company::Graphics::Shapes::Circle c;
    
    return 0;
}
```

### Namespace Aliasing
```cpp
#include <iostream>
using namespace std;

namespace original = std;
namespace gr = Company::Graphics;
namespace au = Company::Audio;

int main() {
    // Shorter aliases
    original::cout << "Hello" << std::endl;
    
    // Can create alias for nested namespace
    // gr::Image img;
    
    return 0;
}
```

### Components in Different Files
```cpp
// math.h
#ifndef MATH_H
#define MATH_H

namespace Math {
    int add(int a, int b);
    int multiply(int a, int b);
}

#endif

// math.cpp
#include "math.h"

namespace Math {
    int add(int a, int b) {
        return a + b;
    }
    
    int multiply(int a, int b) {
        return a * b;
    }
}

// main.cpp
#include "math.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Sum: " << Math::add(5, 3) << endl;
    return 0;
}
```

### Anonymous Namespace (Internal Linkage)
```cpp
#include <iostream>
using namespace std;

// Anonymous namespace - visible only in this file
namespace {
    void helperFunction() {
        cout << "Helper function" << endl;
    }
    
    int internalValue = 100;
}

void publicFunction() {
    helperFunction();  // Can call without qualification
    cout << "Value: " << internalValue << endl;
}

int main() {
    publicFunction();
    helperFunction();  // Can call without qualification
    
    return 0;
}
```

### Namespace for Constants
```cpp
#include <iostream>
using namespace std;

namespace Config {
    const int MAX_USERS = 100;
    const float PI = 3.14159f;
    const string APP_NAME = "MyApp";
}

int main() {
    cout << "Max users: " << Config::MAX_USERS << endl;
    cout << "App name: " << Config::APP_NAME << endl;
    
    return 0;
}
```

### Classes in Namespaces
```cpp
#include <iostream>
using namespace std;

namespace Database {
    class Connection {
    private:
        string connectionString;
        
    public:
        Connection(const string &cs) : connectionString(cs) {}
        
        void connect() {
            cout << "Connected to: " << connectionString << endl;
        }
    };
}

int main() {
    Database::Connection conn("localhost:5432");
    conn.connect();
    
    return 0;
}
```

### Multiple Namespace Declarations
```cpp
#include <iostream>
using namespace std;

// Namespace declared in multiple places
namespace Utils {
    void printLine() {
        cout << "---" << endl;
    }
}

namespace Utils {
    void printGrid() {
        printLine();
    }
}

int main() {
    Utils::printLine();
    Utils::printGrid();
    
    return 0;
}
```

### Extending Standard Library
```cpp
#include <iostream>
#include <string>
using namespace std;

namespace std {
    // Can add functions to existing namespace
    string toUpperCase(const string &str) {
        string result = str;
        for (auto &c : result) {
            c = toupper(c);
        }
        return result;
    }
}

int main() {
    string text = "hello";
    cout << std::toUpperCase(text) << endl;
    
    return 0;
}
```

### Resolving Ambiguities
```cpp
#include <iostream>
using namespace std;

namespace A {
    void print() { cout << "From namespace A" << endl; }
    int x = 10;
}

namespace B {
    void print() { cout << "From namespace B" << endl; }
    int x = 20;
}

int main() {
    A::print();  // Explicitly call A's print
    B::print();  // Explicitly call B's print
    
    cout << "A::x = " << A::x << endl;
    cout << "B::x = " << B::x << endl;
    
    // This would be ambiguous:
    // using namespace A;
    // using namespace B;
    // print();  // ERROR: which print?
    
    return 0;
}
```

### Namespace in Headers
```cpp
// math.h
#ifndef MATH_H
#define MATH_H

namespace My {
    namespace Math {
        class Calculator {
        public:
            static int add(int a, int b);
        };
    }
}

#endif

// math.cpp
#include "math.h"

int My::Math::Calculator::add(int a, int b) {
    return a + b;
}

// main.cpp
#include "math.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Sum: " << My::Math::Calculator::add(5, 3) << endl;
    return 0;
}
```

## Best Practices to Avoid Name Conflicts
| Approach | Example |
|----------|---------|
| Qualification | `std::cout` |
| using declaration | `using std::cout;` |
| Aliasing | `namespace stl = std;` |
| Anonymous namespace | Keep helpers private |
| Nested namespaces | Organization |

## Namespace Design Guidelines
1. Use namespaces for related code groups
2. Keep namespace names short and meaningful
3. Avoid deep nesting (2-3 levels max)
4. Use anonymous namespace for internal utilities
5. Consider using nested namespaces for libraries
6. Don't use `using namespace std;` in headers
7. Use `using` declarations instead of directives

## Common Pattern: versioned API
```cpp
namespace MyLib {
    namespace v1 {
        class API { };
    }
    
    namespace v2 {
        class API { };  // Different version
    }
}
```

## Avoid These Mistakes
- Don't use `using namespace std;` in production code
- Don't nest namespaces too deeply
- Don't pollute namespaces with too many names
- Don't forget to close namespace braces
