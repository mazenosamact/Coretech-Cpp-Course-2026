# Vector Container - Practical Exercises

## Exercise 1: Dynamic Array Management (Embedded Buffering)
**Context:** Real-time data acquisition system needs to store measurements dynamically.

**Problem:**
```cpp
// Create a circular measurement buffer:
// 1. Store sensor readings in vector
// 2. Limit buffer to max 100 readings
// 3. Remove oldest when full (FIFO)
// 4. Calculate statistics
// 5. Clear and reset
```

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class MeasurementBuffer {
private:
    vector<float> readings;
    const int MAX_SIZE = 100;
    
public:
    void addReading(float value) {
        readings.push_back(value);
        
        // Remove oldest if full
        if (readings.size() > MAX_SIZE) {
            readings.erase(readings.begin());
        }
        
        cout << "Added: " << value << " (buffer: " << readings.size() << "/" 
             << MAX_SIZE << ")" << endl;
    }
    
    float getAverage() const {
        if (readings.empty()) return 0.0f;
        
        float sum = accumulate(readings.begin(), readings.end(), 0.0f);
        return sum / readings.size();
    }
    
    float getMin() const {
        if (readings.empty()) return 0.0f;
        return *min_element(readings.begin(), readings.end());
    }
    
    float getMax() const {
        if (readings.empty()) return 0.0f;
        return *max_element(readings.begin(), readings.end());
    }
    
    void printStats() {
        cout << "\nBuffer Statistics:" << endl;
        cout << "  Size: " << readings.size() << endl;
        cout << "  Min: " << getMin() << endl;
        cout << "  Max: " << getMax() << endl;
        cout << "  Avg: " << getAverage() << endl;
    }
    
    void clear() {
        readings.clear();
        cout << "Buffer cleared" << endl;
    }
};

int main() {
    cout << "=== Vector: Dynamic Measurement Buffer ===" << endl;
    
    MeasurementBuffer buffer;
    
    cout << "\n--- Adding readings ---" << endl;
    float temps[] = {22.5, 23.1, 22.8, 23.5, 22.9, 23.2, 22.7, 23.4};
    for (float temp : temps) {
        buffer.addReading(temp);
    }
    
    buffer.printStats();
    
    cout << "\n✓ Vector operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: 2D Matrix with Vector (Image Processing)
**Context:** Process image data stored in 2D vector.

**Problem:**
```cpp
// Create image processing:
// 1. Store 2D pixel data in vector of vectors
// 2. Apply filters (brightness, contrast)
// 3. Find regions/objects
// 4. Save/load operations
```

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Image {
private:
    vector<vector<int>> pixels;
    int width, height;
    
public:
    Image(int w, int h) : width(w), height(h) {
        pixels.assign(h, vector<int>(w, 0));
        cout << "Image created: " << w << "x" << h << endl;
    }
    
    void setPixel(int x, int y, int value) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y][x] = value;
        }
    }
    
    int getPixel(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return pixels[y][x];
        }
        return 0;
    }
    
    void applyBrightness(int factor) {
        for (auto &row : pixels) {
            for (int &pixel : row) {
                pixel = min(255, pixel + factor);
            }
        }
        cout << "Brightness applied: " << factor << endl;
    }
    
    void invert() {
        for (auto &row : pixels) {
            for (int &pixel : row) {
                pixel = 255 - pixel;
            }
        }
        cout << "Image inverted" << endl;
    }
    
    void display() {
        cout << "\nImage content:" << endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cout << pixels[y][x] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "=== Vector: 2D Image Processing ===" << endl;
    
    Image img(5, 3);
    
    cout << "\n--- Setting pixel values ---" << endl;
    img.setPixel(0, 0, 100);
    img.setPixel(2, 1, 150);
    img.setPixel(4, 2, 200);
    
    img.display();
    
    cout << "\n--- Applying filters ---" << endl;
    img.applyBrightness(50);
    img.invert();
    
    img.display();
    
    return 0;
}
```

---

## Exercise 3: Task Queue with Vector (Backend Scheduler)
**Context:** Task scheduler needs to manage job queue.

**Problem:**
```cpp
// Implement task queue:
// 1. Add tasks with priority
// 2. Remove completed tasks
// 3. Sort by priority
// 4. Display pending tasks
// 5. Execute in order
```

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Task {
    string name;
    int priority;
    bool completed;
    
    Task(const string &n, int p) : name(n), priority(p), completed(false) {}
};

class TaskQueue {
private:
    vector<Task> tasks;
    
public:
    void addTask(const string &name, int priority) {
        tasks.push_back(Task(name, priority));
        cout << "Task added: " << name << " (priority: " << priority << ")" << endl;
    }
    
    void sortByPriority() {
        sort(tasks.begin(), tasks.end(),
             [](const Task &a, const Task &b) {
                 return a.priority > b.priority;
             });
        cout << "Tasks sorted by priority" << endl;
    }
    
    void completeTask(const string &name) {
        auto it = find_if(tasks.begin(), tasks.end(),
                         [&name](const Task &t) { return t.name == name; });
        
        if (it != tasks.end()) {
            it->completed = true;
            cout << "Task completed: " << name << endl;
        }
    }
    
    void removeCompleted() {
        int before = tasks.size();
        tasks.erase(remove_if(tasks.begin(), tasks.end(),
                            [](const Task &t) { return t.completed; }),
                   tasks.end());
        cout << "Removed " << (before - tasks.size()) << " completed tasks" << endl;
    }
    
    void displayPending() {
        cout << "\nPending tasks:" << endl;
        for (size_t i = 0; i < tasks.size(); i++) {
            if (!tasks[i].completed) {
                cout << "  [" << i+1 << "] " << tasks[i].name 
                     << " (priority: " << tasks[i].priority << ")" << endl;
            }
        }
    }
};

int main() {
    cout << "=== Vector: Task Queue Management ===" << endl;
    
    TaskQueue queue;
    
    cout << "\n--- Adding tasks ---" << endl;
    queue.addTask("Email notification", 2);
    queue.addTask("Database backup", 1);
    queue.addTask("Generate report", 3);
    queue.addTask("Update config", 2);
    
    queue.displayPending();
    
    cout << "\n--- Sorting by priority ---" << endl;
    queue.sortByPriority();
    queue.displayPending();
    
    cout << "\n--- Completing tasks ---" << endl;
    queue.completeTask("Generate report");
    queue.completeTask("Database backup");
    
    cout << "\n--- Removing completed ---" << endl;
    queue.removeCompleted();
    queue.displayPending();
    
    return 0;
}
```
