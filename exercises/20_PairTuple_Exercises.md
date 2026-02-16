# Pair and Tuple - Practical Exercises

## Exercise 1: Pair for Key-Value Data (Basic Association)
**Context:** Store related data pairs without creating full structures.

**Problem:**
```cpp
// Use pairs for:
// 1. Return multiple values
// 2. Store name-value pairs
// 3. Implement simple cache
// 4. Store min-max ranges
// 5. Coordinate pairs
```

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<string, int> ConfigPair;
typedef pair<float, float> Coordinates;

pair<bool, string> validateUser(const string &username) {
    if (username.length() < 3) {
        return make_pair(false, "Username too short");
    }
    return make_pair(true, "Username valid");
}

pair<int, int> findMinMax(const vector<int> &values) {
    auto result = minmax_element(values.begin(), values.end());
    return make_pair(*result.first, *result.second);
}

int main() {
    cout << "=== Pair: Key-Value Association ===" << endl;
    
    cout << "\n--- Return multiple values ---" << endl;
    auto [valid, msg] = validateUser("ab");
    cout << "Validation: " << (valid ? "✓ " : "✗ ") << msg << endl;
    
    auto [valid2, msg2] = validateUser("john");
    cout << "Validation: " << (valid2 ? "✓ " : "✗ ") << msg2 << endl;
    
    cout << "\n--- Configuration pairs ---" << endl;
    vector<ConfigPair> config;
    config.push_back(make_pair("port", 8080));
    config.push_back({"timeout", 30});
    config.push_back({"max_conn", 100});
    
    cout << "Configuration:" << endl;
    for (const auto &pair : config) {
        cout << "  " << pair.first << " = " << pair.second << endl;
    }
    
    cout << "\n--- Coordinate pairs ---" << endl;
    vector<Coordinates> points = {
        {0.0f, 0.0f},
        {1.0f, 2.0f},
        {3.0f, 4.0f}
    };
    
    cout << "Points:" << endl;
    for (const auto &p : points) {
        cout << "  (" << p.first << ", " << p.second << ")" << endl;
    }
    
    cout << "\n--- Min-Max range ---" << endl;
    vector<int> temps = {22, 25, 19, 27, 23};
    auto [min_temp, max_temp] = findMinMax(temps);
    cout << "Temperature range: " << min_temp << "°C to " << max_temp << "°C" << endl;
    
    cout << "\n✓ Pair operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Tuple for Multiple Values (Advanced Association)
**Context:** Function returning multiple heterogeneous values.

**Problem:**
```cpp
// Use tuple for:
// 1. Return multiple different types
// 2. Structured bindings
// 3. Store database records
// 4. Parse CSV/config lines
// 5. Temporary grouping
```

**Solution:**
```cpp
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
using namespace std;

typedef tuple<string, int, float> StudentRecord;  // name, id, gpa

StudentRecord parseStudentData(const string &line) {
    // Simulated parsing: "John,123,3.85"
    return make_tuple("John", 123, 3.85f);
}

tuple<bool, string, int> processCommand(const string &cmd) {
    if (cmd == "start") {
        return make_tuple(true, "Process started", 1);
    } else if (cmd == "stop") {
        return make_tuple(true, "Process stopped", 0);
    } else {
        return make_tuple(false, "Unknown command", -1);
    }
}

int main() {
    cout << "=== Tuple: Multiple Values Association ===" << endl;
    
    cout << "\n--- Student records ---" << endl;
    StudentRecord student1 = {"Alice", 101, 3.9f};
    StudentRecord student2 = {"Bob", 102, 3.5f};
    StudentRecord student3 = {"Charlie", 103, 3.7f};
    
    cout << "Student 1: " << get<0>(student1) 
         << " (ID: " << get<1>(student1) 
         << ", GPA: " << get<2>(student1) << ")" << endl;
    
    cout << "\n--- Structured bindings ---" << endl;
    auto [name, id, gpa] = student2;
    cout << "Student 2: " << name << " (ID: " << id << ", GPA: " << gpa << ")" << endl;
    
    cout << "\n--- Processing commands ---" << endl;
    auto [success, message, status] = processCommand("start");
    cout << "Command start: " << (success ? "✓" : "✗") << " " << message << endl;
    
    auto [success2, msg2, stat2] = processCommand("stop");
    cout << "Command stop: " << (success2 ? "✓" : "✗") << " " << msg2 << endl;
    
    auto [success3, msg3, stat3] = processCommand("invalid");
    cout << "Command invalid: " << (success3 ? "✓" : "✗") << " " << msg3 << endl;
    
    cout << "\n--- Vector of tuples ---" << endl;
    vector<StudentRecord> students = {student1, student2, student3};
    
    cout << "All students:" << endl;
    for (const auto &rec : students) {
        auto [n, i, g] = rec;
        cout << "  " << n << " (ID: " << i << ", GPA: " << g << ")" << endl;
    }
    
    cout << "\n--- Tuple concatenation (make_tuple) ---" << endl;
    auto location = make_tuple("Lab 101", 25);  // building, capacity
    auto combined = tuple_cat(student1, location);
    
    cout << "Combined data types: name, id, gpa, building, capacity" << endl;
    cout << "Tuple size: " << tuple_size<decltype(combined)>::value << endl;
    
    cout << "\n✓ Tuple operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Database Records with Tuples (Data Persistence)
**Context:** Store and query database-like records.

**Problem:**
```cpp
// Create record system:
// 1. Define record structure with tuple
// 2. Store multiple records
// 3. Filter/search records
// 4. Display formatted
// 5. Sort by field
```

**Solution:**
```cpp
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

typedef tuple<int, string, string, float> LogRecord;  // timestamp, level, message, duration

class RecordDatabase {
private:
    vector<LogRecord> records;
    
public:
    void addRecord(int ts, const string &level, const string &msg, float duration) {
        records.push_back(make_tuple(ts, level, msg, duration));
    }
    
    void filterByLevel(const string &level) {
        cout << "Records with level: " << level << endl;
        cout << "Timestamp | Level  | Message           | Duration" << endl;
        cout << "----------|--------|-------------------|----------" << endl;
        
        for (const auto &rec : records) {
            if (get<1>(rec) == level) {
                cout << setw(9) << get<0>(rec) << " | "
                     << setw(6) << get<1>(rec) << " | "
                     << setw(17) << get<2>(rec) << " | "
                     << fixed << setprecision(2) << get<3>(rec) << "s" << endl;
            }
        }
    }
    
    void displayAll() {
        cout << "\nAll Records:" << endl;
        cout << "Timestamp | Level  | Message           | Duration" << endl;
        cout << "----------|--------|-------------------|----------" << endl;
        
        for (const auto &rec : records) {
            cout << setw(9) << get<0>(rec) << " | "
                 << setw(6) << get<1>(rec) << " | "
                 << setw(17) << get<2>(rec) << " | "
                 << fixed << setprecision(2) << get<3>(rec) << "s" << endl;
        }
    }
    
    void sortByDuration() {
        sort(records.begin(), records.end(),
             [](const LogRecord &a, const LogRecord &b) {
                 return get<3>(a) > get<3>(b);
             });
        cout << "✓ Sorted by duration (longest first)" << endl;
    }
};

int main() {
    cout << "=== Tuple: Database Records ===" << endl;
    
    RecordDatabase db;
    
    cout << "\n--- Adding records ---" << endl;
    db.addRecord(1000, "INFO", "Started", 0.1f);
    db.addRecord(1010, "ERROR", "Connection failed", 2.5f);
    db.addRecord(1020, "INFO", "Retry attempt", 0.2f);
    db.addRecord(1030, "ERROR", "Timeout", 5.0f);
    db.addRecord(1040, "INFO", "Connected", 0.15f);
    
    db.displayAll();
    
    cout << "\n--- Filtering by level ---" << endl;
    db.filterByLevel("ERROR");
    
    cout << "\n--- Sorting by duration ---" << endl;
    db.sortByDuration();
    db.displayAll();
    
    cout << "\n✓ Database record operations complete" << endl;
    
    return 0;
}
```
