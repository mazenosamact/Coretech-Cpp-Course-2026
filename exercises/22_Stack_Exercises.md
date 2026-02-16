# Stack Container - Practical Exercises

## Exercise 1: Expression Evaluation (Postfix Notation)
**Context:** Parse and evaluate mathematical expressions in postfix notation.

**Problem:**
```cpp
// Implement postfix calculator:
// 1. Use stack for operands
// 2. Evaluate postfix expressions
// 3. Handle multiple operators
// 4. Error handling
// 5. Display stack state
```

**Solution:**
```cpp
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

class PostfixCalculator {
private:
    stack<float> s;
    
    float performOperation(float a, float b, const string &op) {
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") {
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        }
        if (op == "^") return pow(a, b);
        throw runtime_error("Unknown operator: " + op);
    }
    
    bool isOperator(const string &token) {
        return token == "+" || token == "-" || token == "*" || 
               token == "/" || token == "^";
    }
    
public:
    float evaluate(const string &expression) {
        clear();
        
        stringstream ss(expression);
        string token;
        
        cout << "Evaluating: " << expression << endl;
        
        while (ss >> token) {
            if (isOperator(token)) {
                if (s.size() < 2) {
                    throw runtime_error("Invalid expression");
                }
                
                float b = s.top(); s.pop();
                float a = s.top(); s.pop();
                
                float result = performOperation(a, b, token);
                cout << "  " << a << " " << token << " " << b << " = " << result << endl;
                s.push(result);
            } else {
                try {
                    float num = stof(token);
                    s.push(num);
                    cout << "  Push: " << num << endl;
                } catch (...) {
                    throw runtime_error("Invalid token: " + token);
                }
            }
        }
        
        if (s.size() != 1) {
            throw runtime_error("Invalid expression");
        }
        
        return s.top();
    }
    
    void clear() {
        while (!s.empty()) s.pop();
    }
};

int main() {
    cout << "=== Stack: Postfix Expression Evaluation ===" << endl;
    
    PostfixCalculator calc;
    
    cout << "\n--- Simple expressions ---" << endl;
    try {
        float result = calc.evaluate("3 4 +");
        cout << "Result: " << result << endl;
        
        result = calc.evaluate("10 5 -");
        cout << "Result: " << result << endl;
        
        result = calc.evaluate("2 3 *");
        cout << "Result: " << result << endl;
    }
    catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    
    cout << "\n--- Complex expression ---" << endl;
    try {
        float result = calc.evaluate("15 7 1 1 + - / 3 * 2 1 1 + + -");
        cout << "Result: " << result << endl;
    }
    catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    
    cout << "\n✓ Expression evaluation complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Backtracking (Maze Solver)
**Context:** Use stack for depth-first search in maze solving.

**Problem:**
```cpp
// Implement maze solver:
// 1. Use stack for path tracking
// 2. Explore possible moves
// 3. Backtrack on dead ends
// 4. Find solution path
// 5. Display path
```

**Solution:**
```cpp
#include <iostream>
#include <stack>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int, int> Position;

class MazeSolver {
private:
    vector<string> maze;
    stack<Position> path;
    
public:
    MazeSolver(vector<string> m) : maze(m) {}
    
    bool solve(Position start, Position end) {
        int rows = maze.size();
        int cols = maze[0].size();
        
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        
        if (dfs(start, end, visited)) {
            cout << "✓ Path found!" << endl;
            displayPath();
            return true;
        } else {
            cout << "✗ No path found" << endl;
            return false;
        }
    }
    
    bool dfs(Position pos, Position end, vector<vector<bool>> &visited) {
        int x = pos.first, y = pos.second;
        
        // Check bounds and walls
        if (x < 0 || x >= (int)maze.size() || 
            y < 0 || y >= (int)maze[0].size() || 
            maze[x][y] == '#' || visited[x][y]) {
            return false;
        }
        
        visited[x][y] = true;
        path.push(pos);
        
        // Reached end
        if (pos == end) {
            return true;
        }
        
        // Try all 4 directions
        Position dirs[] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        for (auto dir : dirs) {
            if (dfs({x + dir.first, y + dir.second}, end, visited)) {
                return true;
            }
        }
        
        path.pop();
        return false;
    }
    
