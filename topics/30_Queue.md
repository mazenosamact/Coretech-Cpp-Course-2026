# Queue Container (FIFO)

## Summary
`std::queue` is an adapter container implementing First-In-First-Out (FIFO) semantics. It provides efficient operations on both ends and is ideal for problems requiring queue-like behavior such as breadth-first search and task scheduling.

## Key Concepts
- **FIFO**: First element added is first removed
- **Adapter Container**: Built on another container
- **Limited Interface**: push, pop, front, back only
- **O(1) Operations**: All operations are constant time
- **No Random Access**: Cannot access middle elements

## Code Examples

### Basic Queue Operations
```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> q;
    
    // Enqueue (add)
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    
    cout << "Queue size: " << q.size() << endl;
    
    // Check elements
    cout << "Front: " << q.front() << endl;
    cout << "Back: " << q.back() << endl;
    
    // Dequeue (remove)
    while (!q.empty()) {
        cout << "Dequeuing: " << q.front() << endl;
        q.pop();
    }
    
    return 0;
}
```

### Breadth-First Search (BFS)
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;

void bfs(int start, const vector<vector<int>> &adj) {
    queue<int> q;
    set<int> visited;
    
    q.push(start);
    visited.insert(start);
    
    cout << "BFS traversal: ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        cout << node << " ";
        
        for (int neighbor : adj[node]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    vector<vector<int>> adj = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1},
        {2}
    };
    
    bfs(0, adj);
    
    return 0;
}
```

### Task Queue Simulation
```cpp
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Task {
    string name;
    int priority;
    
    Task(string n, int p) : name(n), priority(p) {}
};

int main() {
    queue<Task> tasks;
    
    // Add tasks
    tasks.push(Task("Database backup", 1));
    tasks.push(Task("Email notification", 2));
    tasks.push(Task("Log rotation", 3));
    
    cout << "Processing tasks in order:" << endl;
    while (!tasks.empty()) {
        Task current = tasks.front();
        cout << "Processing: " << current.name 
             << " (priority " << current.priority << ")" << endl;
        tasks.pop();
    }
    
    return 0;
}
```

### Customer Service Queue
```cpp
#include <iostream>
#include <queue>
#include <string>
using namespace std;

class CustomerQueue {
private:
    queue<string> customers;
    
public:
    void arrive(const string &name) {
        customers.push(name);
        cout << name << " arrives. Queue size: " << customers.size() << endl;
    }
    
    void serve() {
        if (!customers.empty()) {
            cout << "Serving: " << customers.front() << endl;
            customers.pop();
        } else {
            cout << "No customers waiting." << endl;
        }
    }
    
