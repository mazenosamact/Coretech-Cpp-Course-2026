# Lambda Expressions

## Summary
Lambda expressions are small anonymous functions introduced in C++11. They allow you to define and pass functions as arguments without creating formal function objects, enabling concise functional programming patterns.

## Key Concepts
- **Anonymous**: Functions without names
- **Capture**: Access local variables
- **Closure**: Function with captured state
- **In-place**: Define where needed
- **STL Integration**: Works seamlessly with algorithms

## Code Examples

### Basic Lambda Expression
```cpp
#include <iostream>
using namespace std;

int main() {
    // Simple lambda: no parameters, no capture
    auto greet = []() {
        cout << "Hello from lambda!" << endl;
    };
    
    greet();  // Call the lambda
    
    // Lambda with parameters
    auto add = [](int a, int b) {
        return a + b;
    };
    
    cout << "3 + 5 = " << add(3, 5) << endl;
    
    return 0;
}
```

### Lambda Syntax Breakdown
```cpp
#include <iostream>
using namespace std;

int main() {
    // [capture] (parameters) -> return_type { body }
    
    // No capture, no parameters
    auto lambda1 = []() { cout << "Lambda 1" << endl; };
    
    // Capture by value, with parameters
    int x = 10;
    auto lambda2 = [x](int y) { cout << x + y << endl; };
    
    // Explicit return type
    auto lambda3 = [](int a, int b) -> int {
        return a * b;
    };
    
    // Type deduction (no return type specified)
    auto lambda4 = [](int a) {
        return a * 2;
    };
    
    lambda1();
    lambda2(5);      // x=10 (captured), y=5 (parameter)
    cout << lambda3(3, 4) << endl;
    cout << lambda4(7) << endl;
    
    return 0;
}
```

### Capture by Value
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5, y = 10;
    
    // Capture by value: [x, y]
    auto print = [x, y]() {
        cout << "x = " << x << ", y = " << y << endl;
    };
    
    x = 100;
    y = 200;
    
    print();  // Still prints x=5, y=10 (captured values)
    
    return 0;
}
```

### Capture by Reference
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5;
    
    // Capture by reference: [&x]
    auto modify = [&x]() {
        x = x * 2;
        cout << "Inside lambda: x = " << x << endl;
    };
    
    modify();
    cout << "Outside lambda: x = " << x << endl;  // x is modified
    
    return 0;
}
```

### Mixed Capture
```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 10;
    int factor = 2;
    
    // Capture value by value, factor by reference
    auto calc = [value, &factor](int input) {
        factor = 5;  // Modifies original
        return value + input * factor;
    };
    
    cout << "Result: " << calc(3) << endl;  // 10 + 3*5 = 25
    cout << "Factor after lambda: " << factor << endl;  // 5
    
    return 0;
}
```

### Default Capture
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5, y = 10, z = 15;
    
    // Capture all by value: [=]
    auto lambda1 = [=]() {
        cout << "Values: " << x << ", " << y << ", " << z << endl;
    };
    
    // Capture all by reference: [&]
    auto lambda2 = [&]() {
        x = y = z = 100;
    };
    
    lambda1();  // 5, 10, 15
    lambda2();
    lambda1();  // Still 5, 10, 15 (but x, y, z are now 100)
    
    return 0;
}
```

### Lambda with STL Algorithms
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    
    // forEach with lambda
    cout << "All numbers: ";
    for_each(nums.begin(), nums.end(), [](int n) {
        cout << n << " ";
    });
    cout << endl;
    
    // Filter using lambda
    int threshold = 3;
    cout << "Numbers > " << threshold << ": ";
    for_each(nums.begin(), nums.end(), [threshold](int n) {
        if (n > threshold) cout << n << " ";
    });
    cout << endl;
    
    return 0;
}
```

### Lambda with sort
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<pair<string, int>> students = {
        {"Alice", 85},
        {"Bob", 92},
        {"Charlie", 78}
    };
    
    // Sort by second element (grade) in descending order
    sort(students.begin(), students.end(), 
         [](const pair<string, int> &a, const pair<string, int> &b) {
             return a.second > b.second;
         });
    
    cout << "Sorted by grade (descending):" << endl;
    for (const auto &student : students) {
        cout << student.first << ": " << student.second << endl;
    }
    
    return 0;
}
```

### Mutable Lambda
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5;
    
    // Mutable allows modification of captured copies
    auto modifyCapture = [x]() mutable {
        x = x * 2;
        cout << "Inside (modified): x = " << x << endl;
    };
    
    modifyCapture();
    cout << "Outside: x = " << x << endl;  // Still 5
    
    return 0;
}
```

### Lambda as Function Argument
```cpp
#include <iostream>
#include <functional>
using namespace std;

void execute(function<void(int)> callback, int value) {
    cout << "Executing callback..." << endl;
    callback(value);
}

int main() {
    execute([](int n) {
        cout << "Received: " << n << endl;
    }, 42);
    
    return 0;
}
```

### Lambda Returning Complex Values
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Lambda returning sum
    auto getSum = [](const vector<int> &v) -> int {
        int sum = 0;
        for (int n : v) sum += n;
        return sum;
    };
    
    cout << "Sum: " << getSum(numbers) << endl;
    
    // Lambda returning struct-like result
    auto getStats = [](const vector<int> &v) {
        struct Stats { int min, max, sum; };
        int min = v[0], max = v[0], sum = 0;
        for (int n : v) {
            min = (n < min) ? n : min;
            max = (n > max) ? n : max;
            sum += n;
        }
        return Stats{min, max, sum};
    };
    
    auto stats = getStats(numbers);
    cout << "Min: " << stats.min << ", Max: " << stats.max 
         << ", Sum: " << stats.sum << endl;
    
    return 0;
}
```

### Lambda with find_if
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> nums = {10, 25, 30, 15, 45, 50};
    
    // Find first number greater than 30
    auto it = find_if(nums.begin(), nums.end(), 
                      [](int n) { return n > 30; });
    
    if (it != nums.end()) {
        cout << "Found: " << *it << endl;
    }
    
    return 0;
}
```

### Nested Lambdas
```cpp
#include <iostream>
#include <functional>
using namespace std;

int main() {
    // Lambda that returns a lambda
    auto makeAdder = [](int x) {
        return [x](int y) {
            return x + y;
        };
    };
    
    auto add5 = makeAdder(5);
    cout << "5 + 3 = " << add5(3) << endl;
    
    return 0;
}
```

## Lambda Capture Options
| Syntax | Meaning |
|--------|---------|
| `[]` | No capture |
| `[=]` | All by value |
| `[&]` | All by reference |
| `[x]` | x by value |
| `[&x]` | x by reference |
| `[=, &x]` | All by value except x by ref |
| `[&, x]` | All by ref except x by value |

## Common Patterns
| Use Case | Example |
|----------|---------|
| Filtering | `find_if` with lambda condition |
| Transformation | `transform` with lambda |
| Sorting | `sort` with custom comparator |
| Aggregation | `accumulate` with lambda |
| Iteration | `for_each` with lambda |

## Best Practices
- Use lambdas for short, simple operations
- Prefer named functions for complex logic
- Be careful with lambda lifetimes
- Use `auto` for lambda variables
- Capture only what you need
- Use const references for large objects
