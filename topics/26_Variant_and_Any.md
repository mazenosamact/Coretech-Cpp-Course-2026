# Variant and Any

## Summary
`std::variant` is a type-safe union that holds one of several specified types, while `std::any` can hold any type. They provide flexibility and type safety, replacing unsafe void pointers and C-style unions.

## Key Concepts
- **variant**: Holds one of specified types
- **any**: Holds any type dynamically
- **Type Safety**: Compiler-checked types
- **Value Semantics**: Copy and move support
- **No Performance Cost**: Zero overhead abstraction

## Code Examples

### Basic variant Usage
```cpp
#include <iostream>
#include <variant>
#include <string>
using namespace std;

int main() {
    // Declare variant
    variant<int, double, string> v;
    
    // Assign different types
    v = 42;              // int
    cout << "int: " << get<0>(v) << endl;
    
    v = 3.14;            // double
    cout << "double: " << get<1>(v) << endl;
    
    v = "hello";         // string
    cout << "string: " << get<2>(v) << endl;
    
    return 0;
}
```

### variant with index
```cpp
#include <iostream>
#include <variant>
using namespace std;

int main() {
    variant<int, double, string> v = 42;
    
    // Check which type is stored
    cout << "Current index: " << v.index() << endl;  // 0 for int
    
    v = 3.14;
    cout << "Current index: " << v.index() << endl;  // 1 for double
    
    v = "hello";
    cout << "Current index: " << v.index() << endl;  // 2 for string
    
    return 0;
}
```

### variant with visit
```cpp
#include <iostream>
#include <variant>
#include <string>
using namespace std;

int main() {
    variant<int, double, string> v = 42;
    
    // Process variant with visitor
    auto visitor = [](auto &&value) {
        cout << "Value: " << value << endl;
    };
    
    visit(visitor, v);
    
    v = 3.14;
    visit(visitor, v);
    
    v = "hello";
    visit(visitor, v);
    
    return 0;
}
```

### variant with Structured Type Visitor
```cpp
#include <iostream>
#include <variant>
using namespace std;

int main() {
    variant<int, double, string> v;
    
    // Different handlers for different types
    struct Visitor {
        void operator()(int i) const {
            cout << "Integer: " << i << endl;
        }
        
        void operator()(double d) const {
            cout << "Double: " << d << endl;
        }
        
        void operator()(const string &s) const {
            cout << "String: " << s << endl;
        }
    };
    
    v = 42;
    visit(Visitor(), v);
    
    v = 3.14;
    visit(Visitor(), v);
    
    v = "world";
    visit(Visitor(), v);
    
    return 0;
}
```

### Using holds_alternative
```cpp
#include <iostream>
#include <variant>
using namespace std;

int main() {
    variant<int, double, string> v = 42;
    
    if (holds_alternative<int>(v)) {
        cout << "It's an int: " << get<int>(v) << endl;
    }
    
    if (holds_alternative<double>(v)) {
        cout << "It's a double: " << get<double>(v) << endl;
    }
    
    v = "hello";
    if (holds_alternative<string>(v)) {
        cout << "It's a string: " << get<string>(v) << endl;
    }
    
    return 0;
}
```

### variant Exception Safety
```cpp
#include <iostream>
#include <variant>
#include <stdexcept>
using namespace std;

int main() {
    variant<int, double> v = 42;
    
    try {
        // throws bad_variant_access if wrong type
        double d = get<double>(v);
    }
    catch (const bad_variant_access &e) {
        cout << "Wrong type accessed: " << e.what() << endl;
    }
    
    // Safe access with get_if
    if (auto ptr = get_if<int>(&v)) {
        cout << "Got int: " << *ptr << endl;
    }
    
    return 0;
}
```

### variant with Complex Types
```cpp
#include <iostream>
#include <variant>
#include <vector>
using namespace std;

struct Rectangle {
    double width, height;
};

struct Circle {
    double radius;
};

int main() {
    variant<Rectangle, Circle> shape = Rectangle{10, 20};
    
    auto visitor = [](const auto &s) {
        if constexpr (is_same_v<decltype(s), const Rectangle &>) {
            cout << "Rectangle: " << s.width << "x" << s.height << endl;
        } else {
            cout << "Circle: radius " << s.radius << endl;
        }
    };
    
    visit(visitor, shape);
    
    shape = Circle{5.0};
    visit(visitor, shape);
    
    return 0;
}
```

