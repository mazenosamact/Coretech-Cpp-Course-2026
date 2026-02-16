# Map Container - Practical Exercises

## Exercise 1: Configuration Management (Key-Value Storage)
**Context:** Embedded system needs to store and retrieve configuration parameters.

**Problem:**
```cpp
// Implement configuration system:
// 1. Store key-value pairs (parameter names and values)
// 2. Load/save configurations
// 3. Validate and update parameters
// 4. Query and iterate
// 5. Handle defaults
```

**Solution:**
```cpp
#include <iostream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

class Configuration {
private:
    map<string, string> params;
    map<string, string> defaults;
    
public:
    void setDefault(const string &key, const string &value) {
        defaults[key] = value;
        params[key] = value;  // Initialize with default
        cout << "✓ Default set: " << key << " = " << value << endl;
    }
    
    void setValue(const string &key, const string &value) {
        if (defaults.find(key) != defaults.end()) {
            params[key] = value;
            cout << "✓ Updated: " << key << " = " << value << endl;
        } else {
            cout << "✗ Unknown parameter: " << key << endl;
        }
    }
    
    string getValue(const string &key) {
        if (params.find(key) != params.end()) {
            return params[key];
        }
        return "";
    }
    
    bool getValueAsInt(const string &key, int &out) {
        if (params.find(key) != params.end()) {
            try {
                out = stoi(params[key]);
                return true;
            } catch (...) {
                return false;
            }
        }
        return false;
    }
    
    void reloadDefaults() {
        params = defaults;
        cout << "✓ Restored to defaults" << endl;
    }
    
    void printAll() {
        cout << "\nConfiguration Parameters:" << endl;
        for (const auto &pair : params) {
            cout << "  " << pair.first << " = " << pair.second << endl;
        }
    }
};

int main() {
    cout << "=== Map: Configuration Management ===" << endl;
    
    Configuration config;
    
    cout << "\n--- Setting defaults ---" << endl;
    config.setDefault("port", "8080");
    config.setDefault("host", "localhost");
    config.setDefault("timeout", "30");
    config.setDefault("max_connections", "100");
    
    config.printAll();
    
    cout << "\n--- Updating values ---" << endl;
    config.setValue("port", "9000");
    config.setValue("timeout", "60");
    config.setValue("invalid_param", "value");  // Will fail
    
    config.printAll();
    
    cout << "\n--- Reading values ---" << endl;
    int port = 0;
    if (config.getValueAsInt("port", port)) {
        cout << "Port set to: " << port << endl;
    }
    
    cout << "Host: " << config.getValue("host") << endl;
    
    cout << "\n--- Resetting to defaults ---" << endl;
    config.reloadDefaults();
    config.printAll();
    
    cout << "\n✓ Configuration management complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Network Routing (Path Finding with Maps)
**Context:** Implement IP subnet routing lookup table.

**Problem:**
```cpp
// Create routing table:
// 1. Store CIDR blocks → next hop mappings
// 2. Lookup routes for IP addresses
// 3. Longest prefix matching
// 4. Add/remove routes
// 5. Display routing table
```

**Solution:**
```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

class RoutingTable {
private:
    map<string, string> routes;  // CIDR → next_hop
    
public:
    void addRoute(const string &cidr, const string &next_hop) {
        routes[cidr] = next_hop;
        cout << "✓ Route added: " << cidr << " -> " << next_hop << endl;
    }
    
    string lookupRoute(const string &ip) {
        // Simplified: direct lookup matching
        // In real implementation, would do longest prefix matching
        
        for (const auto &pair : routes) {
            if (pair.first == ip) {
                cout << "Matched: " << pair.first << endl;
                return pair.second;
            }
        }
        
        // Default route
        if (routes.find("0.0.0.0/0") != routes.end()) {
            cout << "Using default route" << endl;
            return routes["0.0.0.0/0"];
        }
        
        return "NOT FOUND";
    }
    
    void removeRoute(const string &cidr) {
        if (routes.erase(cidr)) {
            cout << "✓ Route removed: " << cidr << endl;
        }
    }
    
