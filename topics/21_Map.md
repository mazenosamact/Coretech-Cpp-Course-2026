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

## Unordered Map (Hash-Based)

### Basic Unordered Map Usage
```cpp
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    // Create empty unordered_map
    unordered_map<string, int> ages;
    
    // Insert elements (order doesn't matter)
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 35;
    
    // Access elements - O(1) average case
    cout << "Alice's age: " << ages["Alice"] << endl;
    
    // Iterate (order is unpredictable, unlike map)
    cout << "All ages: " << endl;
    for (const auto &[name, age] : ages) {
        cout << name << ": " << age << endl;  // Order is hash-based, not sorted
    }
    
    cout << "\nSize: " << ages.size() << endl;
    cout << "Load factor: " << ages.load_factor() << endl;
    
    return 0;
}
```

### Unordered Map vs Map Performance
```cpp
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <chrono>
using namespace std;

int main() {
    const int N = 100000;
    
    // Test std::map
    auto start = chrono::high_resolution_clock::now();
    map<int, string> m;
    for (int i = 0; i < N; ++i) {
        m[i] = "value_" + to_string(i);
    }
    for (int i = 0; i < N; ++i) {
        auto val = m.find(i);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "map insert + find: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << " ms" << endl;
    
    // Test std::unordered_map
    start = chrono::high_resolution_clock::now();
    unordered_map<int, string> um;
    for (int i = 0; i < N; ++i) {
        um[i] = "value_" + to_string(i);
    }
    for (int i = 0; i < N; ++i) {
        auto val = um.find(i);
    }
    end = chrono::high_resolution_clock::now();
    cout << "unordered_map insert + find: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << " ms" << endl;
    
    // Typically unordered_map is faster for lookup
    
    return 0;
}
```

### Unordered Map Methods
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, int> inventory;
    
    // Insert
    inventory.insert({"apple", 10});
    inventory.emplace("banana", 5);
    
    // Count (0 or 1)
    cout << "Apple exists: " << inventory.count("apple") << endl;
    
    // Find
    auto it = inventory.find("banana");
    if (it != inventory.end()) {
        cout << "Found banana: " << it->second << endl;
    }
    
    // Erase
    inventory.erase("apple");
    
    // Hash table info
    cout << "Bucket count: " << inventory.bucket_count() << endl;
    cout << "Load factor: " << inventory.load_factor() << endl;
    cout << "Max load factor: " << inventory.max_load_factor() << endl;
    
    // Rehash
    inventory.rehash(50);  // Set minimum bucket count
    
    return 0;
}
```

### Custom Hash Function for Strings (Case-Insensitive Key)
```cpp
#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
using namespace std;

