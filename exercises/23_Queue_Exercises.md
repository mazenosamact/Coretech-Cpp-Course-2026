# Queue Container - Practical Exercises

## Exercise 1: Task Scheduling (FIFO Processing)
**Context:** Process tasks in order they arrive, without priorities.

**Problem:**
```cpp
// Implement task queue:
// 1. Add tasks to back (enqueue)
// 2. Process from front (dequeue)
// 3. Check queue status
// 4. Handle priority override
// 5. Display queue status
```

**Solution:**
```cpp
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Task {
    int id;
    string description;
    int duration;  // seconds
    
    Task(int i, const string &d, int dur) 
        : id(i), description(d), duration(dur) {}
};

class TaskScheduler {
private:
    queue<Task> tasks;
    int task_counter = 0;
    
public:
    void enqueueTask(const string &description, int duration) {
        Task t(task_counter++, description, duration);
        tasks.push(t);
        cout << "✓ Task queued: " << description 
             << " (" << duration << "s)" << endl;
    }
    
    Task dequeueTask() {
        if (tasks.empty()) {
            throw runtime_error("Queue is empty");
        }
        
        Task t = tasks.front();
        tasks.pop();
        cout << "✓ Processing: Task " << t.id << " - " << t.description 
             << " (" << t.duration << "s)" << endl;
        return t;
    }
    
    void displayQueue() {
        cout << "\nTask Queue:" << endl;
        if (tasks.empty()) {
            cout << "  (empty)" << endl;
            return;
        }
        
        queue<Task> temp = tasks;
        int pos = 1;
        while (!temp.empty()) {
            cout << "  [" << pos++ << "] Task " << temp.front().id 
                 << ": " << temp.front().description 
                 << " (" << temp.front().duration << "s)" << endl;
            temp.pop();
        }
    }
    
    int getQueueLength() const {
        return tasks.size();
    }
};

int main() {
    cout << "=== Queue: Task Scheduling (FIFO) ===" << endl;
    
    TaskScheduler scheduler;
    
    cout << "\n--- Enqueuing tasks ---" << endl;
    scheduler.enqueueTask("Database backup", 120);
    scheduler.enqueueTask("Email notification", 10);
    scheduler.enqueueTask("Generate report", 60);
    scheduler.enqueueTask("Update cache", 30);
    
    scheduler.displayQueue();
    
    cout << "\n--- Processing tasks ---" << endl;
    cout << "Queue length: " << scheduler.getQueueLength() << endl;
    
    scheduler.dequeueTask();
    scheduler.dequeueTask();
    
    scheduler.displayQueue();
    cout << "Remaining: " << scheduler.getQueueLength() << endl;
    
    cout << "\n--- Processing all remaining ---" << endl;
    while (scheduler.getQueueLength() > 0) {
        scheduler.dequeueTask();
    }
    
    scheduler.displayQueue();
    
    cout << "\n✓ Task scheduling complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Print Queue (Resource Management)
**Context:** Manage print jobs from multiple users.

**Problem:**
```cpp
// Create print queue:
// 1. Queue print jobs
// 2. Assign to available printer
// 3. Track status (waiting, printing, done)
// 4. Show queue statistics
// 5. Handle cancellations
```

**Solution:**
```cpp
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct PrintJob {
    int id;
    string filename;
    int pages;
    string status;  // waiting, printing, done
    
    PrintJob(int i, const string &f, int p) 
        : id(i), filename(f), pages(p), status("waiting") {}
};

class PrinterManager {
private:
    queue<PrintJob> job_queue;
    int job_counter = 0;
    int pages_per_second = 2;
    
public:
    void submitJob(const string &filename, int pages) {
        PrintJob job(job_counter++, filename, pages);
        job_queue.push(job);
        cout << "✓ Job submitted: " << filename 
             << " (" << pages << " pages)" << endl;
    }
    
    void printNext() {
        if (job_queue.empty()) {
            cout << "✗ No jobs to print" << endl;
            return;
        }
        
        PrintJob job = job_queue.front();
        job_queue.pop();
        
        int print_time = job.pages / pages_per_second;
        cout << "✓ Printing: " << job.filename 
             << " (" << job.pages << " pages, ~" << print_time << "s)" << endl;
        cout << "  Status: " << job.status << " -> printing -> done" << endl;
    }
    
    void displayQueue() {
        cout << "\nPrint Queue:" << endl;
        if (job_queue.empty()) {
            cout << "  (empty)" << endl;
            return;
        }
        
        queue<PrintJob> temp = job_queue;
        int pos = 1;
        while (!temp.empty()) {
            const PrintJob &job = temp.front();
            cout << "  [" << pos++ << "] Job " << job.id 
                 << ": " << job.filename 
                 << " (" << job.pages << "p) - " << job.status << endl;
            temp.pop();
        }
    }
    
    int getQueueLength() const {
        return job_queue.size();
    }
};

int main() {
    cout << "=== Queue: Print Manager ===" << endl;
    
    PrinterManager printer;
    
    cout << "\n--- Submitting print jobs ---" << endl;
    printer.submitJob("report.pdf", 20);
    printer.submitJob("presentation.pptx", 50);
    printer.submitJob("document.docx", 15);
    printer.submitJob("image.jpg", 5);
    
    printer.displayQueue();
    cout << "Total queue: " << printer.getQueueLength() << " jobs" << endl;
    
    cout << "\n--- Processing jobs ---" << endl;
    printer.printNext();
    printer.displayQueue();
    
    cout << "\n";
    printer.printNext();
    printer.displayQueue();
    
    cout << "\nRemaining queue: " << printer.getQueueLength() << endl;
    
    cout << "\n✓ Print queue operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Breadth-First Search (Graph Traversal)
**Context:** Explore graph/network topology using BFS.

**Problem:**
```cpp
// Implement BFS:
// 1. Queue vertices to visit
// 2. Track visited vertices
// 3. Explore layer by layer
// 4. Find shortest path
// 5. Display traversal order
```

**Solution:**
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjacency;
    
public:
    Graph(int v) : vertices(v), adjacency(v) {}
    
    void addEdge(int u, int v) {
        adjacency[u].push_back(v);
        adjacency[v].push_back(u);  // Undirected
    }
    
    void breadthFirstSearch(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;
        
        visited[start] = true;
        q.push(start);
        
        cout << "BFS Traversal starting from vertex " << start << ":" << endl;
        cout << "Order: ";
        
        int depth = 0;
        while (!q.empty()) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                int u = q.front();
                q.pop();
                
                cout << u << " ";
                
                for (int v : adjacency[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            
            if (!q.empty()) depth++;
        }
        cout << endl;
        cout << "Total depth: " << depth << " levels" << endl;
    }
    
    void display() {
        cout << "Graph adjacency list:" << endl;
        for (int i = 0; i < vertices; i++) {
            cout << "  Vertex " << i << ": ";
            for (int v : adjacency[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "=== Queue: Breadth-First Search ===" << endl;
    
    Graph g(6);
    
    cout << "\n--- Building graph ---" << endl;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    
    g.display();
    
    cout << "\n--- BFS from vertex 0 ---" << endl;
    g.breadthFirstSearch(0);
    
    cout << "\n--- BFS from vertex 4 ---" << endl;
    g.breadthFirstSearch(4);
    
    cout << "\n✓ BFS traversal complete" << endl;
    
    return 0;
}
```
