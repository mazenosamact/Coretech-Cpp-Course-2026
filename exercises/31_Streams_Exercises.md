# Streams - Practical Exercises

## Exercise 1: String Data Parsing (CSV Parsing with stringstream)
**Context:** Real-time data systems often receive CSV data that needs parsing and validation.

**Problem:**
```cpp
// Parse employee records from CSV lines:
// 1. Read CSV line with employee data
// 2. Parse fields (name, age, salary, department)
// 3. Validate data types
// 4. Store in structured format
// 5. Display formatted report
```

**Solution:**
```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct Employee {
    string name;
    int age;
    double salary;
    string department;
};

class CSVParser {
public:
    Employee parseLine(const string &line) {
        Employee emp;
        stringstream ss(line);
        string field;
        int field_num = 0;
        
        while (getline(ss, field, ',') && field_num < 4) {
            switch(field_num) {
                case 0:
                    emp.name = field;
                    break;
                case 1:
                    emp.age = stoi(field);
                    break;
                case 2:
                    emp.salary = stod(field);
                    break;
                case 3:
                    emp.department = field;
                    break;
            }
            field_num++;
        }
        
        return emp;
    }
    
    vector<Employee> parseFile(const vector<string> &lines) {
        vector<Employee> employees;
        
        for (const auto &line : lines) {
            employees.push_back(parseLine(line));
        }
        
        return employees;
    }
    
    void displayEmployee(const Employee &emp) {
        cout << left << setw(20) << emp.name
             << setw(5) << emp.age
             << setw(12) << fixed << setprecision(2) << emp.salary
             << emp.department << endl;
    }
};

int main() {
    cout << "=== Streams: CSV Parsing ===" << endl;
    
    vector<string> csv_lines = {
        "John Smith,28,75000.50,Engineering",
        "Sarah Johnson,32,82000.75,Management",
        "Mike Davis,25,65000.00,Marketing",
        "Emily Chen,30,79500.25,Engineering"
    };
    
    CSVParser parser;
    
    cout << "\n--- Parsing CSV data ---" << endl;
    auto employees = parser.parseFile(csv_lines);
    
    cout << "\n--- Employee Report ---" << endl;
    cout << left << setw(20) << "Name"
         << setw(5) << "Age"
         << setw(12) << "Salary"
         << "Department" << endl;
    cout << string(53, '-') << endl;
    
    for (const auto &emp : employees) {
        parser.displayEmployee(emp);
    }
    
    cout << "\n--- Statistics ---" << endl;
    double total = 0;
    for (const auto &emp : employees) {
        total += emp.salary;
    }
    cout << "Average salary: $" << fixed << setprecision(2) 
         << (total / employees.size()) << endl;
    
    cout << "\n✓ CSV parsing complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: String Conversion (Data Type Conversions)
**Context:** System utilities often need to convert between different data types dynamically.

**Problem:**
```cpp
// Implement conversion utilities:
// 1. Convert numbers to formatted strings
// 2. Parse strings to numbers with validation
// 3. Format complex data structures
// 4. Handle conversion errors
// 5. Create formatted output
```

**Solution:**
```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Converter {
public:
    // Convert number to string
    string intToString(int value) {
        stringstream ss;
        ss << value;
        return ss.str();
    }
    
    // Convert float to formatted string
    string floatToString(double value, int precision = 2) {
        stringstream ss;
        ss << fixed << setprecision(precision) << value;
        return ss.str();
    }
    
    // Convert string to integer with validation
    bool stringToInt(const string &str, int &result) {
        stringstream ss(str);
        ss >> result;
        
        // Check if conversion succeeded
        if (ss.fail()) {
            cerr << "✗ Failed to convert '" << str << "' to int" << endl;
            return false;
        }
        return true;
    }
    
    // Convert string to double with validation
    bool stringToDouble(const string &str, double &result) {
        stringstream ss(str);
        ss >> result;
        
        if (ss.fail()) {
            cerr << "✗ Failed to convert '" << str << "' to double" << endl;
            return false;
        }
        return true;
    }
    
    // Format sensor reading
    string formatSensorData(const string &sensor_name, double value, const string &unit) {
        stringstream ss;
        ss << sensor_name << ": " << fixed << setprecision(2) << value << unit;
        return ss.str();
    }
    
    // Parse coordinates from string "x,y"
    bool parseCoordinates(const string &str, int &x, int &y) {
        stringstream ss(str);
        char comma;
        
        ss >> x >> comma >> y;
        
        if (ss.fail() || comma != ',') {
            cerr << "✗ Invalid coordinate format" << endl;
            return false;
        }
        return true;
    }
};

