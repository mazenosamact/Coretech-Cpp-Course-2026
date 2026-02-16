# Pair and Tuple

## Summary
`pair` and `tuple` are containers that group related values of potentially different types. `pair` holds exactly two values, while `tuple` can hold any number of values, providing convenient heterogeneous data structures.

## Key Concepts
- **pair**: Two-element container
- **tuple**: Variable-length heterogeneous container
- **Type Safety**: Each element can have different type
- **Structured Binding**: C++17 unpacking
- **make_pair/make_tuple**: Helper functions

## Code Examples

### Basic pair Usage
```cpp
#include <iostream>
#include <utility>
using namespace std;

int main() {
    // Create pair different ways
    pair<int, string> p1(1, "apple");
    pair<int, string> p2 = {2, "banana"};
    auto p3 = make_pair(3, "cherry");
    
    // Access elements
    cout << "p1.first: " << p1.first << endl;
    cout << "p1.second: " << p1.second << endl;
    
    // Modify elements
    p1.first = 10;
    p1.second = "modified";
    
    cout << "p1 modified: " << p1.first << " " << p1.second << endl;
    
    return 0;
}
```

### pair in Containers
```cpp
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main() {
    vector<pair<string, int>> students;
    
    students.push_back({"Alice", 95});
    students.push_back(make_pair("Bob", 87));
    students.emplace_back("Charlie", 92);
    
    for (const auto &p : students) {
        cout << p.first << ": " << p.second << endl;
    }
    
    return 0;
}
```

### pair Comparison
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<pair<int, string>> data = {
        {3, "three"},
        {1, "one"},
        {2, "two"}
    };
    
    // Sort by first element (default)
    sort(data.begin(), data.end());
    
    cout << "Sorted pairs:" << endl;
    for (const auto &[num, text] : data) {
        cout << num << ": " << text << endl;
    }
    
    return 0;
}
```

### Basic tuple Usage
```cpp
#include <iostream>
#include <tuple>
using namespace std;

int main() {
    // Create tuple different ways
    tuple<int, double, string> t1(42, 3.14, "hello");
    auto t2 = make_tuple(100, 2.71, "world");
    
    // Access by index
    cout << "t1[0]: " << get<0>(t1) << endl;
    cout << "t1[1]: " << get<1>(t1) << endl;
    cout << "t1[2]: " << get<2>(t1) << endl;
    
    // Modify
    get<0>(t1) = 50;
    cout << "Modified t1[0]: " << get<0>(t1) << endl;
    
    return 0;
}
```

### Tuple Unpacking (C++17)
```cpp
#include <iostream>
#include <tuple>
using namespace std;

int main() {
    auto t = make_tuple(42, 3.14, "hello");
    
    // Structured binding
    auto [x, y, z] = t;
    
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "z: " << z << endl;
    
    // Partial unpacking
    auto [first, second] = make_pair("Alice", 95);
    cout << "Name: " << first << ", Score: " << second << endl;
    
    return 0;
}
```

### tuple from Function
```cpp
#include <iostream>
#include <tuple>
#include <string>
using namespace std;

// Return multiple values
tuple<int, double, string> getData() {
    return make_tuple(42, 3.14, "data");
}

// Alternative using tuple
pair<int, string> getCredentials() {
    return {"admin", "password123"};
}

int main() {
    auto [num, pi, text] = getData();
    cout << "Got: " << num << ", " << pi << ", " << text << endl;
    
    auto [user, pass] = getCredentials();
    cout << "User: " << user << endl;
    
    return 0;
}
```

### tuple Iteration (C++17)
```cpp
#include <iostream>
#include <tuple>
using namespace std;

// Helper to print tuple
template<typename Tuple, size_t Index = 0>
void printTuple(const Tuple &t) {
    if constexpr (Index < tuple_size_v<Tuple>) {
        cout << get<Index>(t);
        if constexpr (Index + 1 < tuple_size_v<Tuple>) {
            cout << ", ";
        }
        printTuple<Tuple, Index + 1>(t);
    }
}

