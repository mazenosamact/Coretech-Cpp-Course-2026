# Map Container

## Summary
`std::map` is an ordered associative container that stores key-value pairs sorted by key. It provides logarithmic search, insertion, and deletion, making it ideal for maintaining sorted data.

## Key Concepts
- **Key-Value Pairs**: Each element has unique key and associated value
- **Ordered**: Automatically sorts by key
- **Logarithmic Operations**: O(log n) for search/insert/delete
- **Red-Black Tree**: Underlying data structure
- **Unique Keys**: Duplicate keys not allowed

## Code Examples

### Basic Map Usage
```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    // Create empty map
    map<string, int> ages;
    
    // Insert elements
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 35;
    
    // Access elements
    cout << "Alice's age: " << ages["Alice"] << endl;
    
    // Iterate
    cout << "All ages: ";
    for (const auto &pair : ages) {
        cout << pair.first << ":" << pair.second << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Insertion Methods
```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> scores;
    
    // Method 1: Using [] operator
    scores["Player1"] = 100;
    
    // Method 2: Using insert() with pair
    scores.insert({"Player2", 150});
    scores.insert(make_pair("Player3", 120));
    
    // Method 3: Using emplace()
    scores.emplace("Player4", 130);
    
    for (const auto &[name, score] : scores) {
        cout << name << ": " << score << endl;
    }
    
    return 0;
}
```

### Accessing Elements
```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    map<string, int> inventory;
    inventory["apple"] = 10;
    inventory["banana"] = 5;
    inventory["orange"] = 8;
    
    // Using [] - creates if doesn't exist
    cout << "Apples: " << inventory["apple"] << endl;
    
    // Using .at() - throws exception if not found
    try {
        cout << "Grapes: " << inventory.at("grape") << endl;
    } catch (const out_of_range &e) {
        cout << "Grapes not found" << endl;
    }
    
    // Using .find()
    auto it = inventory.find("banana");
    if (it != inventory.end()) {
        cout << "Found banana: " << it->second << endl;
    }
    
    return 0;
}
```

### Iteration
```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> months;
    months[1] = "January";
    months[2] = "February";
    months[3] = "March";
    
    // Range-based for
    cout << "Months (forward): ";
    for (const auto &pair : months) {
        cout << pair.second << " ";
    }
    cout << endl;
    
    // Reverse iteration
    cout << "Months (reverse): ";
    for (auto it = months.rbegin(); it != months.rend(); ++it) {
        cout << it->second << " ";
    }
    cout << endl;
    
    // Iterator-based
    cout << "With iterators: ";
    for (auto it = months.begin(); it != months.end(); ++it) {
        cout << it->first << ":" << it->second << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Searching and Counting
```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> scores;
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;
    
    // Count occurrences (0 or 1 for map)
    cout << "Alice exists: " << scores.count("Alice") << endl;
    cout << "Dave exists: " << scores.count("Dave") << endl;
    
    // Find with bounds
    auto lower = scores.lower_bound("Bob");
    auto upper = scores.upper_bound("Bob");
    
    cout << "lower_bound(Bob): " << lower->first << endl;
    cout << "upper_bound(Bob): " << upper->first << endl;
    
    return 0;
}
```

### Updating and Removing
```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> scores;
    scores["Alice"] = 50;
    scores["Bob"] = 60;
    scores["Charlie"] = 70;
    
    // Update
    scores["Alice"] = 95;
    cout << "Alice new score: " << scores["Alice"] << endl;
    
    // Erase by key
    scores.erase("Bob");
    
    // Erase by iterator
    auto it = scores.find("Charlie");
    if (it != scores.end()) {
        scores.erase(it);
    }
    
    // Clear all
    // scores.clear();
    
    cout << "Size after deletions: " << scores.size() << endl;
    
    return 0;
}
```

### Multimap (Duplicate Keys)
```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    // multimap allows duplicate keys
    multimap<string, int> grades;
    grades.insert({"Math", 95});
    grades.insert({"Math", 92});
    grades.insert({"English", 88});
    grades.insert({"English", 90});
    
    // Find all entries
    cout << "Math grades: " << endl;
    auto range = grades.equal_range("Math");
    for (auto it = range.first; it != range.second; ++it) {
        cout << "  " << it->second << endl;
    }
    
    return 0;
}
```

### Custom Comparator
```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    // Map with descending order
    map<int, string, greater<int>> descending;
    descending[3] = "Third";
    descending[1] = "First";
    descending[2] = "Second";
    
    cout << "Descending order: " << endl;
    for (const auto &[key, val] : descending) {
        cout << key << ": " << val << endl;
    }
    
    return 0;
}
```

### Complex Key Types
```cpp
#include <iostream>
#include <map>
using namespace std;

struct Person {
    string name;
    int age;
    
    bool operator<(const Person &other) const {
        return name < other.name;
    }
};

int main() {
    map<Person, int> salaries;
    
    Person p1{"Alice", 25};
    Person p2{"Bob", 30};
    
    salaries[p1] = 50000;
    salaries[p2] = 60000;
    
    cout << "Salaries: " << endl;
    for (const auto &[person, salary] : salaries) {
        cout << person.name << ": $" << salary << endl;
    }
    
    return 0;
}
```

### Map with Vector Values
```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    // Map of students to their grades
    map<string, vector<int>> studentGrades;
    
    studentGrades["Alice"] = {95, 89, 92};
    studentGrades["Bob"] = {87, 91, 88};
    studentGrades["Charlie"] = {90, 85, 93};
    
    for (const auto &[name, grades] : studentGrades) {
        cout << name << ": ";
        for (int grade : grades) {
            cout << grade << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

### Frequency Counter
```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    map<char, int> frequency;
    string text = "hello world";
    
    for (char c : text) {
        frequency[c]++;
    }
    
    cout << "Character frequency: " << endl;
    for (const auto &[ch, count] : frequency) {
        if (ch == ' ') {
            cout << "(space): " << count << endl;
        } else {
            cout << ch << ": " << count << endl;
        }
    }
    
    return 0;
}
```

## Map Methods Summary
| Method | Purpose |
|--------|---------|
| `insert()` | Add element |
| `emplace()` | Insert in-place |
| `erase()` | Remove element |
| `clear()` | Remove all |
| `find()` | Locate element |
| `count()` | Count occurrences |
| `lower_bound()` | Find first >= |
| `upper_bound()` | Find first > |
| `equal_range()` | Find range |
| `size()` | Number of elements |
| `empty()` | Check if empty |

## Performance Characteristics
| Operation | Complexity |
|-----------|------------|
| Insert | O(log n) |
| Delete | O(log n) |
| Search | O(log n) |
| Iteration | O(n) |

## Use Cases
- Storing key-value associations
- Frequency counting
- Dictionary/lookup tables
- Sorted data sets
- Avoiding duplicates

## Comparison: map vs multimap
| Feature | map | multimap |
|---------|-----|----------|
| Unique keys | Yes | No |
| Duplicates | No | Yes |
| [] operator | Yes | No |
| Performance | O(log n) | O(log n) |

## Best Practices
1. Use `find()` instead of `count()`
2. Check bounds with `find()`
3. Use `upper_bound()` for ranges
4. Understand key ordering
5. Consider `unordered_map` for O(1) access
