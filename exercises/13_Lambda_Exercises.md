# Lambda Expressions - Practical Exercises

## Exercise 1: Callbacks in Event System (Embedded/Backend)
**Context:** Implement event handlers using lambdas for GPIO interrupts.

**Problem:**
```cpp
// Create event system:
// 1. Button event with lambda callback
// 2. Timer event with delayed action
// 3. State change with captured variables
// 4. Multiple event handlers
```

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class EventSystem {
private:
    vector<function<void()>> button_handlers;
    int button_press_count = 0;
    
public:
    void registerButtonHandler(function<void()> handler) {
        button_handlers.push_back(handler);
    }
    
    void simulateButtonPress() {
        button_press_count++;
        cout << "Button pressed (count: " << button_press_count << ")" << endl;
        
        for (auto &handler : button_handlers) {
            handler();
        }
    }
};

int main() {
    cout << "=== Lambda Event System ===" << endl;
    
    EventSystem events;
    int led_state = 0;
    
    cout << "\n--- Registering event handlers ---" << endl;
    
    // Lambda 1: Toggle LED
    events.registerButtonHandler([&led_state]() {
        led_state = !led_state;
        cout << "  → LED " << (led_state ? "ON" : "OFF") << endl;
    });
    
    // Lambda 2: Log press
    events.registerButtonHandler([]() {
        cout << "  → Button event logged" << endl;
    });
    
    // Lambda 3: Conditional action
    int press_count = 0;
    events.registerButtonHandler([&press_count]() {
        press_count++;
        if (press_count == 3) {
            cout << "  → Triple press detected!" << endl;
            press_count = 0;
        }
    });
    
    cout << "\n--- Simulating button presses ---" << endl;
    for (int i = 0; i < 5; i++) {
        events.simulateButtonPress();
    }
    
    return 0;
}
```

---

## Exercise 2: Algorithm with Lambdas (STL Processing)
**Context:** Filter and transform data using lambdas with STL algorithms.

**Problem:**
```cpp
// Implement:
// 1. Filter even numbers using lambda
// 2. Transform values using lambda  
// 3. Count items matching condition
// 4. Find element with lambda predicate
```

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    cout << "=== Lambda with STL Algorithms ===" << endl;
    
    vector<int> numbers = {10, 23, 45, 12, 67, 34, 89, 56};
    
    cout << "\n--- Original data ---" << endl;
    cout << "Numbers: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Filter: Find all even numbers
    cout << "\n--- Filter even numbers ---" << endl;
    vector<int> evens;
    copy_if(numbers.begin(), numbers.end(),
            back_inserter(evens),
            [](int x) { return x % 2 == 0; });
    
    cout << "Even numbers: ";
    for (int n : evens) cout << n << " ";
    cout << endl;
    
    // Transform: Square all numbers
    cout << "\n--- Square all numbers ---" << endl;
    vector<int> squared;
    transform(numbers.begin(), numbers.end(),
              back_inserter(squared),
              [](int x) { return x * x; });
    
    cout << "Squared: ";
    for (int n : squared) cout << n << " ";
    cout << endl;
    
    // Count: Numbers greater than 40
    cout << "\n--- Count numbers > 40 ---" << endl;
    int count = count_if(numbers.begin(), numbers.end(),
                         [](int x) { return x > 40; });
    cout << "Count: " << count << endl;
    
    // Find: First number divisible by 5
    cout << "\n--- Find first divisible by 5 ---" << endl;
    auto it = find_if(numbers.begin(), numbers.end(),
                      [](int x) { return x % 5 == 0; });
    
    if (it != numbers.end()) {
        cout << "Found: " << *it << endl;
    }
    
    // Sort with custom comparator
    cout << "\n--- Sort in descending order ---" << endl;
    vector<int> sorted_nums = numbers;
    sort(sorted_nums.begin(), sorted_nums.end(),
         [](int a, int b) { return a > b; });
    
    cout << "Sorted descending: ";
    for (int n : sorted_nums) cout << n << " ";
    cout << endl;
    
    return 0;
}
```

---

## Exercise 3: Captured Variables and Closures (Advanced)
**Context:** Use captured state in repeated lambda calls.

**Problem:**
```cpp
// Demonstrate:
// 1. Capture by value [=]
// 2. Capture by reference [&]
// 3. Selective capture [x, &y]
// 4. Mutable lambda
```

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int main() {
    cout << "=== Lambda Captures ===" << endl;
    
    int x = 10;
    int y = 20;
    
    cout << "\n--- Capture by value [=] ---" << endl;
    auto byValue = [=]() {
        cout << "Inside lambda: x=" << x << ", y=" << y << endl;
    };
    
    byValue();  // Shows original values
    x = 100;
    byValue();  // Still shows original values
    cout << "After change: x=" << x << " (lambda not affected)" << endl;
    
    cout << "\n--- Capture by reference [&] ---" << endl;
    int counter = 0;
    auto byRef = [&]() {
        counter++;
        cout << "Counter: " << counter << endl;
    };
    
    byRef();  // 1
    byRef();  // 2
    byRef();  // 3
    cout << "Final counter: " << counter << endl;
    
    cout << "\n--- Selective capture [x, &y] ---" << endl;
    int temp_x = 5;
    int temp_y = 50;
    
    auto selective = [temp_x, &temp_y]() {
        // temp_x is copy, temp_y is reference
        cout << "temp_x (copy): " << temp_x 
             << ", temp_y (ref): " << temp_y << endl;
    };
    
    selective();
    temp_y = 500;
    selective();  // Shows updated temp_y
    
    cout << "\n--- Mutable lambda ---" << endl;
    int value = 0;
    auto increment = [value]() mutable {
        value++;  // Modifies captured copy
        cout << "Value inside: " << value << endl;
    };
    
    increment();  // 1
    increment();  // 2
    cout << "Value outside: " << value << endl;  // Still 0 (copy not affected)
    
    cout << "\n✓ Different capture strategies demonstrated" << endl;
    
    return 0;
}
```
