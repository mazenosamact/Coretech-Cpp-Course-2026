# List Container - Practical Exercises

## Exercise 1: Linked List Operations (Efficient Insertion/Deletion)
**Context:** Process queue where items are frequently added and removed from both ends.

**Problem:**
```cpp
// Implement work queue:
// 1. Add/remove from front and back
// 2. Iterate through list
// 3. Find and remove specific items
// 4. Display queue state
// 5. Process items with callbacks
```

**Solution:**
```cpp
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

struct Job {
    int id;
    string task;
    int priority;
    
    Job(int i, const string &t, int p) : id(i), task(t), priority(p) {}
};

class JobQueue {
private:
    list<Job> queue;
    int next_id = 0;
    
public:
    void addJob(const string &task, int priority) {
        queue.push_back(Job(next_id++, task, priority));
        cout << "✓ Job added: " << task << " (priority: " << priority << ")" << endl;
    }
    
    Job processNext() {
        if (queue.empty()) {
            throw runtime_error("Queue is empty");
        }
        
        Job job = queue.front();
        queue.pop_front();
        cout << "✓ Processing: Job " << job.id << " - " << job.task << endl;
        return job;
    }
    
    void cancelJob(int job_id) {
        auto it = find_if(queue.begin(), queue.end(),
                         [job_id](const Job &j) { return j.id == job_id; });
        
        if (it != queue.end()) {
            cout << "✓ Cancelled: " << it->task << endl;
            queue.erase(it);
        }
    }
    
    void displayQueue() {
        cout << "\nJob Queue:" << endl;
        if (queue.empty()) {
            cout << "  (empty)" << endl;
            return;
        }
        
        int pos = 1;
        for (const auto &job : queue) {
            cout << "  [" << pos++ << "] Job " << job.id << ": " << job.task 
                 << " (priority: " << job.priority << ")" << endl;
        }
    }
    
    int size() const {
        return queue.size();
    }
};

int main() {
    cout << "=== List: Job Queue (Efficient Insertion/Deletion) ===" << endl;
    
    JobQueue queue;
    
    cout << "\n--- Adding jobs ---" << endl;
    queue.addJob("Send email", 1);
    queue.addJob("Backup database", 3);
    queue.addJob("Update config", 2);
    queue.addJob("Clean logs", 1);
    
    queue.displayQueue();
    
    cout << "\n--- Cancelling job ---" << endl;
    queue.cancelJob(1);
    queue.displayQueue();
    
    cout << "\n--- Processing jobs ---" << endl;
    queue.processNext();
    queue.processNext();
    queue.displayQueue();
    
    cout << "\n--- Remaining: " << queue.size() << " jobs" << endl;
    
    cout << "\n✓ List operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Bidirectional Iteration (Playlist Management)
**Context:** Audio playlist with forward and backward navigation.

**Problem:**
```cpp
// Create playlist system:
// 1. Add songs
// 2. Navigate forward/backward
// 3. Insert songs at position
// 4. Remove songs
// 5. Display with current indicator
```

**Solution:**
```cpp
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

struct Song {
    string title;
    string artist;
    int duration;
    
    Song(const string &t, const string &a, int d) 
        : title(t), artist(a), duration(d) {}
};

class Playlist {
private:
    list<Song> songs;
    list<Song>::iterator current;
    
public:
    void addSong(const string &title, const string &artist, int duration) {
        songs.push_back(Song(title, artist, duration));
        if (current == songs.end()) {
            current = songs.begin();
        }
        cout << "✓ Added: " << title << " by " << artist << " (" << duration << "s)" << endl;
    }
    
    void play() {
        if (current == songs.end()) {
            cout << "No song available" << endl;
            return;
        }
        cout << "Now playing: " << current->title << " by " << current->artist << endl;
    }
    
    void nextSong() {
        if (current == songs.end()) return;
        
        auto next = next(current);
        if (next != songs.end()) {
            current = next;
            play();
        } else {
            cout << "Already at last song" << endl;
        }
    }
    