### Basic any Usage
```cpp
#include <iostream>
#include <any>
using namespace std;

int main() {
    // Store any type
    any a = 42;
    cout << "int: " << any_cast<int>(a) << endl;
    
    a = 3.14;
    cout << "double: " << any_cast<double>(a) << endl;
    
    a = string("hello");
    cout << "string: " << any_cast<string>(a) << endl;
    
    // Check type
    cout << "Has value: " << !a.empty() << endl;
    
    return 0;
}
```

### any with type_info
```cpp
#include <iostream>
#include <any>
#include <typeinfo>
using namespace std;

int main() {
    any a = 42;
    
    cout << "Type: " << a.type().name() << endl;
    
    // Check type before casting
    if (a.type() == typeid(int)) {
        cout << "It's an int: " << any_cast<int>(a) << endl;
    }
    
    a = "world";
    cout << "Type: " << a.type().name() << endl;
    
    // Wrong cast would throw bad_any_cast
    try {
        cout << any_cast<int>(a) << endl;
    }
    catch (const bad_any_cast &e) {
        cout << "Wrong cast: " << e.what() << endl;
    }
    
    return 0;
}
```

### any in Containers
```cpp
#include <iostream>
#include <any>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<any> values;
    
    values.push_back(42);
    values.push_back(3.14);
    values.push_back(string("hello"));
    values.push_back(true);
    
    for (const auto &val : values) {
        cout << "Type: " << val.type().name();
        
        if (val.type() == typeid(int)) {
            cout << ", Value: " << any_cast<int>(val);
        } else if (val.type() == typeid(double)) {
            cout << ", Value: " << any_cast<double>(val);
        } else if (val.type() == typeid(string)) {
            cout << ", Value: " << any_cast<string>(val);
        } else if (val.type() == typeid(bool)) {
            cout << ", Value: " << (any_cast<bool>(val) ? "true" : "false");
        }
        
        cout << endl;
    }
    
    return 0;
}
```

### Comparison: variant vs any
```cpp
#include <iostream>
#include <variant>
#include <any>
using namespace std;

int main() {
    // variant: Type-safe, known at compile-time
    variant<int, double> v = 42;
    
    // any: Types known at runtime only
    any a = 42;
    
    // variant is type-safe and doesn't require try-catch
    if (holds_alternative<int>(v)) {
        cout << "Variant has int: " << get<int>(v) << endl;
    }
    
    // any requires type checking or exception handling
    if (a.type() == typeid(int)) {
        cout << "Any has int: " << any_cast<int>(a) << endl;
    }
    
    return 0;
}
```

### variant with Optional
```cpp
#include <iostream>
#include <variant>
#include <optional>
using namespace std;

// Represent success or failure
variant<int, string> divide(int a, int b) {
    if (b == 0) {
        return string("Division by zero");
    }
    return a / b;
}

int main() {
    auto result = divide(10, 2);
    
    if (holds_alternative<int>(result)) {
        cout << "Success: " << get<int>(result) << endl;
    } else {
        cout << "Error: " << get<string>(result) << endl;
    }
    
    auto error = divide(10, 0);
    if (holds_alternative<int>(error)) {
        cout << "Success: " << get<int>(error) << endl;
    } else {
        cout << "Error: " << get<string>(error) << endl;
    }
    
    return 0;
}
```

## variant vs any vs union
| Feature | variant | any | union |
|---------|---------|-----|-------|
| Type Safety | Full | Runtime | None |
| Multiple types | Up to limit | Any | Must know all |
| Memory safe | Yes | Yes | No |
| Performance | Zero-cost | Overhead | Minimal |
| Checking | Compile-time | Runtime | Manual |

## When to Use

| Use Case | Best Option |
|----------|-------------|
| Few known types | variant |
| Many dynamic types | any |
| Multiple owners | shared_ptr<any> |
| Return error | variant<T, Error> |
| Settings dict | map<string, any> |

## Best Practices
1. Prefer `variant` when types are known
2. Use `visit` instead of manual checking
3. Use `get_if()` to avoid exceptions
4. Avoid mixing `variant` and `any`
5. Document why `any` is needed
6. Consider template metaprogramming for `any` alternatives
7. Use `holds_alternative` for type checking
