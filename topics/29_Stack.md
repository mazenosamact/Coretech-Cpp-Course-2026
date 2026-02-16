# Stack Container (LIFO)

## Summary
`std::stack` is an adapter container implementing Last-In-First-Out (LIFO) semantics. It restricts access to only the top element, making it ideal for problems requiring stack-like behavior like expression evaluation and backtracking.

## Key Concepts
- **LIFO**: Last element added is first removed
- **Adapter Container**: Built on top of another container
- **Limited Interface**: Only push, pop, top operations
- **O(1) Operations**: All main operations are constant time
- **No Iterators**: Cannot iterate through stack

## Code Examples

### Basic Stack Operations
```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> s;
    
    // Push elements
    s.push(10);
    s.push(20);
    s.push(30);
    
    cout << "Stack size: " << s.size() << endl;
    
    // Check if empty
    if (!s.empty()) {
        cout << "Top element: " << s.top() << endl;
    }
    
    // Pop elements
    while (!s.empty()) {
        cout << "Popping: " << s.top() << endl;
        s.pop();
    }
    
    return 0;
}
```

### Parenthesis Matching
```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(const string &expr) {
    stack<char> s;
    
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (s.empty()) return false;
            
            char top = s.top();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
            s.pop();
        }
    }
    
    return s.empty();
}

int main() {
    string expr1 = "({[()]})";
    string expr2 = "({[}])";
    
    cout << expr1 << " is "
         << (isBalanced(expr1) ? "balanced" : "not balanced") << endl;
    cout << expr2 << " is "
         << (isBalanced(expr2) ? "balanced" : "not balanced") << endl;
    
    return 0;
}
```

### Stack-based Expression Evaluation
```cpp
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

// Postfix expression: 5 3 +
// Result: 5 + 3 = 8
double evaluatePostfix(const string &expr) {
    stack<double> s;
    stringstream ss(expr);
    string token;
    
    while (ss >> token) {
        if (token == "+" || token == "-" || 
            token == "*" || token == "/") {
            
            double b = s.top(); s.pop();
            double a = s.top(); s.pop();
            
            if (token == "+") s.push(a + b);
            else if (token == "-") s.push(a - b);
            else if (token == "*") s.push(a * b);
            else if (token == "/") s.push(a / b);
        } else {
            s.push(stod(token));
        }
    }
    
    return s.top();
}

int main() {
    cout << "3 4 +" << " = " << evaluatePostfix("3 4 +") << endl;
    cout << "10 5 -" << " = " << evaluatePostfix("10 5 -") << endl;
    cout << "5 3 *" << " = " << evaluatePostfix("5 3 *") << endl;
    cout << "20 4 /" << " = " << evaluatePostfix("20 4 /") << endl;
    
    return 0;
}
```

### Function Call Stack Simulation
```cpp
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

struct FunctionCall {
    string name;
    int lineNumber;
    
    FunctionCall(string n, int line) : name(n), lineNumber(line) {}
};

int main() {
    stack<FunctionCall> callStack;
    
    // Simulate function calls
    callStack.push(FunctionCall("main", 5));
    callStack.push(FunctionCall("process", 12));
    callStack.push(FunctionCall("calculate", 18));
    
    cout << "Call stack (top to bottom):" << endl;
    while (!callStack.empty()) {
        const FunctionCall &fc = callStack.top();
        cout << "  " << fc.name << " (line " << fc.lineNumber << ")" << endl;
        callStack.pop();
    }
    
    return 0;
}
```

### Undo/Redo System
```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Editor {
private:
    string content;
    stack<string> undoStack;
    stack<string> redoStack;
    
public:
    void type(const string &text) {
        undoStack.push(content);
        content += text;
        while (!redoStack.empty()) redoStack.pop();
    }
    
    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(content);
            content = undoStack.top();
            undoStack.pop();
        }
    }
    
    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(content);
            content = redoStack.top();
            redoStack.pop();
        }
    }
    
    string getContent() const {
        return content;
    }
};

int main() {
    Editor editor;
    
    editor.type("Hello");
    cout << "After typing: " << editor.getContent() << endl;
    
    editor.type(" World");
    cout << "After typing: " << editor.getContent() << endl;
    
    editor.undo();
    cout << "After undo: " << editor.getContent() << endl;
    
    editor.undo();
    cout << "After undo: " << editor.getContent() << endl;
    
    editor.redo();
    cout << "After redo: " << editor.getContent() << endl;
    
    return 0;
}
```