int main() {
    auto t = make_tuple(1, "two", 3.0);
    cout << "Tuple: ";
    printTuple(t);
    cout << endl;
    
    return 0;
}
```

### pair with map
```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> scores;
    
    // Insert using pair
    scores.insert({"Alice", 95});
    scores.insert(make_pair("Bob", 87));
    
    // Iterate - each element is pair
    for (const auto &[name, score] : scores) {
        cout << name << ": " << score << endl;
    }
    
    return 0;
}
```

### tuple with Types
```cpp
#include <iostream>
#include <tuple>
using namespace std;

int main() {
    // Different types in tuple
    tuple<int, float, double, string, char> complex_t(
        42, 3.14f, 2.71, "hello", 'A'
    );
    
    cout << "Integer: " << get<0>(complex_t) << endl;
    cout << "Float: " << get<1>(complex_t) << endl;
    cout << "Double: " << get<2>(complex_t) << endl;
    cout << "String: " << get<3>(complex_t) << endl;
    cout << "Char: " << get<4>(complex_t) << endl;
    
    cout << "Tuple size: " << tuple_size<decltype(complex_t)>::value << endl;
    
    return 0;
}
```

### pair Swap
```cpp
#include <iostream>
#include <utility>
using namespace std;

int main() {
    pair<int, string> p1(1, "Alice");
    pair<int, string> p2(2, "Bob");
    
    cout << "Before swap:" << endl;
    cout << "p1: " << p1.first << " " << p1.second << endl;
    cout << "p2: " << p2.first << " " << p2.second << endl;
    
    swap(p1, p2);
    
    cout << "\nAfter swap:" << endl;
    cout << "p1: " << p1.first << " " << p1.second << endl;
    cout << "p2: " << p2.first << " " << p2.second << endl;
    
    return 0;
}
```

### Advanced: tuple Concatenation
```cpp
#include <iostream>
#include <tuple>
using namespace std;

// Helper to concatenate tuples
template<typename T1, typename T2, size_t... I1, size_t... I2>
auto concatenate_impl(const T1 &t1, const T2 &t2,
                      index_sequence<I1...>, index_sequence<I2...>) {
    return make_tuple(get<I1>(t1)..., get<I2>(t2)...);
}

template<typename T1, typename T2>
auto concatenate(const T1 &t1, const T2 &t2) {
    return concatenate_impl(t1, t2,
        make_index_sequence<tuple_size<T1>::value>{},
        make_index_sequence<tuple_size<T2>::value>{});
}

int main() {
    auto t1 = make_tuple(1, "two");
    auto t2 = make_tuple(3.0, 'a');
    
    auto combined = concatenate(t1, t2);
    auto [a, b, c, d] = combined;
    
    cout << a << " " << b << " " << c << " " << d << endl;
    
    return 0;
}
```

### pair as Return Type
```cpp
#include <iostream>
#include <utility>
#include <string>
using namespace std;

// Return success/failure with value
pair<bool, string> login(const string &user, const string &pass) {
    if (user == "admin" && pass == "secret") {
        return {true, "Login successful"};
    }
    return {false, "Invalid credentials"};
}

int main() {
    auto [success, message] = login("admin", "secret");
    cout << (success ? "Success" : "Failed") << ": " << message << endl;
    
    auto [s2, m2] = login("guest", "wrong");
    cout << (s2 ? "Success" : "Failed") << ": " << m2 << endl;
    
    return 0;
}
```

## pair vs tuple
| Feature | pair | tuple |
|---------|------|-------|
| Elements | Exactly 2 | Any number |
| Type Safety | Strongly typed | Strongly typed |
| Access | `.first`, `.second` | `get<>()` |
| Unpacking | Limited | Full (C++17) |
| Size | 2 | Variable |

## Common Use Cases
| Type | Use |
|------|-----|
| pair | Key-value, coordinates, results |
| tuple | Complex return types, multiple values |
| map values | Composite key lookups |
| Function returns | Multiple return values |

## Best Practices
1. Use `pair` for simple two-value groups
2. Use `tuple` when you need more elements
3. Use structured bindings (C++17) to unpack
4. Use `get<>()` for indexed access
5. Name the values with structured binding
6. Consider using struct for named fields instead
7. Use `make_pair()` and `make_tuple()` for deduction
