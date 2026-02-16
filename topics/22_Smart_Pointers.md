# Smart Pointers (unique_ptr vs shared_ptr)

## Summary
Smart pointers automatically manage memory using RAII (Resource Acquisition Is Initialization). `unique_ptr` provides exclusive ownership, while `shared_ptr` allows multiple owners. They eliminate memory leaks and are safer than raw pointers.

## Key Concepts
- **RAII**: Automatic resource cleanup via destructors
- **unique_ptr**: Single owner, exclusive ownership
- **shared_ptr**: Multiple owners, reference counting
- **Automatic Deallocation**: No manual delete needed
- **Zero Overhead**: No runtime cost vs raw pointers

## Code Examples

### unique_ptr Basics
```cpp
#include <iostream>
#include <memory>
using namespace std;

class Resource {
public:
    Resource(string name) : name(name) {
        cout << "Creating: " << name << endl;
    }
    
    ~Resource() {
        cout << "Destroying: " << name << endl;
    }
    
    void use() { cout << "Using: " << name << endl; }
    
private:
    string name;
};

int main() {
    {
        // Create unique_ptr
        unique_ptr<Resource> ptr(new Resource("Resource1"));
        ptr->use();
    }  // Automatically destroyed here
    
    // Modern syntax (C++14)
    {
        auto ptr2 = make_unique<Resource>("Resource2");
        ptr2->use();
    }  // Automatically destroyed
    
    return 0;
}
```

### unique_ptr Transfer of Ownership
```cpp
#include <iostream>
#include <memory>
using namespace std;

class Data {
public:
    Data(int val) : value(val) {}
    int getValue() { return value; }
    
private:
    int value;
};

void processData(unique_ptr<Data> data) {
    cout << "Processing: " << data->getValue() << endl;
}  // Data deleted here

int main() {
    unique_ptr<Data> ptr1 = make_unique<Data>(42);
    
    // Transfer ownership
    processData(move(ptr1));
    
    // ptr1 is now null
    if (!ptr1) {
        cout << "ptr1 is null after move" << endl;
    }
    
    return 0;
}
```

### shared_ptr Basics
```cpp
#include <iostream>
#include <memory>
using namespace std;

class Database {
public:
    Database(string name) : name(name) {
        cout << "Connecting: " << name << endl;
    }
    
    ~Database() {
        cout << "Disconnecting: " << name << endl;
    }
    
    void query(string sql) {
        cout << "Query on " << name << ": " << sql << endl;
    }
    
private:
    string name;
};

int main() {
    {
        auto db1 = make_shared<Database>("MainDB");
        {
            auto db2 = db1;  // Share ownership
            cout << "Use count: " << db1.use_count() << endl;  // 2
            db2->query("SELECT * FROM users");
        }
        cout << "Use count after db2 destroyed: " 
             << db1.use_count() << endl;  // 1
    }  // Database destroyed when last shared_ptr is destroyed
    
    return 0;
}
```

### shared_ptr Reference Counting
```cpp
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int main() {
    shared_ptr<int> ptr1 = make_shared<int>(42);
    
    cout << "Initial use count: " << ptr1.use_count() << endl;  // 1
    
    shared_ptr<int> ptr2 = ptr1;  // Share ownership
    cout << "After ptr2 = ptr1: " << ptr1.use_count() << endl;  // 2
    
    shared_ptr<int> ptr3 = ptr1;
    cout << "After ptr3 = ptr1: " << ptr1.use_count() << endl;  // 3
    
    vector<shared_ptr<int>> vec = {ptr1, ptr2, ptr3};
    cout << "In vector: " << ptr1.use_count() << endl;  // 6
    
    ptr2 = nullptr;  // Release
    cout << "After ptr2 = nullptr: " << ptr1.use_count() << endl;  // 5
    
    return 0;
}
```

### unique_ptr with Arrays
```cpp
#include <iostream>
#include <memory>
using namespace std;

int main() {
    // Dynamic array with unique_ptr
    unique_ptr<int[]> arr(new int[5]);
    
    // Initialize
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }
    
    // Access
    cout << "Array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Automatically freed when out of scope
    return 0;
}
```

### Smart Pointers in Containers
```cpp
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Node {
public:
    Node(int val) : value(val) {}
    int value;
    unique_ptr<Node> next;
};

int main() {
    vector<unique_ptr<Node>> nodes;
    
    nodes.push_back(make_unique<Node>(10));
    nodes.push_back(make_unique<Node>(20));
    nodes.push_back(make_unique<Node>(30));
    
    for (const auto &node : nodes) {
        cout << "Node value: " << node->value << endl;
    }
    
    return 0;
}
```