### Depth-First Search (DFS) with Stack
```cpp
#include <iostream>
#include <stack>
#include <vector>
#include <set>
using namespace std;

void dfs(int node, const vector<vector<int>> &adj) {
    stack<int> s;
    set<int> visited;
    
    s.push(node);
    visited.insert(node);
    
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        
        cout << current << " ";
        
        for (int neighbor : adj[current]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                s.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    vector<vector<int>> adj = {
        {1, 2},
        {0, 3},
        {0, 3},
        {1, 2}
    };
    
    cout << "DFS from node 0: ";
    dfs(0, adj);
    
    return 0;
}
```

### Stack of Strings
```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> s;
    
    s.push("first");
    s.push("second");
    s.push("third");
    
    cout << "Stack of strings:" << endl;
    while (!s.empty()) {
        cout << "  " << s.top() << endl;
        s.pop();
    }
    
    return 0;
}
```

### Stack with Custom Type
```cpp
#include <iostream>
#include <stack>
using namespace std;

struct Person {
    string name;
    int age;
    
    Person(string n, int a) : name(n), age(a) {}
};

int main() {
    stack<Person> s;
    
    s.push(Person("Alice", 30));
    s.push(Person("Bob", 25));
    s.push(Person("Charlie", 35));
    
    cout << "Stack of persons:" << endl;
    while (!s.empty()) {
        Person p = s.top();
        cout << "  " << p.name << " (" << p.age << ")" << endl;
        s.pop();
    }
    
    return 0;
}
```

### Reverse Polish Notation (RPN)
```cpp
#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

double rpn(const vector<string> &tokens) {
    stack<double> s;
    
    for (const string &token : tokens) {
        if (token == "+" || token == "-" || 
            token == "*" || token == "/"  || token == "^") {
            
            double b = s.top(); s.pop();
            double a = s.top(); s.pop();
            
            if (token == "+") s.push(a + b);
            else if (token == "-") s.push(a - b);
            else if (token == "*") s.push(a * b);
            else if (token == "/") s.push(a / b);
            else if (token == "^") s.push(pow(a, b));
        } else {
            s.push(stod(token));
        }
    }
    
    return s.top();
}

int main() {
    vector<string> tokens1 = {"2", "1", "+", "3", "*"};  // (2+1)*3 = 9
    cout << "Result: " << rpn(tokens1) << endl;
    
    vector<string> tokens2 = {"15", "7", "1", "1", "-", "/", "+", "3", "*", "2", "1", "1", "+", "-", "/"};
    cout << "Complex RPN: " << rpn(tokens2) << endl;
    
    return 0;
}
```

### Stack Underlying Container
```cpp
#include <iostream>
#include <stack>
#include <vector>
#include <deque>
using namespace std;

int main() {
    // Default: deque
    stack<int> s1;
    
    // Using vector
    stack<int, vector<int>> s2;
    
    // Using deque explicitly
    stack<int, deque<int>> s3;
    
    s1.push(1); s1.push(2);
    s2.push(10); s2.push(20);
    s3.push(100); s3.push(200);
    
    cout << "s1 top: " << s1.top() << endl;
    cout << "s2 top: " << s2.top() << endl;
    cout << "s3 top: " << s3.top() << endl;
    
    return 0;
}
```

## Interface
```cpp
push(val)      // Add element
pop()          // Remove top
top()          // Access top
empty()        // Check if empty
size()         // Number of elements
```

## Stack vs vector Stack Usage
```cpp
// Vector as stack
vector<int> v;
v.push_back(1);
v.push_back(2);
int top = v.back();
v.pop_back();

// Proper stack
stack<int> s;
s.push(1);
s.push(2);
int top = s.top();
s.pop();
```

## Common Use Cases
1. Expression evaluation (postfix/prefix)
2. Parenthesis matching
3. Function call tracking
4. Undo/Redo mechanisms
5. Depth-First Search (DFS)
6. Browser back button
7. Balanced bracket checking

## Performance
- All operations: O(1)
- Space: O(n)
- Default container: deque (good balance)

## Best Practices
1. Use stack for LIFO problems
2. Don't access middle elements
3. Use stack not vector for clarity
4. Consider default container (deque)
5. Handle empty() before top()