    void displayMaze() {
        cout << "Maze:" << endl;
        for (const auto &row : maze) {
            cout << row << endl;
        }
    }
    
    void displayPath() {
        cout << "\nPath (bottom to top): ";
        while (!path.empty()) {
            auto pos = path.top();
            path.pop();
            cout << "(" << pos.first << "," << pos.second << ") ";
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Stack: Maze Solving (Backtracking) ===" << endl;
    
    vector<string> maze = {
        "S.##.",
        "#.#.#",
        "#...#",
        "###.E"
    };
    
    MazeSolver solver(maze);
    
    cout << "\n--- Maze ---" << endl;
    solver.displayMaze();
    
    cout << "\n--- Solving ---" << endl;
    solver.solve({0, 0}, {3, 4});
    
    cout << "\n✓ Maze solving complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Function Call Stack (Browser History)
**Context:** Navigate browser history with back/forward buttons.

**Problem:**
```cpp
// Implement browser history:
// 1. Use stack for back history
// 2. Use stack for forward history
// 3. Visit page (clear forward, add to back)
// 4. Back button (pop back, push current to forward)
// 5. Forward button (pop forward, push current to back)
```

**Solution:**
```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class BrowserHistory {
private:
    stack<string> back_stack;
    stack<string> forward_stack;
    string current_page;
    
public:
    BrowserHistory() : current_page("HomePage") {
        cout << "✓ Browser initialized at HomePage" << endl;
    }
    
    void visit(const string &url) {
        cout << "\nVisiting: " << url << endl;
        
        if (!current_page.empty()) {
            back_stack.push(current_page);
        }
        
        // Clear forward history when visiting new page
        while (!forward_stack.empty()) {
            forward_stack.pop();
        }
        
        current_page = url;
        cout << "✓ Now at: " << current_page << endl;
    }
    
    void back() {
        if (back_stack.empty()) {
            cout << "✗ No back history" << endl;
            return;
        }
        
        cout << "\nGoing back..." << endl;
        forward_stack.push(current_page);
        current_page = back_stack.top();
        back_stack.pop();
        cout << "✓ Now at: " << current_page << endl;
    }
    
    void forward() {
        if (forward_stack.empty()) {
            cout << "✗ No forward history" << endl;
            return;
        }
        
        cout << "\nGoing forward..." << endl;
        back_stack.push(current_page);
        current_page = forward_stack.top();
        forward_stack.pop();
        cout << "✓ Now at: " << current_page << endl;
    }
    
    void displayHistory() {
        cout << "\n--- Browser State ---" << endl;
        cout << "Back history: ";
        
        stack<string> temp = back_stack;
        if (temp.empty()) {
            cout << "(empty)";
        } else {
            while (!temp.empty()) {
                cout << temp.top() << " > ";
                temp.pop();
            }
        }
        cout << endl;
        
        cout << "Current: " << current_page << endl;
        
        cout << "Forward history: ";
        temp = forward_stack;
        if (temp.empty()) {
            cout << "(empty)";
        } else {
            while (!temp.empty()) {
                cout << temp.top() << " > ";
                temp.pop();
            }
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Stack: Browser History Navigation ===" << endl;
    
    BrowserHistory browser;
    
    cout << "\n--- Visiting pages ---" << endl;
    browser.visit("google.com");
    browser.visit("youtube.com");
    browser.visit("github.com");
    browser.visit("cppreference.com");
    
    browser.displayHistory();
    
    cout << "\n--- Going back ---" << endl;
    browser.back();
    browser.back();
    
    browser.displayHistory();
    
    cout << "\n--- Going forward ---" << endl;
    browser.forward();
    
    browser.displayHistory();
    
    cout << "\n--- Visiting new page (forward history cleared) ---" << endl;
    browser.visit("stackoverflow.com");
    
    browser.displayHistory();
    
    cout << "\n✓ Browser history complete" << endl;
    
    return 0;
}
```
