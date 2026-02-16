# STL Algorithms: sort and copy

## Summary
STL algorithms provide generic, type-safe functions for manipulating containers. `sort` arranges elements in order while `copy` duplicates elements between containers, both demonstrating the power of iterators and templates.

## Key Concepts
- **Generic Algorithms**: Work with any container
- **Iterators**: Define ranges to operate on
- **Comparators**: Custom sorting logic
- **Predicates**: Functions for filtering/checking
- **Time Complexity**: O(n log n) for sort, O(n) for copy

## Code Examples

### Basic sort
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {5, 2, 8, 1, 9, 3};
    
    // Default ascending sort
    sort(v.begin(), v.end());
    
    cout << "Sorted: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    
    // Descending sort
    sort(v.begin(), v.end(), greater<int>());
    
    cout << "Descending: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Sorting with Custom Comparator
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Person {
    string name;
    int age;
};

int main() {
    vector<Person> people = {
        {"Alice", 30}, {"Bob", 25}, {"Charlie", 35}
    };
    
    // Sort by age
    sort(people.begin(), people.end(),
         [](const Person &a, const Person &b) {
             return a.age < b.age;
         });
    
    cout << "Sorted by age:" << endl;
    for (const auto &p : people) {
        cout << p.name << " (" << p.age << ")" << endl;
    }
    
    // Sort by name
    sort(people.begin(), people.end(),
         [](const Person &a, const Person &b) {
             return a.name < b.name;
         });
    
    cout << "\nSorted by name:" << endl;
    for (const auto &p : people) {
        cout << p.name << " (" << p.age << ")" << endl;
    }
    
    return 0;
}
```

### Sorting Pairs
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<pair<int, string>> v = {
        {3, "three"}, {1, "one"}, {2, "two"}
    };
    
    // Sort by first element (default)
    sort(v.begin(), v.end());
    
    cout << "Sorted by first:" << endl;
    for (const auto &[num, text] : v) {
        cout << num << ": " << text << endl;
    }
    
    // Sort by second element
    sort(v.begin(), v.end(),
         [](const pair<int, string> &a, const pair<int, string> &b) {
             return a.second < b.second;
         });
    
    cout << "\nSorted by string:" << endl;
    for (const auto &[num, text] : v) {
        cout << num << ": " << text << endl;
    }
    
    return 0;
}
```

### Partial Sorting
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // Partial sort - only first 3 elements sorted
    partial_sort(v.begin(), v.begin() + 3, v.end());
    
    cout << "Partial sort (first 3): ";
    for (int x : v) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### nth_element
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4};
    
    // Find 4th smallest element
    nth_element(v.begin(), v.begin() + 3, v.end());
    
    cout << "4th element: " << v[3] << endl;
    cout << "Elements before: ";
    for (int i = 0; i < 3; i++) cout << v[i] << " ";
    cout << endl;
    
    return 0;
}
```

### Basic copy
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> source = {1, 2, 3, 4, 5};
    vector<int> dest(5);  // Must have space
    
    // Copy to dest
    copy(source.begin(), source.end(), dest.begin());
    
    cout << "Destination: ";
    for (int x : dest) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### copy_if (Conditional Copy)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> source = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> dest;
    
    // Copy only even numbers
    copy_if(source.begin(), source.end(),
            back_inserter(dest),
            [](int x) { return x % 2 == 0; });
    
    cout << "Even numbers: ";
    for (int x : dest) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Copying with Transform
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> source = {1, 2, 3, 4, 5};
    vector<int> dest;
    
    // Copy and transform (multiply by 2)
    transform(source.begin(), source.end(),
              back_inserter(dest),
              [](int x) { return x * 2; });
    
    cout << "Doubled: ";
    for (int x : dest) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Moving vs Copying
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    vector<string> source = {"one", "two", "three"};
    vector<string> dest;
    
    // Move (more efficient for expensive types)
    move(source.begin(), source.end(), back_inserter(dest));
    
    cout << "After move:" << endl;
    cout << "Source size: " << source.size() << endl;
    cout << "Source[0] empty: " << source[0].empty() << endl;
    cout << "Dest[0]: " << dest[0] << endl;
    
    return 0;
}
```

### Combining sort with copy
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> original = {5, 2, 8, 1, 9, 3};
    vector<int> sorted_version;
    
    // Copy then sort
    copy(original.begin(), original.end(),
         back_inserter(sorted_version));
    sort(sorted_version.begin(), sorted_version.end());
    
    cout << "Original: ";
    for (int x : original) cout << x << " ";
    cout << endl;
    
    cout << "Sorted copy: ";
    for (int x : sorted_version) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Advanced: Custom Sort with Lambda
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    vector<int> v = {-5, 3, -8, 1, -2, 7};
    
    // Sort by absolute value, then by sign
    sort(v.begin(), v.end(),
         [](int a, int b) {
             int abs_a = abs(a), abs_b = abs(b);
             if (abs_a != abs_b) {
                 return abs_a < abs_b;
             }
             return a < b;
         });
    
    cout << "Sorted by absolute value: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Reverse Copy
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> source = {1, 2, 3, 4, 5};
    vector<int> reversed;
    
    // Copy in reverse
    copy(source.rbegin(), source.rend(),
         back_inserter(reversed));
    
    cout << "Reversed: ";
    for (int x : reversed) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Unique Values (sort + unique)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {1, 2, 2, 3, 3, 3, 4, 4, 5};
    
    // Sort first
    sort(v.begin(), v.end());
    
    // Remove duplicates (shifts unique elements to front)
    auto new_end = unique(v.begin(), v.end());
    v.erase(new_end, v.end());
    
    cout << "Unique values: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

## Common Sorting Comparators
```cpp
// Ascending (default)
sort(v.begin(), v.end());
sort(v.begin(), v.end(), less<int>());

// Descending
sort(v.begin(), v.end(), greater<int>());

// Custom lambda
sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
    return /* condition */ ;
});
```

## Copy Variants
| Function | Purpose |
|----------|---------|
| `copy` | Copy all elements |
| `copy_if` | Copy if predicate true |
| `copy_n` | Copy first n elements |
| `copy_backward` | Copy in reverse |
| `move` | Move elements |
| `transform` | Copy with transformation |

## Performance Tips
1. **Sort** uses introsort (quicksort + heapsort hybrid)
2. **Copy** is O(n), generally very fast
3. **move** is faster than copy for expensive types
4. **partial_sort** better than sort for small results
5. Use **back_inserter** for unknown destination size
6. **Reserve** vector capacity before inserting

## Best Practices
1. Use STL algorithms instead of manual loops
2. Pass containers by const reference
3. Use lambda for inline comparators
4. Consider move semantics for expensive types
5. Use appropriate iterator categories
6. Reserve capacity before bulk operations
