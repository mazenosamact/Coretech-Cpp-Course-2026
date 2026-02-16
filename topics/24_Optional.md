# std::optional

## Summary
`std::optional` represents a value that may or may not exist, providing a type-safe alternative to null pointers or sentinel values. It avoids the null-checking boilerplate and makes intent clear.

## Key Concepts
- **Optional Value**: Contains a value or nothing
- **Type Safety**: No null pointers
- **Clear Intent**: Makes optional values explicit
- **Efficient**: No dynamic allocation
- **C++17 Feature**: Part of standard library

## Code Examples

### Basic optional Usage
```cpp
#include <iostream>
#include <optional>
using namespace std;

optional<int> divide(int a, int b) {
    if (b == 0) {
        return nullopt;  // Return nothing
    }
    return a / b;  // Return value
}

int main() {
    auto result1 = divide(10, 2);
    auto result2 = divide(10, 0);
    
    if (result1.has_value()) {
        cout << "10 / 2 = " << result1.value() << endl;
    }
    
    if (result2.has_value()) {
        cout << "10 / 0 = " << result2.value() << endl;
    } else {
        cout << "Division by zero" << endl;
    }
    
    return 0;
}
```

### Checking Value Existence
```cpp
#include <iostream>
#include <optional>
using namespace std;

int main() {
    optional<string> value1 = "Hello";
    optional<string> value2 = nullopt;
    
    // Method 1: has_value()
    if (value1.has_value()) {
        cout << "value1: " << value1.value() << endl;
    }
    
    // Method 2: operator bool
    if (value1) {
        cout << "value1 exists" << endl;
    }
    
    // Method 3: operator*
    if (value1) {
        cout << "value1: " << *value1 << endl;
    }
    
    // Check empty
    if (!value2) {
        cout << "value2 is empty" << endl;
    }
    
    return 0;
}
```

### Default Values
```cpp
#include <iostream>
#include <optional>
using namespace std;

optional<int> findValue(int key) {
    if (key < 0) {
        return nullopt;
    }
    return key * 10;
}

int main() {
    // Use value_or() for default
    int result1 = findValue(5).value_or(0);
    cout << "Result1: " << result1 << endl;  // 50
    
    int result2 = findValue(-1).value_or(-1);
    cout << "Result2: " << result2 << endl;  // -1
    
    return 0;
}
```

### Structured Binding
```cpp
#include <iostream>
#include <optional>
using namespace std;

optional<string> getUsername(int id) {
    if (id == 1) {
        return "alice";
    }
    return nullopt;
}

int main() {
    // C++17 structured binding
    if (auto username = getUsername(1)) {
        cout << "User: " << *username << endl;
    }
    
    if (auto username = getUsername(99)) {
        cout << "User: " << *username << endl;
    } else {
        cout << "User not found" << endl;
    }
    
    return 0;
}
```

### optional with Complex Types
```cpp
#include <iostream>
#include <optional>
using namespace std;

struct Person {
    string name;
    int age;
    
    Person(string n, int a) : name(n), age(a) {}
};

optional<Person> findPerson(int id) {
    if (id == 1) {
        return Person("Alice", 25);
    }
    return nullopt;
}

int main() {
    auto person = findPerson(1);
    if (person) {
        cout << "Name: " << person->name << ", Age: " << person->age << endl;
    }
    
    auto notFound = findPerson(99);
    cout << "Found: " << (notFound ? "Yes" : "No") << endl;
    
    return 0;
}
```

### Mapping and Transforming
```cpp
#include <iostream>
#include <optional>
#include <string>
using namespace std;

optional<int> parseInt(const string &str) {
    try {
        return stoi(str);
    } catch (...) {
        return nullopt;
    }
}

int main() {
    auto num = parseInt("42");
    
    // Transform with map-like operations
    if (num && *num > 0) {
        cout << "Positive number: " << *num << endl;
    }
    
    auto invalid = parseInt("abc");
    if (!invalid) {
        cout << "Not a valid number" << endl;
    }
    
    return 0;
}
```