    void display() {
        cout << "\nRouting Table:" << endl;
        cout << "CIDR Block          | Next Hop" << endl;
        cout << "--------------------+---------" << endl;
        for (const auto &pair : routes) {
            cout << pair.first << " | " << pair.second << endl;
        }
    }
};

int main() {
    cout << "=== Map: Network Routing ===" << endl;
    
    RoutingTable rt;
    
    cout << "\n--- Adding routes ---" << endl;
    rt.addRoute("192.168.1.0/24", "eth0");
    rt.addRoute("192.168.2.0/24", "eth1");
    rt.addRoute("10.0.0.0/8", "eth2");
    rt.addRoute("0.0.0.0/0", "eth3");  // default
    
    rt.display();
    
    cout << "\n--- Looking up routes ---" << endl;
    cout << "Looking up 192.168.1.50:\n";
    cout << "Next hop: " << rt.lookupRoute("192.168.1.50") << endl;
    
    cout << "\nLooking up 172.16.0.1:\n";
    cout << "Next hop: " << rt.lookupRoute("172.16.0.1") << endl;
    
    cout << "\n--- Updating route ---" << endl;
    rt.removeRoute("192.168.2.0/24");
    rt.addRoute("192.168.2.0/24", "eth4");
    
    rt.display();
    
    cout << "\n✓ Routing table operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Database Index (Efficient Search)
**Context:** Create an inverted index for fast log searching.

**Problem:**
```cpp
// Implement search index:
// 1. Map keywords to log entries
// 2. Multiple entries per keyword
// 3. Add/remove indexed items
// 4. Search with AND/OR logic
// 5. Display results
```

**Solution:**
```cpp
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct LogEntry {
    int id;
    string message;
    string level;
    
    LogEntry(int i, const string &msg, const string &lvl) 
        : id(i), message(msg), level(lvl) {}
};

class LogIndex {
private:
    map<string, vector<int>> index;  // keyword → [log_ids]
    vector<LogEntry> logs;
    
public:
    void addLog(int id, const string &message, const string &level) {
        LogEntry entry(id, message, level);
        logs.push_back(entry);
        
        // Index by keywords (words in message)
        stringstream ss(message);
        string word;
        while (ss >> word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            index[word].push_back(id);
            index[level].push_back(id);
        }
        
        cout << "✓ Log " << id << " indexed" << endl;
    }
    
    vector<LogEntry> searchByKeyword(const string &keyword) {
        vector<LogEntry> results;
        string key = keyword;
        transform(key.begin(), key.end(), key.begin(), ::tolower);
        
        if (index.find(key) != index.end()) {
            for (int id : index[key]) {
                results.push_back(logs[id]);
            }
        }
        
        return results;
    }
    
    void displayResults(const vector<LogEntry> &results) {
        if (results.empty()) {
            cout << "No results found" << endl;
            return;
        }
        
        cout << "Found " << results.size() << " entries:" << endl;
        for (const auto &entry : results) {
            cout << "  [" << entry.id << "] " << entry.level << ": " 
                 << entry.message << endl;
        }
    }
};

int main() {
    cout << "=== Map: Database Index ===" << endl;
    
    LogIndex index;
    
    cout << "\n--- Adding log entries ---" << endl;
    index.addLog(0, "Network connection established", "INFO");
    index.addLog(1, "Network timeout occurred", "ERROR");
    index.addLog(2, "Database connection failed", "ERROR");
    index.addLog(3, "Configuration loaded successfully", "INFO");
    index.addLog(4, "Network interface UP", "INFO");
    
    cout << "\n--- Searching for 'network' ---" << endl;
    auto results = index.searchByKeyword("network");
    index.displayResults(results);
    
    cout << "\n--- Searching for 'ERROR' level ---" << endl;
    results = index.searchByKeyword("ERROR");
    index.displayResults(results);
    
    cout << "\n--- Searching for 'connection' ---" << endl;
    results = index.searchByKeyword("connection");
    index.displayResults(results);
    
    cout << "\n--- Searching for 'database' ---" << endl;
    results = index.searchByKeyword("database");
    index.displayResults(results);
    
    cout << "\n✓ Index search operations complete" << endl;
    
    return 0;
}
```