    void previousSong() {
        if (current == songs.begin()) {
            cout << "Already at first song" << endl;
            return;
        }
        
        current = prev(current);
        play();
    }
    
    void display() {
        cout << "\nPlaylist:" << endl;
        int pos = 1;
        for (auto it = songs.begin(); it != songs.end(); ++it) {
            string marker = (it == current) ? "► " : "  ";
            cout << marker << "[" << pos++ << "] " << it->title 
                 << " - " << it->artist << " (" << it->duration << "s)" << endl;
        }
    }
};

int main() {
    cout << "=== List: Bidirectional Playlist Navigation ===" << endl;
    
    Playlist playlist;
    
    cout << "\n--- Building playlist ---" << endl;
    playlist.addSong("Song A", "Artist 1", 180);
    playlist.addSong("Song B", "Artist 2", 200);
    playlist.addSong("Song C", "Artist 3", 210);
    playlist.addSong("Song D", "Artist 4", 190);
    
    playlist.display();
    
    cout << "\n--- Playing ---" << endl;
    playlist.play();
    
    cout << "\n--- Navigation ---" << endl;
    playlist.nextSong();
    playlist.nextSong();
    playlist.display();
    
    cout << "\n--- Going back ---" << endl;
    playlist.previousSong();
    playlist.display();
    
    cout << "\n✓ Playlist operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Memory-Efficient Deque Alternative (Ring Buffer)
**Context:** Store fixed-size circular buffer using list properties.

**Problem:**
```cpp
// Implement circular buffer:
// 1. Fixed maximum size
// 2. Automatically remove oldest when full
// 3. Efficient front/back operations
// 4. Display buffer state
// 5. Calculate statistics
```

**Solution:**
```cpp
#include <iostream>
#include <list>
#include <numeric>
#include <cmath>
using namespace std;

class CircularBuffer {
private:
    list<float> buffer;
    const size_t MAX_SIZE = 10;
    
public:
    void addValue(float value) {
        buffer.push_back(value);
        
        if (buffer.size() > MAX_SIZE) {
            buffer.pop_front();
        }
        
        cout << "✓ Added: " << value << " (buffer: " << buffer.size() 
             << "/" << MAX_SIZE << ")" << endl;
    }
    
    float getAverage() const {
        if (buffer.empty()) return 0.0f;
        
        float sum = accumulate(buffer.begin(), buffer.end(), 0.0f);
        return sum / buffer.size();
    }
    
    float getStdDev() const {
        if (buffer.empty()) return 0.0f;
        
        float avg = getAverage();
        float sum_sq_diff = 0.0f;
        
        for (float val : buffer) {
            float diff = val - avg;
            sum_sq_diff += diff * diff;
        }
        
        return sqrt(sum_sq_diff / buffer.size());
    }
    
    void display() {
        cout << "\nBuffer contents: ";
        for (float val : buffer) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    void printStats() {
        cout << "\nBuffer Statistics:" << endl;
        cout << "  Size: " << buffer.size() << "/" << MAX_SIZE << endl;
        cout << "  Average: " << getAverage() << endl;
        cout << "  Std Dev: " << getStdDev() << endl;
    }
};

int main() {
    cout << "=== List: Circular Buffer Implementation ===" << endl;
    
    CircularBuffer buffer;
    
    cout << "\n--- Adding values ---" << endl;
    float temperatures[] = {22.5, 23.0, 22.8, 23.5, 22.9, 
                           23.2, 22.7, 23.4, 23.1, 22.6, 
                           23.3, 22.9};
    
    for (float temp : temperatures) {
        buffer.addValue(temp);
    }
    
    buffer.display();
    buffer.printStats();
    
    cout << "\n--- Adding more values (last 2 will wrap) ---" << endl;
    buffer.addValue(23.0);
    buffer.addValue(22.8);
    
    buffer.display();
    buffer.printStats();
    
    cout << "\n✓ Circular buffer operations complete" << endl;
    
    return 0;
}
```