### Constructor and Assignment
```cpp
#include <iostream>
#include <optional>
using namespace std;

int main() {
    // Different ways to create optional
    optional<int> opt1;              // Empty
    optional<int> opt2 = nullopt;    // Empty
    optional<int> opt3 = 42;         // With value
    optional<int> opt4{100};         // With value
    
    cout << "opt1 empty: " << (!opt1 ? "yes" : "no") << endl;
    cout << "opt3 value: " << *opt3 << endl;
    
    // Reset to empty
    opt3 = nullopt;
    cout << "opt3 after reset: " << (!opt3 ? "empty" : "has value") << endl;
    
    // Assign new value
    opt3 = 200;
    cout << "opt3 new value: " << *opt3 << endl;
    
    return 0;
}
```

### optional as Return Type
```cpp
#include <iostream>
#include <optional>
#include <vector>
using namespace std;

optional<int> findIndex(const vector<int> &v, int value) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == value) {
            return i;  // Found
        }
    }
    return nullopt;  // Not found
}

int main() {
    vector<int> nums = {10, 20, 30, 40, 50};
    
    auto idx1 = findIndex(nums, 30);
    if (idx1) {
        cout << "Found at index: " << *idx1 << endl;
    }
    
    auto idx2 = findIndex(nums, 99);
    if (idx2) {
        cout << "Found" << endl;
    } else {
        cout << "Not found" << endl;
    }
    
    return 0;
}
```

### Chaining optionals
```cpp
#include <iostream>
#include <optional>
using namespace std;

optional<int> getFirst() {
    return 10;
}

optional<int> getSecond(int prev) {
    if (prev > 5) {
        return prev * 2;
    }
    return nullopt;
}

int main() {
    // Chain operations
    if (auto first = getFirst()) {
        if (auto second = getSecond(*first)) {
            cout << "First: " << *first << ", Second: " << *second << endl;
        }
    }
    
    // Or using nested optionals
    auto result = getFirst().and_then([](int first) {
        return getSecond(first);
    });
    
    if (result) {
        cout << "Result: " << *result << endl;
    }
    
    return 0;
}
```

### optional vs Pointers
```cpp
#include <iostream>
#include <optional>
using namespace std;

// Old style with pointers
int *divide_ptr(int a, int b) {
    if (b == 0) {
        return nullptr;
    }
    static int result = a / b;
    return &result;
}

// Modern style with optional
optional<int> divide_optional(int a, int b) {
    if (b == 0) {
        return nullopt;
    }
    return a / b;
}

int main() {
    // Pointer style - less clear intent
    if (int *result = divide_ptr(10, 2)) {
        cout << "Pointer result: " << *result << endl;
    }
    
    // optional style - clearer intent
    if (auto result = divide_optional(10, 2)) {
        cout << "Optional result: " << *result << endl;
    }
    
    return 0;
}
```

## optional Member Functions
| Method | Purpose |
|--------|---------|
| `has_value()` | Check if contains value |
| `value()` | Get value (throws if empty) |
| `value_or()` | Get value or default |
| `operator bool` | Implicit conversion to bool |
| `operator*` | Dereference operator |
| `operator->` | Arrow operator |
| `reset()` | Clear the value |
| `emplace()` | Construct in-place |

## Comparisons with Alternatives
| Approach | Pros | Cons |
|----------|------|------|
| optional | Type-safe, clear | C++17 only |
| Pointers | Traditional | Null unsafe |
| Exceptions | Can propagate errors | Slower |
| Return codes | Simple | Unclear intent |

## Best Practices
1. Use `optional` for truly optional values
2. Use `value_or()` for defaults
3. Use structured bindings (C++17)
4. Avoid `.value()` without checking (throws)
5. Prefer `operator*` over `.value()` when checking
6. Use `and_then()` for chaining
7. Return `optional` instead of null pointers

## Common Uses
- Search functions that may not find results
- Parsing/conversion that might fail
- Looking up values from containers
- Function parameters that are truly optional
- Making intent explicit to readers