// Custom hash function for case-insensitive strings
struct CaseInsensitiveHash {
    size_t operator()(const string &s) const {
        size_t hash = 0;
        for (char c : s) {
            hash ^= std::hash<char>{}(tolower(c)) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

// Custom equality for case-insensitive strings
struct CaseInsensitiveEqual {
    bool operator()(const string &a, const string &b) const {
        if (a.size() != b.size()) return false;
        return equal(a.begin(), a.end(), b.begin(), 
                    [](char x, char y) { return tolower(x) == tolower(y); });
    }
};

int main() {
    // Case-insensitive unordered_map
    unordered_map<string, int, CaseInsensitiveHash, CaseInsensitiveEqual> scores;
    
    scores["Alice"] = 95;
    scores["BOB"] = 87;
    
    // Keys are treated case-insensitively
    cout << "alice: " << scores["ALICE"] << endl;  // Finds "Alice"
    cout << "bob: " << scores["bob"] << endl;       // Finds "BOB"
    
    for (const auto &[name, score] : scores) {
        cout << name << ": " << score << endl;
    }
    
    return 0;
}
```

### Custom Key Type with Hash Function
```cpp
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

struct Employee {
    int id;
    string name;
    
    Employee(int id = 0, const string &name = "") : id(id), name(name) {}
    
    bool operator==(const Employee &other) const {
        return id == other.id && name == other.name;
    }
};

// Custom hash function for Employee
namespace std {
    template <>
    struct hash<Employee> {
        size_t operator()(const Employee &emp) const {
            size_t h1 = hash<int>{}(emp.id);
            size_t h2 = hash<string>{}(emp.name);
            // Combine hashes
            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
        }
    };
}

int main() {
    unordered_map<Employee, double> salaries;
    
    Employee e1(1, "Alice");
    Employee e2(2, "Bob");
    Employee e3(3, "Charlie");
    
    salaries[e1] = 50000.0;
    salaries[e2] = 60000.0;
    salaries[e3] = 55000.0;
    
    cout << "Salaries:\n";
    for (const auto &[emp, salary] : salaries) {
        cout << emp.id << ". " << emp.name << ": $" << salary << endl;
    }
    
    // Lookup
    cout << "\nLookup Alice: " << salaries[e1] << endl;
    
    return 0;
}
```

### Product Inventory with Unordered Map
```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct Product {
    int id;
    string name;
    
    Product(int id = 0, const string &name = "") : id(id), name(name) {}
    
    bool operator==(const Product &other) const {
        return id == other.id;
    }
};

namespace std {
    template <>
    struct hash<Product> {
        size_t operator()(const Product &p) const {
            return hash<int>{}(p.id);
        }
    };
}

int main() {
    unordered_map<Product, int> inventory;
    
    Product laptop(1, "Laptop");
    Product mouse(2, "Mouse");
    Product keyboard(3, "Keyboard");
    
    inventory[laptop] = 5;
    inventory[mouse] = 50;
    inventory[keyboard] = 30;
    
    cout << "Current Inventory:\n";
    for (const auto &[product, quantity] : inventory) {
        cout << product.name << " (ID: " << product.id << "): " 
             << quantity << " units\n";
    }
    
    // Stock check
    cout << "\nNumber of different products: " << inventory.size() << endl;
    
    // Update stock
    inventory[laptop] -= 2;
    cout << "\nAfter selling 2 laptops: " << inventory[laptop] << " remaining\n";
    
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

### Unordered Map Methods Summary
| Method | Purpose |
|--------|---------|
| `insert()` | Add element |
| `emplace()` | Insert in-place |
| `erase()` | Remove element |
| `clear()` | Remove all |
| `find()` | Locate element |
| `count()` | Count occurrences |
| `at()` | Access with bounds check |
| `size()` | Number of elements |
| `empty()` | Check if empty |
| `bucket_count()` | Number of buckets |
| `load_factor()` | Current load factor |
| `max_load_factor()` | Max acceptable load |
| `reserve()` | Reserve capacity |
| `rehash()` | Set bucket count |

## Performance Characteristics

### map (Red-Black Tree)
| Operation | Complexity |
|-----------|------------|
| Insert | O(log n) |
| Delete | O(log n) |
| Search | O(log n) |
| Iteration | O(n) |
| Space | O(n) |

### unordered_map (Hash Table)
| Operation | Average | Worst Case |
|-----------|---------|------------|
| Insert | O(1) | O(n) |
| Delete | O(1) | O(n) |
| Search | O(1) | O(n) |
| Iteration | O(n) | O(n) |
| Space | O(n) | O(n) |

## Use Cases
- Storing key-value associations
- Frequency counting
- Dictionary/lookup tables
- Sorted data sets
- Avoiding duplicates

### Use Cases by Container

**Use map when:**
- You need sorted data
- You need reverse iteration
- You need range queries (lower_bound, upper_bound)
- Order of iteration matters
- You need custom comparators

**Use unordered_map when:**
- You need fast average-case lookup (O(1))
- Order doesn't matter
- You have large datasets with frequent access
- You need custom hash functions
- Memory overhead of balanced tree is concern

**Use multimap when:**
- You need multiple values per key
- You need to maintain order
- You need range queries with duplicates

## Comparison: map vs multimap vs unordered_map
| Feature | map | multimap | unordered_map |
|---------|-----|----------|---------------|
| Unique keys | Yes | No | Yes |
| Duplicates | No | Yes | No |
| [] operator | Yes | No | Yes |
| Ordered | Yes | Yes | No |
| Reverse iteration | Yes | Yes | No |
| Search | O(log n) | O(log n) | O(1) avg |
| Insert | O(log n) | O(log n) | O(1) avg |
| Delete | O(log n) | O(log n) | O(1) avg |
| Space efficiency | Medium | Medium | Higher |
| Cache friendly | Yes | Yes | Moderate |
| Comparator | Yes | Yes | No |
| Hash function | No | No | Yes |

## Best Practices
1. Use `find()` instead of `count()` for existence checking
2. Check bounds with `find()` before dereferencing
3. Use `upper_bound()` and `lower_bound()` for range operations in map
4. Understand key ordering requirements
5. Consider `unordered_map` for O(1) average lookup
6. For custom key types in unordered_map, provide both hash function and equality operator
7. Use hash functions that distribute keys uniformly
8. Monitor load_factor() for unordered_map performance
9. Use `reserve()` to pre-allocate capacity
10. Remember unordered_map has no order guarantee (iteration order is undefined)
