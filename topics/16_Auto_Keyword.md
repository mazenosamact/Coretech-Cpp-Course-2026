# auto Keyword

## Summary
The `auto` keyword enables type deduction, allowing the compiler to automatically determine the type of a variable based on its initializer. This reduces verbosity, improves code maintainability, and is essential for working with complex types.

## Key Concepts
- **Type Deduction**: Compiler infers type from initialization
- **Simplifies Code**: Reduces verbose type declarations
- **Template Integration**: Works with generic programming
- **Not Lazy**: Type is determined at compile-time
- **Range-based Loops**: Works perfectly with STL containers

## Code Examples

### Basic auto Usage
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // Without auto - verbose
    vector<int> vec1 = {1, 2, 3, 4, 5};
    vector<int>::iterator it1 = vec1.begin();
    
    // With auto - concise
    auto vec2 = vector<int>{1, 2, 3, 4, 5};
    auto it2 = vec2.begin();
    
    // Simple types
    auto x = 42;                // int
    auto y = 3.14;              // double
    auto str = "Hello";         // const char*
    auto name = string("John");  // string
    
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "str: " << str << endl;
    cout << "name: " << name << endl;
    
    return 0;
}
```

### auto with Container Iteration
```cpp
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    vector<int> numbers = {10, 20, 30, 40, 50};
    
    // Without auto
    for (vector<int>::iterator it = numbers.begin(); 
         it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // With auto
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Range-based for (C++11)
    for (auto num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Works with maps
    map<string, int> scores = {{"Alice", 95}, {"Bob", 87}};
    for (auto pair : scores) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    return 0;
}
```

### auto with Function Return Types
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

auto getVector() {
    return vector<int>{1, 2, 3, 4, 5};
}

auto findMax(const vector<int> &v) {
    return *max_element(v.begin(), v.end());
}

int main() {
    auto vec = getVector();
    auto max = findMax(vec);
    
    cout << "Vector size: " << vec.size() << endl;
    cout << "Max element: " << max << endl;
    
    return 0;
}
```

### auto with Complex Types
```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    // Without auto - very verbose
    map<string, vector<pair<int, double>>> complex1;
    map<string, vector<pair<int, double>>>::iterator it1;
    
    // With auto - concise
    auto complex2 = map<string, vector<pair<int, double>>>();
    auto it2 = complex2.begin();
    
    // Lambda with auto
    auto multiply = [](int a, int b) { return a * b; };
    cout << "3 * 4 = " << multiply(3, 4) << endl;
    
    // Function pointers are easier with auto
    auto pFunc = &multiply;
    // cout << "Using pointer: " << (*pFunc)(5, 6) << endl;
    
    return 0;
}
```

### auto with Pointers and References
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int x = 42;
    string name = "Alice";
    
    // auto deduces pointer type
    auto ptr = &x;            // int*
    cout << "Pointer value: " << *ptr << endl;
    
    // auto deduces reference type
    auto &ref = name;         // string&
    ref = "Bob";
    cout << "Reference value: " << name << endl;
    
    // Const auto
    const auto &constRef = name;
    cout << "Const reference: " << constRef << endl;
    
    // Const pointer
    auto const constPtr = &x;
    cout << "Const pointer: " << *constPtr << endl;
    
    return 0;
}
```

### auto in Structured Bindings (C++17)
```cpp
#include <iostream>
#include <tuple>
#include <map>
using namespace std;

int main() {
    // Tuple unpacking
    auto [x, y, z] = tuple<int, double, string>(1, 2.5, "text");
    cout << "x=" << x << ", y=" << y << ", z=" << z << endl;
    
    // Map iteration with structured bindings
    map<string, int> scores = {{"Alice", 95}, {"Bob", 87}};
    for (auto [name, score] : scores) {
        cout << name << ": " << score << endl;
    }
    
    return 0;
}
```

### auto Deduction Rules
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Deduction without pointers/references
    auto a = 42;              // int
    auto b = 42.0;            // double
    auto c = "text";          // const char*
    
    // Deduction with pointers
    int x = 10;
    auto ptr = &x;            // int* (removes &)
    
    // Deduction with const
    const int y = 20;
    auto z = y;               // int (removes const)
    
    // Deduction with references
    int w = 30;
    auto &ref = w;            // int& (keeps reference)
    
    // Deduction with const references
    auto &constRef = y;       // const int& (keeps const)
    
    cout << "a: " << a << endl;
    cout << "z: " << z << endl;
    
    return 0;
}
```

### auto with STL Algorithms
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    
    // Using auto with algorithms
    auto doubled = vector<int>();
    transform(nums.begin(), nums.end(), back_inserter(doubled),
              [](int n) { return n * 2; });
    
    auto count_even = count_if(nums.begin(), nums.end(),
                               [](int n) { return n % 2 == 0; });
    
    auto sum = accumulate(nums.begin(), nums.end(), 0);
    
    cout << "Doubled: ";
    for (auto n : doubled) cout << n << " ";
    cout << endl;
    
    cout << "Count even: " << count_even << endl;
    cout << "Sum: " << sum << endl;
    
    return 0;
}
```

### auto with Classes
```cpp
#include <iostream>
using namespace std;

class Calculator {
public:
    int add(int a, int b) { return a + b; }
    int multiply(int a, int b) { return a * b; }
};

int main() {
    auto calc = Calculator();
    auto result1 = calc.add(5, 3);
    auto result2 = calc.multiply(4, 7);
    
    cout << "5 + 3 = " << result1 << endl;
    cout << "4 * 7 = " << result2 << endl;
    
    return 0;
}
```

### Breaking auto Deduction
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<bool> vec = {true, false, true};
    
    // auto deduction with vector<bool> proxy
    // This is a special case - returns proxy object
    auto bit = vec[0];  // Not a bool&, but a bitset proxy
    
    // Explicit type avoids confusion
    bool actualBool = vec[0];
    
    cout << "Size of bit: " << sizeof(bit) << endl;
    cout << "Size of bool: " << sizeof(actualBool) << endl;
    
    return 0;
}
```

## auto Deduction Table
| Expression | Type |
|------------|------|
| `auto x = 42;` | `int` |
| `auto x = 42.0;` | `double` |
| `auto ptr = &x;` | `int*` |
| `auto &ref = x;` | `int&` |
| `const int y = 10;` `auto x = y;` | `int` |
| `auto x = vector<int>();` | `vector<int>` |

## When to Use auto
| Scenario | Benefit |
|----------|---------|
| Iterator declarations | Readability |
| Complex template types | Simplicity |
| Lambda types | Efficiency |
| Function return deduction | Type safety |
| Range-based loops | Convenience |

## When to Avoid auto
- Very simple types where explicit type aids readability
- When documenting expected type
- With template metaprogramming confusion
- When type might change unexpectedly

## Best Practices
1. Use `auto` for complex types and iterators
2. Provide explicit types for clarity when appropriate
3. Use `auto [...]` for structured bindings (C++17+)
4. Combine with meaningful variable names
5. Remember `auto` doesn't deduce references by default
6. Use `const auto &` to avoid unnecessary copies
