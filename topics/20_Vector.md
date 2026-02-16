# Vector Container

## Summary
`std::vector` is a dynamic array container that automatically manages memory and allows efficient random access. It can grow and shrink dynamically, making it one of the most commonly used STL containers.

## Key Concepts
- **Dynamic Resizing**: Grows as needed
- **Random Access**: O(1) access by index
- **Contiguous Memory**: Elements stored contiguously
- **Efficient Insertion/Deletion**: Slow at beginning/middle, fast at end
- **Iterator Support**: Full iterator support

## Code Examples

### Basic Vector Operations
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Create empty vector
    vector<int> v1;
    
    // Create with initial size
    vector<int> v2(5, 0);  // 5 elements, all 0
    
    // Create with initializer list
    vector<int> v3 = {10, 20, 30, 40, 50};
    
    // Add elements
    v1.push_back(100);
    v1.push_back(200);
    
    cout << "v1 size: " << v1.size() << endl;
    cout << "v3 size: " << v3.size() << endl;
    
    return 0;
}
```

### Accessing Elements
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {10, 20, 30, 40, 50};
    
    // Using [] operator
    cout << "v[0]: " << v[0] << endl;
    cout << "v[4]: " << v[4] << endl;
    
    // Using .at() with bounds checking
    cout << "v.at(2): " << v.at(2) << endl;
    
    // First and last elements
    cout << "First: " << v.front() << endl;
    cout << "Last: " << v.back() << endl;
    
    // Modify elements
    v[0] = 100;
    v.at(1) = 200;
    
    return 0;
}
```

### Iterating Through Vector
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {10, 20, 30, 40, 50};
    
    // Range-based for
    cout << "Range-based: ";
    for (int val : v) {
        cout << val << " ";
    }
    cout << endl;
    
    // Index-based for
    cout << "Index-based: ";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    
    // Iterator-based for
    cout << "Iterator: ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Adding and Removing Elements
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {10, 20, 30};
    
    // Add to end
    v.push_back(40);
    v.push_back(50);
    
    // Remove from end
    v.pop_back();
    
    // Insert at position
    v.insert(v.begin() + 1, 15);  // Insert 15 at index 1
    
    // Erase elements
    v.erase(v.begin() + 2);       // Remove element at index 2
    
    // Clear all
    // v.clear();  // Uncomment to clear
    
    cout << "Size: " << v.size() << endl;
    cout << "Elements: ";
    for (int val : v) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Capacity and Memory Management
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    
    cout << "Initial capacity: " << v.capacity() << endl;
    
    // Add elements
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
        cout << "Added " << i << ", capacity: " << v.capacity() 
             << ", size: " << v.size() << endl;
    }
    
    // Reserve space
    vector<int> v2;
    v2.reserve(100);
    cout << "\nAfter reserve(100): " << v2.capacity() << endl;
    
    // Shrink to fit
    v.push_back(10);
    cout << "\nBefore shrink_to_fit: " << v.capacity() << endl;
    v.shrink_to_fit();
    cout << "After shrink_to_fit: " << v.capacity() << endl;
    
    return 0;
}
```

### Vector of Objects
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Person {
public:
    string name;
    int age;
    
    Person(string n, int a) : name(n), age(a) {}
    
    void display() const {
        cout << name << " (" << age << ")" << endl;
    }
};

int main() {
    vector<Person> people;
    
    people.push_back(Person("Alice", 25));
    people.push_back(Person("Bob", 30));
    people.push_back(Person("Charlie", 35));
    
    for (const auto &person : people) {
        person.display();
    }
    
    return 0;
}
```

### 2D Vector
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Create 3x4 matrix
    vector<vector<int>> matrix(3, vector<int>(4, 0));
    
    // Fill matrix
    int value = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = value++;
        }
    }
    
    // Display matrix
    for (const auto &row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

### Vector Operations
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {4, 5, 6};
    
    // Concatenate (insert v2 into v1)
    v1.insert(v1.end(), v2.begin(), v2.end());
    
    cout << "After concatenation: ";
    for (int val : v1) {
        cout << val << " ";
    }
    cout << endl;
    
    // Sort
    sort(v1.begin(), v1.end());
    cout << "After sorting: ";
    for (int val : v1) {
        cout << val << " ";
    }
    cout << endl;
    
    // Reverse
    reverse(v1.begin(), v1.end());
    cout << "After reversing: ";
    for (int val : v1) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Vector Copy and Move
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v1 = {10, 20, 30};
    
    // Copy
    vector<int> v2 = v1;
    
    // Modify v2 doesn't affect v1
    v2[0] = 100;
    cout << "v1[0]: " << v1[0] << endl;  // 10
    cout << "v2[0]: " << v2[0] << endl;  // 100
    
    // Move (transfers ownership)
    vector<int> v3 = move(v1);
    cout << "After move, v1.size(): " << v1.size() << endl;  // 0
    cout << "After move, v3.size(): " << v3.size() << endl;  // 3
    
    return 0;
}
```

### Range and Comparison
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {1, 2, 3, 4, 5};
    vector<int> v3 = {1, 2, 4, 4, 5};
    
    // Comparison
    if (v1 == v2) {
        cout << "v1 == v2" << endl;
    }
    
    if (v1 != v3) {
        cout << "v1 != v3" << endl;
    }
    
    // Find element
    auto it = find(v1.begin(), v1.end(), 3);
    if (it != v1.end()) {
        cout << "Found 3 at position: " << (it - v1.begin()) << endl;
    }
    
    return 0;
}
```

## Vector Methods Summary
| Method | Purpose |
|--------|---------|
| `push_back()` | Add element at end |
| `pop_back()` | Remove from end |
| `insert()` | Insert at position |
| `erase()` | Remove element(s) |
| `clear()` | Remove all |
| `size()` | Get number of elements |
| `empty()` | Check if empty |
| `capacity()` | Get allocated capacity |
| `reserve()` | Pre-allocate capacity |
| `shrink_to_fit()` | Reduce capacity |

## Performance Characteristics
| Operation | Complexity |
|-----------|------------|
| Access | O(1) |
| Insert at end | O(1) amortized |
| Insert middle | O(n) |
| Remove from end | O(1) |
| Remove middle | O(n) |
| Search | O(n) |

## Use Cases
- Most common dynamic array needs
- When you need random access
- When growth is unpredictable
- When insertion at end is primary operation

## When NOT to Use
- When frequent insertions/deletions in middle
- When memory layout must be fixed