### Circular Reference Problem with shared_ptr
```cpp
#include <iostream>
#include <memory>
using namespace std;

class Node {
public:
    Node(int v) : value(v) {}
    int value;
    shared_ptr<Node> next;  // Can cause circular reference
    
    ~Node() { cout << "Destroying node: " << value << endl; }
};

int main() {
    {
        auto node1 = make_shared<Node>(1);
        auto node2 = make_shared<Node>(2);
        
        node1->next = node2;
        node2->next = node1;  // Circular reference!
        
        cout << "node1 use count: " << node1.use_count() << endl;  // 2
    }
    // Both nodes still not deleted due to circular reference!
    
    return 0;
}
```

### Solving Circular Reference with weak_ptr
```cpp
#include <iostream>
#include <memory>
using namespace std;

class Node {
public:
    Node(int v) : value(v) {}
    
    ~Node() { cout << "Destroying: " << value << endl; }
    
    int value;
    shared_ptr<Node> next;
    weak_ptr<Node> prev;  // Use weak_ptr to break cycle
};

int main() {
    {
        auto node1 = make_shared<Node>(1);
        auto node2 = make_shared<Node>(2);
        
        node1->next = node2;
        node2->prev = node1;  // Weak reference, no cycle
        
        cout << "node1 use count: " << node1.use_count() << endl;  // 1
    }
    // Nodes properly destroyed
    
    return 0;
}
```

### Smart Pointers Returning from Functions
```cpp
#include <iostream>
#include <memory>
using namespace std;

class Result {
public:
    Result(string msg) : message(msg) {}
    string message;
};

// Return unique_ptr - ownership transferred
unique_ptr<Result> calculateResult() {
    return make_unique<Result>("Success!");
}

// Return shared_ptr - shared ownership
shared_ptr<Result> getSharedResult() {
    return make_shared<Result>("Shared result");
}

int main() {
    auto result1 = calculateResult();
    cout << result1->message << endl;
    
    auto result2 = getSharedResult();
    cout << "Use count: " << result2.use_count() << endl;
    
    return 0;
}
```

### Custom Deleter
```cpp
#include <iostream>
#include <memory>
#include <fstream>
using namespace std;

int main() {
    // Custom deleter for FILE
    auto deleter = [](FILE *f) {
        if (f) {
            cout << "Closing file" << endl;
            fclose(f);
        }
    };
    
    unique_ptr<FILE, decltype(deleter)> file(
        fopen("test.txt", "w"), 
        deleter
    );
    
    if (file) {
        fprintf(file.get(), "Hello, file!");
    }
    // File automatically closed by custom deleter
    
    return 0;
}
```

### unique_ptr Best Practices
```cpp
#include <iostream>
#include <memory>
using namespace std;

class Logger {
public:
    Logger() : count(0) {}
    void log(string msg) { 
        cout << ++count << ": " << msg << endl; 
    }
private:
    int count;
};

int main() {
    // GOOD: Use make_unique
    auto logger = make_unique<Logger>();
    logger->log("Starting");
    
    // AVOID: Raw new with unique_ptr
    // unique_ptr<Logger> logger2(new Logger());
    
    // Function returns ownership
    auto getLogger = []() {
        return make_unique<Logger>();
    };
    
    auto logger3 = getLogger();
    logger3->log("From function");
    
    return 0;
}
```

## Smart Pointer Comparison
| Feature | unique_ptr | shared_ptr | raw pointer |
|---------|-----------|-----------|-------------|
| Ownership | Exclusive | Shared | None |
| Multiple owners | No | Yes | N/A |
| Overhead | None | Reference count | None |
| Copy | No (move only) | Yes | Direct |
| Delete trigger | Out of scope | Count = 0 | Manual |
| Array support | Yes | No | N/A |

## Key Rules
1. **Use `make_unique` and `make_shared`** for creation
2. **Pass by reference** not by shared_ptr value
3. **Use `move`** when transferring unique_ptr ownership
4. **Avoid circular references** with shared_ptr
5. **Use `weak_ptr`** for cycles or caches

## When to Choose
| Choice | When |
|--------|------|
| unique_ptr | Exclusive ownership, most cases |
| shared_ptr | Multiple owners need cleanup |
| raw pointer | Parameter passing, no ownership |
| weak_ptr | Breaking circular references |

## Common Mistakes
- Storing shared_ptr by value in parameters
- Creating circular references
- Mixing unique_ptr and shared_ptr unnecessarily
- Not using make_unique/make_shared
