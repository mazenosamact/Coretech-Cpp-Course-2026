# List Container (Doubly Linked List)

## Summary
`std::list` is a doubly-linked list container providing efficient insertion and deletion at any position while having slower random access compared to `vector`. It's ideal when frequent insertions/deletions are needed.

## Key Concepts
- **Doubly Linked List**: Each node has forward and backward pointers
- **O(1) Insertion/Deletion**: At any position if iterator available
- **O(n) Random Access**: Must traverse from beginning or end
- **Bidirectional Iterators**: Can move forward and backward
- **No Reallocation**: Elements stored in separate memory blocks

## Code Examples

### Basic list Operations
```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l;
    
    // Add elements
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    l.push_front(0);
    
    cout << "List: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    // Remove elements
    l.pop_back();
    l.pop_front();
    
    cout << "After removal: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Insert and Erase
```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l = {1, 2, 3, 5};
    
    auto it = l.begin();
    advance(it, 3);  // Move to 4th position
    
    // Insert 4 before position
    l.insert(it, 4);
    
    cout << "After insert: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    // Erase element
    it = l.begin();
    advance(it, 2);
    l.erase(it);
    
    cout << "After erase: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Finding and Erasing Elements
```cpp
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main() {
    list<int> l = {1, 2, 3, 4, 5, 3};
    
    // Find element
    auto it = find(l.begin(), l.end(), 3);
    if (it != l.end()) {
        cout << "Found 3 at position" << endl;
        l.erase(it);
    }
    
    cout << "After erase: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    // Remove all occurrences
    l = {1, 2, 3, 4, 5, 3};
    l.remove(3);  // STL remove for lists
    
    cout << "After remove all 3: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Splice - Efficient Merge
```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l1 = {1, 2, 3};
    list<int> l2 = {4, 5, 6};
    
    // Move l2 into l1
    l1.splice(l1.end(), l2);
    
    cout << "l1 after splice: ";
    for (int x : l1) cout << x << " ";
    cout << endl;
    
    cout << "l2 after splice (now empty): " << l2.size() << endl;
    
    // Splice part of list
    list<int> l3 = {10, 20, 30};
    list<int> l4 = {11, 22, 33};
    
    auto it = l4.begin();
    advance(it, 1);
    
    l3.splice(l3.end(), l4, it);  // Move 22
    
    cout << "l3: ";
    for (int x : l3) cout << x << " ";
    cout << ", l4: ";
    for (int x : l4) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Reverse and Sort
```cpp
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main() {
    list<int> l = {5, 2, 8, 1, 9, 3};
    
    // Reverse (O(n))
    l.reverse();
    
    cout << "Reversed: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    // Sort (O(n log n))
    l.sort();
    
    cout << "Sorted: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    // Custom comparator
    l.sort(greater<int>());
    
    cout << "Sorted descending: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Unique Elements
```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    
    // Must be sorted for unique to work
    l.sort();
    
    // Remove consecutive duplicates
    l.unique();
    
    cout << "After unique: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Merge Sorted Lists
```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l1 = {1, 3, 5, 7};
    list<int> l2 = {2, 4, 6, 8};
    
    // Both must be sorted
    l1.merge(l2);
    
    cout << "Merged: ";
    for (int x : l1) cout << x << " ";
    cout << endl;
    
    cout << "l2 after merge: " << l2.size() << endl;
    
    return 0;
}
```

### Iterating and Accessing
```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<string> l = {"apple", "banana", "cherry"};
    
    // Forward iteration
    cout << "Forward: ";
    for (auto it = l.begin(); it != l.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Reverse iteration
    cout << "Reverse: ";
    for (auto it = l.rbegin(); it != l.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Front and back access
    cout << "First: " << l.front() << endl;
    cout << "Last: " << l.back() << endl;
    
    return 0;
}
```

### Bidirectional Iteration
```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l = {1, 2, 3, 4, 5};
    
    auto it = l.begin();
    
    // Move forward
    ++it;
    ++it;
    cout << "After ++it twice: " << *it << endl;
    
    // Move backward
    --it;
    cout << "After --it: " << *it << endl;
    
    return 0;
}
```

### Complexity Example: Insertion
```cpp
#include <iostream>
#include <list>
#include <vector>
#include <chrono>
using namespace std;

int main() {
    // List: Efficient insertion in middle
    list<int> l;
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 100; ++i) {
        auto it = l.begin();
        advance(it, l.size() / 2);  // Go to middle
        l.insert(it, i);
    }
    
    auto end = chrono::high_resolution_clock::now();
    cout << "List insertion time: " 
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " microseconds" << endl;
    
    // Vector: Inefficient insertion in middle
    vector<int> v;
    start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 100; ++i) {
        v.insert(v.begin() + v.size() / 2, i);
    }
    
    end = chrono::high_resolution_clock::now();
    cout << "Vector insertion time: " 
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " microseconds" << endl;
    
    return 0;
}
```

### remove_if with Predicate
```cpp
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main() {
    list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // Remove even numbers
    auto it = remove_if(l.begin(), l.end(),
                       [](int x) { return x % 2 == 0; });
    l.erase(it, l.end());
    
    cout << "After removing even: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Empty and Clear
```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l = {1, 2, 3, 4, 5};
    
    cout << "Size: " << l.size() << endl;
    cout << "Empty: " << (l.empty() ? "yes" : "no") << endl;
    
    l.clear();
    
    cout << "After clear:" << endl;
    cout << "Size: " << l.size() << endl;
    cout << "Empty: " << (l.empty() ? "yes" : "no") << endl;
    
    return 0;
}
```

## list vs vector vs deque
| Operation | list | vector | deque |
|-----------|------|--------|-------|
| Random Access | O(n) | O(1) | O(1) |
| Insert/Delete front | O(1) | O(n) | O(1) |
| Insert/Delete middle | O(1)* | O(n) | O(n) |
| Insert/Delete back | O(1) | O(1) | O(1) |
| Memory |Fragmented| Contiguous | Chunked |
| Cache friendly | No | Yes | Better |

## When to Use list
- Frequent insertions/deletions in middle
- Don't need random access
- Have iterators to insertion point
- Need bidirectional movement
- Memory fragmentation acceptable

## Member Functions
```cpp
push_front(val)     // O(1)
push_back(val)      // O(1)
pop_front()         // O(1)
pop_back()          // O(1)
insert(it, val)     // O(1)
erase(it)           // O(1)
splice(it, list2)   // O(1)
sort()              // O(n log n)
reverse()           // O(n)
unique()            // O(n)
```

## Best Practices
1. Use list for frequent middle insertions
2. Prefer vector for cache locality
3. Use iterators, not indices
4. Use member functions (sort, remove) over algorithms
5. Don't assume O(1) random access
6. Consider deque as middle ground