int main() {
    cout << "=== Streams: String Conversions ===" << endl;
    
    Converter conv;
    
    cout << "\n--- Number to String ---" << endl;
    cout << "Integer: " << conv.intToString(42) << endl;
    cout << "Float: " << conv.floatToString(3.14159, 2) << endl;
    cout << "Float (precision 4): " << conv.floatToString(2.71828, 4) << endl;
    
    cout << "\n--- String to Number (with validation) ---" << endl;
    int num = 0;
    if (conv.stringToInt("123", num)) {
        cout << "✓ Converted to: " << num << endl;
    }
    
    double dval = 0.0;
    if (conv.stringToDouble("45.67", dval)) {
        cout << "✓ Converted to: " << dval << endl;
    }
    
    if (!conv.stringToInt("not_a_number", num)) {
        cout << "  (Error handled gracefully)" << endl;
    }
    
    cout << "\n--- Sensor Data Formatting ---" << endl;
    cout << conv.formatSensorData("Temperature", 22.5, "°C") << endl;
    cout << conv.formatSensorData("Humidity", 65.3, "%") << endl;
    cout << conv.formatSensorData("Pressure", 1013.25, "hPa") << endl;
    
    cout << "\n--- Coordinate Parsing ---" << endl;
    int x, y;
    if (conv.parseCoordinates("100,200", x, y)) {
        cout << "✓ Parsed coordinates: (" << x << ", " << y << ")" << endl;
    }
    
    if (!conv.parseCoordinates("invalid", x, y)) {
        cout << "  (Error handled gracefully)" << endl;
    }
    
    cout << "\n✓ Conversions complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: File Configuration Reader (Real-World File I/O)
**Context:** Applications need to read configuration files with key-value pairs.

**Problem:**
```cpp
// Implement config file reader:
// 1. Read config file (key=value format)
// 2. Parse each line
// 3. Validate entries
// 4. Store in map
// 5. Provide access methods
// 6. Generate report
```

**Solution:**
```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

class ConfigFile {
private:
    map<string, string> settings;
    string filename;
    
public:
    ConfigFile(const string &fname) : filename(fname) {}
    
    // Load configuration from file
    bool load() {
        ifstream infile(filename);
        
        if (!infile.is_open()) {
            cerr << "✗ Cannot open file: " << filename << endl;
            return false;
        }
        
        string line;
        int line_num = 0;
        
        while (getline(infile, line)) {
            line_num++;
            
            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') continue;
            
            // Parse key=value
            size_t equals_pos = line.find('=');
            if (equals_pos == string::npos) {
                cerr << "✗ Invalid format at line " << line_num << endl;
                continue;
            }
            
            string key = line.substr(0, equals_pos);
            string value = line.substr(equals_pos + 1);
            
            // Trim whitespace
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            
            settings[key] = value;
            cout << "✓ Loaded: " << key << " = " << value << endl;
        }
        
        infile.close();
        return true;
    }
    
    // Get value by key
    string get(const string &key, const string &default_val = "") {
        if (settings.find(key) != settings.end()) {
            return settings[key];
        }
        return default_val;
    }
    
    // Get integer value
    int getInt(const string &key, int default_val = 0) {
        string val = get(key);
        if (val.empty()) return default_val;
        
        try {
            return stoi(val);
        } catch (...) {
            return default_val;
        }
    }
    
    // Get double value
    double getDouble(const string &key, double default_val = 0.0) {
        string val = get(key);
        if (val.empty()) return default_val;
        
        try {
            return stod(val);
        } catch (...) {
            return default_val;
        }
    }
    
    // Display all settings
    void display() {
        cout << "\n--- Configuration Settings ---" << endl;
        cout << left << setw(30) << "Key" << "Value" << endl;
        cout << string(50, '-') << endl;
        
        for (const auto &pair : settings) {
            cout << left << setw(30) << pair.first << pair.second << endl;
        }
    }
    
    int size() const {
        return settings.size();
    }
};

int main() {
    cout << "=== Streams: File Configuration Reader ===" << endl;
    
    // First, create a sample config file
    {
        ofstream config_file("app.config");
        config_file << "# Application Configuration\n";
        config_file << "app_name=MyApplication\n";
        config_file << "version=1.0.0\n";
        config_file << "port=8080\n";
        config_file << "host=localhost\n";
        config_file << "timeout=30\n";
        config_file << "max_connections=100\n";
        config_file << "debug_mode=true\n";
        config_file << "database_url=localhost:5432\n";
        config_file.close();
        cout << "✓ Created app.config file" << endl;
    }
    
    cout << "\n--- Loading configuration ---" << endl;
    ConfigFile config("app.config");
    
    if (!config.load()) {
        cerr << "Failed to load configuration" << endl;
        return 1;
    }
    
    config.display();
    
    cout << "\n--- Accessing configuration values ---" << endl;
    cout << "App Name: " << config.get("app_name") << endl;
    cout << "Version: " << config.get("version") << endl;
    cout << "Port: " << config.getInt("port") << endl;
    cout << "Timeout: " << config.getInt("timeout") << " seconds" << endl;
    cout << "Max Connections: " << config.getInt("max_connections") << endl;
    
    cout << "\n--- Using defaults for missing keys ---" << endl;
    cout << "Missing key: " << config.get("unknown_key", "default_value") << endl;
    cout << "Missing port: " << config.getInt("unknown_port", 9999) << endl;
    
    cout << "\n✓ Configuration reading complete" << endl;
    
    return 0;
}
```

---

## Exercise 4: Log File Analysis (File Reading and Analysis)
**Context:** System administrators need to parse and analyze log files for errors and patterns.

**Problem:**
```cpp
// Implement log analyzer:
// 1. Read log file line by line
// 2. Parse log entries (timestamp, level, message)
// 3. Count errors/warnings
// 4. Filter by severity
// 5. Generate statistics
// 6. Display results
```

**Solution:**
```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

struct LogEntry {
    string timestamp;
    string level;
    string message;
};

class LogAnalyzer {
private:
    vector<LogEntry> entries;
    map<string, int> level_count;
    
public:
    // Parse log entry format: "[timestamp] LEVEL: message"
    LogEntry parseLine(const string &line) {
        LogEntry entry;
        
        // Extract timestamp [...]
        size_t bracket_close = line.find(']');
        if (bracket_close != string::npos) {
            entry.timestamp = line.substr(1, bracket_close - 1);
        }
        
        // Extract level and message
        size_t level_start = bracket_close + 2;
        size_t colon_pos = line.find(':', level_start);
        
        if (colon_pos != string::npos) {
            entry.level = line.substr(level_start, colon_pos - level_start);
            entry.message = line.substr(colon_pos + 2);
        }
        
        return entry;
    }
    
    // Load log file
    bool loadLog(const string &filename) {
        ifstream infile(filename);
        
        if (!infile.is_open()) {
            cerr << "✗ Cannot open log file: " << filename << endl;
            return false;
        }
        
        string line;
        while (getline(infile, line)) {
            if (!line.empty()) {
                LogEntry entry = parseLine(line);
                entries.push_back(entry);
                level_count[entry.level]++;
            }
        }
        
        infile.close();
        return true;
    }
    
    // Get entries by severity level
    vector<LogEntry> getByLevel(const string &level) {
        vector<LogEntry> filtered;
        for (const auto &entry : entries) {
            if (entry.level == level) {
                filtered.push_back(entry);
            }
        }
        return filtered;
    }
    
    // Display statistics
    void displayStatistics() {
        cout << "\n--- Log Statistics ---" << endl;
        cout << left << setw(15) << "Level" << "Count" << endl;
        cout << string(25, '-') << endl;
        
        for (const auto &pair : level_count) {
            cout << left << setw(15) << pair.first << pair.second << endl;
        }
        
        cout << "Total entries: " << entries.size() << endl;
    }
    
    // Display entries
    void displayEntries(const vector<LogEntry> &entries_to_show, int limit = -1) {
        int count = 0;
        for (const auto &entry : entries_to_show) {
            if (limit != -1 && count >= limit) break;
            
            cout << "[" << entry.timestamp << "] " 
                 << left << setw(8) << entry.level << ": " 
                 << entry.message << endl;
            count++;
        }
    }
    
    int size() const {
        return entries.size();
    }
};

int main() {
    cout << "=== Streams: Log File Analysis ===" << endl;
    
    // Create sample log file
    {
        ofstream log("app.log");
        log << "[2025-01-15 10:30:45] INFO: Application started\n";
        log << "[2025-01-15 10:30:46] DEBUG: Connecting to database\n";
        log << "[2025-01-15 10:30:47] INFO: Database connection established\n";
        log << "[2025-01-15 10:31:00] WARNING: Slow query detected\n";
        log << "[2025-01-15 10:31:15] ERROR: Connection timeout\n";
        log << "[2025-01-15 10:31:16] ERROR: Retrying connection...\n";
        log << "[2025-01-15 10:31:20] INFO: Reconnected successfully\n";
        log << "[2025-01-15 10:32:00] WARNING: High memory usage\n";
        log << "[2025-01-15 10:33:00] DEBUG: Cache invalidated\n";
        log << "[2025-01-15 11:00:00] INFO: Application shutdown\n";
        log.close();
        cout << "✓ Created app.log file" << endl;
    }
    
    cout << "\n--- Loading log file ---" << endl;
    LogAnalyzer analyzer;
    
    if (!analyzer.loadLog("app.log")) {
        return 1;
    }
    
    cout << "✓ Loaded " << analyzer.size() << " log entries" << endl;
    
    analyzer.displayStatistics();
    
    cout << "\n--- All entries ---" << endl;
    analyzer.displayEntries(analyzer.getByLevel(""), -1);
    
    cout << "\n--- ERROR entries only ---" << endl;
    auto errors = analyzer.getByLevel("ERROR");
    analyzer.displayEntries(errors);
    
    cout << "\n--- WARNING entries only ---" << endl;
    auto warnings = analyzer.getByLevel("WARNING");
    analyzer.displayEntries(warnings);
    
    cout << "\n✓ Log analysis complete" << endl;
    
    return 0;
}
```
