# Set Container - Practical Exercises

## Exercise 1: Unique Values Management (Deduplication)
**Context:** Track unique system events or user IDs.

**Problem:**
```cpp
// Create deduplication system:
// 1. Store unique IDs/values automatically
// 2. Check membership
// 3. Add and remove elements
// 4. Set operations (union, intersection, difference)
// 5. Generate reports
```

**Solution:**
```cpp
#include <iostream>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

class UniqueEventTracker {
private:
    set<int> event_ids;
    
public:
    void recordEvent(int event_id) {
        if (event_ids.insert(event_id).second) {
            cout << "✓ New event recorded: " << event_id << endl;
        } else {
            cout << "  (Event " << event_id << " already recorded)" << endl;
        }
    }
    
    bool hasOccurred(int event_id) const {
        return event_ids.find(event_id) != event_ids.end();
    }
    
    int getUniqueCount() const {
        return event_ids.size();
    }
    
    void displayAll() {
        cout << "Recorded events: ";
        for (int id : event_ids) {
            cout << id << " ";
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Set: Unique Values Management ===" << endl;
    
    UniqueEventTracker tracker;
    
    cout << "\n--- Recording events ---" << endl;
    int events[] = {101, 102, 101, 103, 102, 104, 105};
    for (int e : events) {
        tracker.recordEvent(e);
    }
    
    cout << "\n--- Event statistics ---" << endl;
    tracker.displayAll();
    cout << "Total unique events: " << tracker.getUniqueCount() << endl;
    
    cout << "\n--- Checking specific events ---" << endl;
    cout << "Event 103 occurred: " << (tracker.hasOccurred(103) ? "Yes" : "No") << endl;
    cout << "Event 999 occurred: " << (tracker.hasOccurred(999) ? "Yes" : "No") << endl;
    
    cout << "\n✓ Unique tracking complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Set Operations (Finding Common Elements)
**Context:** Analyze common data between datasets.

**Problem:**
```cpp
// Implement set operations:
// 1. Intersection (common elements)
// 2. Union (all elements)
// 3. Difference (A - B)
// 4. Symmetric difference
// 5. Superset/subset tests
```

**Solution:**
```cpp
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    cout << "=== Set: Set Operations ===" << endl;
    
    set<int> serverA = {1, 2, 3, 4, 5};
    set<int> serverB = {3, 4, 5, 6, 7};
    
    cout << "\nServer A ports: ";
    for (int p : serverA) cout << p << " ";
    cout << endl;
    
    cout << "Server B ports: ";
    for (int p : serverB) cout << p << " ";
    cout << endl;
    
    cout << "\n--- Intersection (common ports) ---" << endl;
    vector<int> common;
    set_intersection(serverA.begin(), serverA.end(),
                     serverB.begin(), serverB.end(),
                     back_inserter(common));
    cout << "Common: ";
    for (int p : common) cout << p << " ";
    cout << endl;
    
    cout << "\n--- Union (all ports) ---" << endl;
    vector<int> all;
    set_union(serverA.begin(), serverA.end(),
              serverB.begin(), serverB.end(),
              back_inserter(all));
    cout << "All: ";
    for (int p : all) cout << p << " ";
    cout << endl;
    
    cout << "\n--- Difference (A - B) ---" << endl;
    vector<int> unique_to_a;
    set_difference(serverA.begin(), serverA.end(),
                   serverB.begin(), serverB.end(),
                   back_inserter(unique_to_a));
    cout << "Only in A: ";
    for (int p : unique_to_a) cout << p << " ";
    cout << endl;
    
    cout << "\n--- Symmetric difference ---" << endl;
    vector<int> sym_diff;
    set_symmetric_difference(serverA.begin(), serverA.end(),
                            serverB.begin(), serverB.end(),
                            back_inserter(sym_diff));
    cout << "In either but not both: ";
    for (int p : sym_diff) cout << p << " ";
    cout << endl;
    
    cout << "\n✓ Set operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: IP Whitelist Management (Access Control)
**Context:** Maintain sorted unique IP addresses for security policies.

**Problem:**
```cpp
// Create IP whitelist system:
// 1. Store unique approved IPs in sorted order
// 2. Add/remove IPs
// 3. Check if IP is whitelisted
// 4. Display sorted list
// 5. Export/import operations
```

**Solution:**
```cpp
#include <iostream>
#include <set>
#include <string>
#include <sstream>
using namespace std;

class IPWhitelist {
private:
    set<string> ips;
    
    bool isValidIP(const string &ip) {
        // Simple validation: check format
        int dots = 0;
        for (char c : ip) {
            if (c == '.') dots++;
        }
        return dots == 3;
    }
    
public:
    void addIP(const string &ip) {
        if (!isValidIP(ip)) {
            cout << "✗ Invalid IP: " << ip << endl;
            return;
        }
        
        if (ips.insert(ip).second) {
            cout << "✓ IP added: " << ip << endl;
        } else {
            cout << "  (IP " << ip << " already whitelisted)" << endl;
        }
    }
    
    void removeIP(const string &ip) {
        if (ips.erase(ip)) {
            cout << "✓ IP removed: " << ip << endl;
        } else {
            cout << "✗ IP not found: " << ip << endl;
        }
    }
    
    bool isAllowed(const string &ip) const {
        return ips.find(ip) != ips.end();
    }
    
    void displayAll() {
        cout << "\nWhitelisted IPs (sorted):" << endl;
        int count = 0;
        for (const string &ip : ips) {
            cout << "  [" << ++count << "] " << ip << endl;
        }
        cout << "Total: " << ips.size() << endl;
    }
};

int main() {
    cout << "=== Set: IP Whitelist Management ===" << endl;
    
    IPWhitelist policy;
    
    cout << "\n--- Adding IPs ---" << endl;
    policy.addIP("192.168.1.100");
    policy.addIP("10.0.0.5");
    policy.addIP("192.168.1.100");  // Duplicate
    policy.addIP("172.16.0.1");
    policy.addIP("192.168.1.50");
    policy.addIP("invalid");  // Invalid
    
    policy.displayAll();
    
    cout << "\n--- Security checks ---" << endl;
    cout << "Is 192.168.1.100 allowed? " 
         << (policy.isAllowed("192.168.1.100") ? "✓ Yes" : "✗ No") << endl;
    cout << "Is 192.168.1.99 allowed? " 
         << (policy.isAllowed("192.168.1.99") ? "✓ Yes" : "✗ No") << endl;
    cout << "Is 10.0.0.5 allowed? " 
         << (policy.isAllowed("10.0.0.5") ? "✓ Yes" : "✗ No") << endl;
    
    cout << "\n--- Removing IP ---" << endl;
    policy.removeIP("172.16.0.1");
    
    policy.displayAll();
    
    cout << "\n✓ Whitelist management complete" << endl;
    
    return 0;
}
```