    void showQueue() {
        cout << "Queue: ";
        queue<string> temp = customers;  // Copy for viewing
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

int main() {
    CustomerQueue cq;
    
    cq.arrive("Alice");
    cq.arrive("Bob");
    cq.arrive("Charlie");
    cq.showQueue();
    
    cq.serve();
    cq.showQueue();
    
    cq.serve();
    cq.showQueue();
    
    return 0;
}
```

### Message Queue
```cpp
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Message {
    string from;
    string subject;
    string body;
    
    Message(string f, string s, string b) 
        : from(f), subject(s), body(b) {}
};

int main() {
    queue<Message> mailbox;
    
    // Receive messages
    mailbox.push(Message("alice@example.com", "Meeting", "Next Monday?"));
    mailbox.push(Message("bob@example.com", "Project", "Update attached"));
    mailbox.push(Message("charlie@example.com", "Hello", "How are you?"));
    
    cout << "Processing messages:" << endl;
    while (!mailbox.empty()) {
        Message msg = mailbox.front();
        cout << "From: " << msg.from << endl;
        cout << "Subject: " << msg.subject << endl;
        cout << "Body: " << msg.body << endl << endl;
        mailbox.pop();
    }
    
    return 0;
}
```

### Print Job Queue
```cpp
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct PrintJob {
    string filename;
    int pages;
    int priority;
    
    PrintJob(string f, int p, int pr) 
        : filename(f), pages(p), priority(pr) {}
};

int main() {
    queue<PrintJob> printQueue;
    
    printQueue.push(PrintJob("report.pdf", 10, 1));
    printQueue.push(PrintJob("photo.jpg", 5, 2));
    printQueue.push(PrintJob("document.docx", 15, 1));
    
    int totalPages = 0;
    cout << "Print queue:" << endl;
    queue<PrintJob> temp = printQueue;
    while (!temp.empty()) {
        PrintJob job = temp.front();
        cout << job.filename << " (" << job.pages << " pages)" << endl;
        totalPages += job.pages;
        temp.pop();
    }
    
    cout << "Total pages to print: " << totalPages << endl;
    
    return 0;
}
```

### Producer-Consumer Pattern
```cpp
#include <iostream>
#include <queue>
using namespace std;

class ProducerConsumer {
private:
    queue<int> buffer;
    
public:
    void produce(int item) {
        buffer.push(item);
        cout << "Produced: " << item << ", buffer size: " << buffer.size() << endl;
    }
    
    int consume() {
        if (!buffer.empty()) {
            int item = buffer.front();
            buffer.pop();
            cout << "Consumed: " << item << ", buffer size: " << buffer.size() << endl;
            return item;
        }
        return -1;
    }
    
    bool isEmpty() {
        return buffer.empty();
    }
};

int main() {
    ProducerConsumer pc;
    
    // Produce items
    for (int i = 1; i <= 5; ++i) {
        pc.produce(i * 10);
    }
    
    cout << endl;
    
    // Consume items
    while (!pc.isEmpty()) {
        pc.consume();
    }
    
    return 0;
}
```

### Level Order Traversal of Tree
```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;
    
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

void levelOrderTraversal(TreeNode *root) {
    if (!root) return;
    
    queue<TreeNode*> q;
    q.push(root);
    
    cout << "Level order: ";
    while (!q.empty()) {
        TreeNode *node = q.front();
        q.pop();
        
        cout << node->value << " ";
        
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    cout << endl;
}

int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    levelOrderTraversal(root);
    
    return 0;
}
```

### Double-ended Queue (deque)
```cpp
#include <iostream>
#include <deque>
using namespace std;

int main() {
    deque<int> dq;
    
    // Add to both ends
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.push_front(0);
    dq.push_front(-1);
    
    cout << "Deque: ";
    for (int x : dq) cout << x << " ";
    cout << endl;
    
    // Remove from both ends
    cout << "Front: " << dq.front() << ", Back: " << dq.back() << endl;
    
    dq.pop_front();
    dq.pop_back();
    
    cout << "After removal: ";
    for (int x : dq) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Priority Queue (Different from Regular Queue)
```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    // Regular queue: FIFO
    queue<int> q;
    q.push(3);
    q.push(1);
    q.push(2);
    
    cout << "Queue (FIFO): ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    
    // Priority queue: highest first
    priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(2);
    
    cout << "Priority Queue: ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
    
    return 0;
}
```

## Interface
```cpp
push(val)      // Enqueue (add to back)
pop()          // Dequeue (remove from front)
front()        // Access front element
back()         // Access back element
empty()        // Check if empty
size()         // Number of elements
```

## Queue vs stack
| Aspect | Queue | Stack |
|--------|-------|-------|
| Order | FIFO | LIFO |
| Add | Back | Top |
| Remove | Front | Top |
| Example | Printer queue | Undo stack |
| Use case | Sequential | Last-first |

## Common Use Cases
1. Breadth-First Search (BFS)
2. Level-order tree traversal
3. Task scheduling
4. Message passing
5. Customer service lines
6. Print job management
7. Packet processing

## Default Containers
- `queue<T>` uses `deque<T>` by default
- Can use `vector<T>` as underlying container
- `priority_queue<T>` uses `vector<T>` with heap

## Performance
- All operations: O(1)
- Space: O(n)

## Best Practices
1. Use queue for FIFO problems
2. Check empty() before front()/back()
3. Use queue not deque for clarity
4. Don't access middle elements
5. Consider deque for double-ended operations
