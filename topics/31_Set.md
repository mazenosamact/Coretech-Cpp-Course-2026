# Set Container (Sorted Unique Elements)

## Summary
`std::set` is an ordered container that maintains unique elements in sorted order. It's implemented as a balanced binary search tree (Red-Black Tree) providing O(log n) insertion, deletion, and searching. `std::unordered_set` provides O(1) average operations without ordering.

## Key Concepts
- **Ordered**: Elements sorted by comparison function
- **Unique**: No duplicates allowed
- **O(log n) Operations**: Insertion, deletion, search
- **Bidirectional Iterators**: Can iterate forward and backward
- **Self-Balancing Tree**: Maintains balance automatically
- **unordered_set**: Hash table, O(1) average, no order

## Code Examples

### Basic set Operations
```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s;
    
    // Insert elements
    s.insert(30);
    s.insert(10);
    s.insert(20);
    s.insert(10);  // Duplicate, ignored
    
    cout << "Set size: " << s.size() << endl;
    cout << "Elements (sorted): ";
    for (int x : s) cout << x << " ";
    cout << endl;
    
    // Find element
    if (s.find(20) != s.end()) {
        cout << "20 found" << endl;
    }
    
    // Erase element
    s.erase(20);
    
    cout << "After erasing 20: ";
    for (int x : s) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Finding and Iterating
```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s = {5, 2, 8, 1, 9, 3};
    
    // Forward iteration
    cout << "Forward: ";
    for (int x : s) cout << x << " ";
    cout << endl;
    
    // Reverse iteration
    cout << "Reverse: ";
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Find specific element
    auto it = s.find(8);
    if (it != s.end()) {
        cout << "Found 8 at position" << endl;
    }
    
    // Lower and upper bounds
    auto lower = s.lower_bound(3);
    auto upper = s.upper_bound(8);
    
    cout << "Elements [3...8]: ";
    for (auto it = lower; it != upper; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Removing Duplicates
```cpp
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {5, 2, 5, 8, 2, 1, 9, 3, 5};
    
    // Convert to set (automatically removes duplicates)
    set<int> s(v.begin(), v.end());
    
    cout << "Original size: " << v.size() << endl;
    cout << "Unique elements: " << s.size() << endl;
    cout << "Unique values: ";
    for (int x : s) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Set of Strings
```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    set<string> words = {"apple", "zebra", "banana", "apple", "cherry"};
    
    cout << "Unique words (sorted): ";
    for (const string &w : words) {
        cout << w << " ";
    }
    cout << endl;
    
    // Check if word exists
    if (words.count("banana")) {
        cout << "banana is in the set" << endl;
    }
    
    return 0;
}
```

### Custom Comparator
```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    // Default: ascending
    set<int> s1 = {5, 2, 8, 1, 9};
    
    cout << "Ascending (default): ";
    for (int x : s1) cout << x << " ";
    cout << endl;
    
    // Descending
    set<int, greater<int>> s2 = {5, 2, 8, 1, 9};
    
    cout << "Descending: ";
    for (int x : s2) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Custom Objects in set
```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;

struct Student {
    string name;
    int id;
    
    Student(string n, int i) : name(n), id(i) {}
    
    // Comparison operator for sorting
    bool operator<(const Student &other) const {
        return id < other.id;
    }
};

int main() {
    set<Student> students;
    
    students.insert(Student("Alice", 103));
    students.insert(Student("Bob", 101));
    students.insert(Student("Charlie", 102));
    
    cout << "Students (sorted by ID):" << endl;
    for (const Student &s : students) {
        cout << s.id << ": " << s.name << endl;
    }
    
    return 0;
}
```

