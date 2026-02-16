# Static Keyword - Practical Exercises

## Exercise 1: Static Member Variables (Shared State)
**Context:** Track global state across all instances of a class.

**Problem:**
```cpp
// Implement static members:
// 1. Shared count across all instances
// 2. Static initialization
// 3. Access static members
// 4. Modify through instances and class
// 5. Compare with instance variables
```

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Sensor {
private:
    int sensor_id;
    float last_reading;
    static int instance_count;  // Shared across all instances
    static vector<string> sensor_log;
    
public:
    Sensor(int id) : sensor_id(id), last_reading(0.0f) {
        instance_count++;
        cout << "✓ Sensor " << id << " created (total: " << instance_count << ")" << endl;
    }
    
    ~Sensor() {
        instance_count--;
        cout << "✓ Sensor " << sensor_id << " destroyed (remaining: " << instance_count << ")" << endl;
    }
    
    void recordReading(float value) {
        last_reading = value;
        string log_msg = "Sensor " + to_string(sensor_id) + ": " + to_string(value);
        sensor_log.push_back(log_msg);
        cout << "Recorded: " << log_msg << endl;
    }
    
    static int getInstanceCount() {
        return instance_count;
    }
    
    static void displayLog() {
        cout << "\nSensor Activity Log:" << endl;
        for (const auto &entry : sensor_log) {
            cout << "  " << entry << endl;
        }
    }
};

// Static member initialization (outside class)
int Sensor::instance_count = 0;
vector<string> Sensor::sensor_log;

int main() {
    cout << "=== Static: Shared Member Variables ===" << endl;
    
    cout << "\n--- Creating sensors ---" << endl;
    Sensor s1(101);
    Sensor s2(102);
    Sensor s3(103);
    
    cout << "\n--- Recording readings ---" << endl;
    s1.recordReading(22.5);
    s2.recordReading(23.1);
    s3.recordReading(22.8);
    
    cout << "\n--- Checking static count ---" << endl;
    cout << "Total sensors: " << Sensor::getInstanceCount() << endl;
    
    s1.recordReading(22.7);
    
    cout << "\n--- Displaying log ---" << endl;
    Sensor::displayLog();
    
    cout << "\n--- Destroying a sensor ---" << endl;
    {
        Sensor temp(104);
        temp.recordReading(23.2);
        cout << "Temp sensor about to go out of scope..." << endl;
    }
    
    cout << "Remaining sensors: " << Sensor::getInstanceCount() << endl;
    
    cout << "\n✓ Static members complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Static Member Functions (No 'this')
**Context:** Class methods that don't need instance data.

**Problem:**
```cpp
// Implement static functions:
// 1. Factory methods
// 2. Utility functions
// 3. No access to 'this'
// 4. Call on class, not instance
// 5. Common use patterns
```

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Logger {
private:
    static vector<string> messages;
    static string log_level;
    
    Logger() {}  // Private to prevent instantiation
    
public:
    static void setLogLevel(const string &level) {
        log_level = level;
        cout << "✓ Log level set to: " << level << endl;
    }
    
    static void info(const string &msg) {
        if (log_level == "DEBUG" || log_level == "INFO") {
            messages.push_back("[INFO] " + msg);
            cout << "[INFO] " << msg << endl;
        }
    }
    
    static void error(const string &msg) {
        messages.push_back("[ERROR] " + msg);
        cout << "[ERROR] " << msg << endl;
    }
    
    static void debug(const string &msg) {
        if (log_level == "DEBUG") {
            messages.push_back("[DEBUG] " + msg);
            cout << "[DEBUG] " << msg << endl;
        }
    }
    
    static void displayAll() {
        cout << "\nAll logs:" << endl;
        for (const auto &msg : messages) {
            cout << "  " << msg << endl;
        }
    }
};

// Static member initialization
vector<string> Logger::messages;
string Logger::log_level = "INFO";

class Config {
private:
    string hostname;
    int port;
    
public:
    Config(const string &h, int p) : hostname(h), port(p) {}
    
    // Static factory method
    static Config createDefault() {
        cout << "Creating default config..." << endl;
        return Config("localhost", 8080);
    }
    
    static Config createProduction() {
        cout << "Creating production config..." << endl;
        return Config("api.example.com", 443);
    }
    
    void display() const {
        cout << "Config: " << hostname << ":" << port << endl;
    }
};

int main() {
    cout << "=== Static: Member Functions (Utilities) ===" << endl;
    
    cout << "\n--- Using Logger (static utility class) ---" << endl;
    Logger::setLogLevel("DEBUG");
    
    Logger::info("Application started");
    Logger::debug("Connection opened");
    Logger::error("Failed to connect to database");
    Logger::info("Retrying connection");
    
    Logger::displayAll();
    
    cout << "\n--- Using static factory methods ---" << endl;
    auto dev_config = Config::createDefault();
    dev_config.display();
    
    auto prod_config = Config::createProduction();
    prod_config.display();
    
    cout << "\n✓ Static functions complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Static Local Variables (Persistent Storage)
**Context:** Function maintaining state across multiple calls.

**Problem:**
```cpp
// Use static local variables:
// 1. Function-scoped persistence
// 2. Initialization once
// 3. Preserve value between calls
// 4. Unique ID generation
// 5. Lazy initialization
```

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

int generateUniqueID() {
    static int next_id = 1000;  // Initialized once on first call
    return next_id++;
}

void demonstrateCounter() {
    static int call_count = 0;  // Persists across calls
    call_count++;
    cout << "Function called " << call_count << " times" << endl;
}

string getConnectionString() {
    static string connection;  // Initialized once
    
    if (connection.empty()) {
        cout << "  (initializing connection...)" << endl;
        connection = "Server=localhost;Port=5432;Database=mydb";
    } else {
        cout << "  (using cached connection)" << endl;
    }
    
    return connection;
}

class Counter {
public:
    int getValue() {
        static int value = 0;  // Instance-level static
        return value++;
    }
    
    void reset() {
        // No way to reset static local variable
        // This is a limitation of static local variables
    }
};

int main() {
    cout << "=== Static: Local Variables ===" << endl;
    
    cout << "\n--- Generating unique IDs ---" << endl;
    cout << "ID 1: " << generateUniqueID() << endl;
    cout << "ID 2: " << generateUniqueID() << endl;
    cout << "ID 3: " << generateUniqueID() << endl;
    cout << "ID 4: " << generateUniqueID() << endl;
    
    cout << "\n--- Function call counter ---" << endl;
    demonstrateCounter();
    demonstrateCounter();
    demonstrateCounter();
    demonstrateCounter();
    
    cout << "\n--- Lazy initialization (first call only) ---" << endl;
    cout << "Connection 1:" << endl;
    string conn1 = getConnectionString();
    cout << "  " << conn1 << endl;
    
    cout << "Connection 2 (reuses cached):" << endl;
    string conn2 = getConnectionString();
    cout << "  " << conn2 << endl;
    
    cout << "\n--- Object instance with static local ---" << endl;
    Counter cnt;
    cout << "Value 1: " << cnt.getValue() << endl;
    cout << "Value 2: " << cnt.getValue() << endl;
    cout << "Value 3: " << cnt.getValue() << endl;
    
    cout << "\n✓ Static local variables complete" << endl;
    
    return 0;
}
```