### Lower and Upper Bounds
```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s = {10, 20, 30, 40, 50};
    
    // Lower bound: first element >= value
    auto lower = s.lower_bound(25);
    cout << "Lower bound of 25: " << *lower << endl;
    
    // Upper bound: first element > value
    auto upper = s.upper_bound(25);
    cout << "Upper bound of 25: " << *upper << endl;
    
    // Range of elements in [20, 40)
    lower = s.lower_bound(20);
    upper = s.upper_bound(40);
    
    cout << "Elements in [20...40): ";
    for (auto it = lower; it != upper; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Equal Range
```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s = {1, 2, 3, 4, 5, 5, 5};  // Note: set removes duplicates
    
    auto range = s.equal_range(5);
    
    cout << "Range of 5: ";
    for (auto it = range.first; it != range.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Multiset - Allow Duplicates
```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    multiset<int> m;
    
    m.insert(5);
    m.insert(2);
    m.insert(5);  // Allowed in multiset
    m.insert(8);
    m.insert(2);
    
    cout << "Multiset (with duplicates): ";
    for (int x : m) cout << x << " ";
    cout << endl;
    
    cout << "Count of 5: " << m.count(5) << endl;
    cout << "Count of 2: " << m.count(2) << endl;
    
    // Erase all occurrences
    m.erase(2);
    
    cout << "After erasing all 2s: ";
    for (int x : m) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Unordered_set - Hash Table
```cpp
#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    unordered_set<string> words;
    
    words.insert("apple");
    words.insert("zebra");
    words.insert("banana");
    words.insert("apple");  // Duplicate ignored
    
    cout << "Unordered set (no particular order): ";
    for (const string &w : words) {
        cout << w << " ";
    }
    cout << endl;
    
    cout << "Count of 'zebra': " << words.count("zebra") << endl;
    
    // Erase
    words.erase("banana");
    
    cout << "Size after erase: " << words.size() << endl;
    
    return 0;
}
```

### Set Operations
```cpp
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    set<int> s1 = {1, 2, 3, 4, 5};
    set<int> s2 = {3, 4, 5, 6, 7};
    
    // Union
    set<int> unionSet;
    set_union(s1.begin(), s1.end(),
              s2.begin(), s2.end(),
              inserter(unionSet, unionSet.begin()));
    
    cout << "Union: ";
    for (int x : unionSet) cout << x << " ";
    cout << endl;
    
    // Intersection
    set<int> interSet;
    set_intersection(s1.begin(), s1.end(),
                     s2.begin(), s2.end(),
                     inserter(interSet, interSet.begin()));
    
    cout << "Intersection: ";
    for (int x : interSet) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Set of Pairs
```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<pair<int, string>> s;
    
    s.insert({3, "three"});
    s.insert({1, "one"});
    s.insert({2, "two"});
    
    cout << "Set of pairs:" << endl;
    for (const auto &p : s) {
        cout << p.first << ": " << p.second << endl;
    }
    
    return 0;
}
```

### Count and Membership
```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s = {1, 3, 5, 7, 9};
    
    // Check membership (returns 0 or 1 for set)
    cout << "1 in set: " << s.count(1) << endl;
    cout << "2 in set: " << s.count(2) << endl;
    
    // Using find
    if (s.find(5) != s.end()) {
        cout << "5 found" << endl;
    }
    
    return 0;
}
```

## set vs unordered_set
| Feature | set | unordered_set |
|---------|-----|---------------|
| Order | Sorted | No order |
| Time | O(log n) | O(1) avg |
| Worst case | O(log n) | O(n) |
| Space | Minimal overhead | Hash table |
| Iterator stability | Yes | No |
| Iteration order | Sorted | Random |

## Common Comparators
```cpp
set<int> asc;                    // Default ascending
set<int, greater<int>> desc;     // Descending
set<int, less<int>> asc2;        // Explicit ascending
set<string> words;               // String comparison
```

## Use Cases
| Problem | Solution |
|---------|----------|
| Remove duplicates | set |
| Sorted unique items | set |
| Fast membership test | unordered_set |
| Range queries | set with bounds |
| Frequency counting | multiset |
| Sorted pairs | set<pair> |

## Member Functions
```cpp
insert(val)        // O(log n)
erase(val)         // O(log n)
find(val)          // O(log n)
count(val)         // O(log n)
lower_bound(val)   // O(log n)
upper_bound(val)   // O(log n)
equal_range(val)   // O(log n)
clear()            // O(n)
size()             // O(1)
empty()            // O(1)
```

## Best Practices
1. Use `set` when order matters
2. Use `unordered_set` for hash table performance
3. Use `multiset` for duplicates
4. Avoid modifying elements (const)
5. Use `find()` instead of `count()` for checking
6. Use `lower_bound()/upper_bound()` for ranges
7. Consider memory with hash tables
