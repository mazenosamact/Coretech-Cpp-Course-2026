# iostream and Streams - Practical Exercises

## Exercise 1: Configuration File Parser (Linux System Administration)
**Context:** System configuration utility that reads and validates configuration files.

**Problem:**
```cpp
// Parse a configuration file with format:
// hostname=myserver
// port=8080
// debug=true
// max_connections=100
//
// Tasks:
// 1. Read configuration using ifstream
// 2. Parse key=value pairs
// 3. Validate data types (string, int, bool)
// 4. Report errors with line numbers
// 5. Write parsed config to binary file using ofstream
```

**Solution:**
```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

class ConfigParser {
private:
    map<string, string> config;
    
public:
    bool loadFromFile(const char *filename) {
        ifstream infile(filename);
        
        if (!infile.is_open()) {
            cerr << "Error: Cannot open file " << filename << endl;
            return false;
        }
        
        string line;
        int line_num = 0;
        
        while (getline(infile, line)) {
            line_num++;
            
            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') continue;
            
            size_t pos = line.find('=');
            if (pos == string::npos) {
                cerr << "Error at line " << line_num << ": No '=' found" << endl;
                continue;
            }
            
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);
            
            // Trim whitespace
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            
            config[key] = value;
            cout << "Loaded: " << key << " = " << value << endl;
        }
        
        infile.close();
        return true;
    }
    
    bool getInt(const string &key, int &value) {
        if (config.find(key) == config.end()) {
            cerr << "Key not found: " << key << endl;
            return false;
        }
        
        try {
            value = stoi(config[key]);
            return true;
        } catch (...) {
            cerr << "Error: '" << key << "' is not a valid integer" << endl;
            return false;
        }
    }
    
    bool getBool(const string &key, bool &value) {
        if (config.find(key) == config.end()) {
            cerr << "Key not found: " << key << endl;
            return false;
        }
        
        string val = config[key];
        if (val == "true" || val == "1" || val == "yes") {
            value = true;
            return true;
        } else if (val == "false" || val == "0" || val == "no") {
            value = false;
            return true;
        }
        
        cerr << "Error: '" << key << "' is not a valid boolean" << endl;
        return false;
    }
    
    string getString(const string &key) {
        if (config.find(key) != config.end()) {
            return config[key];
        }
        return "";
    }
    
    void saveToFile(const char *filename) {
        ofstream outfile(filename);
        
        for (const auto &pair : config) {
            outfile << pair.first << "=" << pair.second << endl;
        }
        
        outfile.close();
        cout << "\n✓ Configuration saved to " << filename << endl;
    }
};

int main() {
    cout << "=== Configuration File Parser ===" << endl;
    
    // Create a sample config file
    ofstream sample("config.txt");
    sample << "# Server Configuration\n";
    sample << "hostname=myserver\n";
    sample << "port=8080\n";
    sample << "debug=true\n";
    sample << "max_connections=100\n";
    sample.close();
    
    ConfigParser parser;
    
    cout << "\n--- Loading configuration ---" << endl;
    parser.loadFromFile("config.txt");
    
    cout << "\n--- Retrieving values ---" << endl;
    cout << "Hostname: " << parser.getString("hostname") << endl;
    
    int port = 0;
    if (parser.getInt("port", port)) {
        cout << "Port: " << port << endl;
    }
    
    bool debug = false;
    if (parser.getBool("debug", debug)) {
        cout << "Debug mode: " << (debug ? "enabled" : "disabled") << endl;
    }
    
    int max_conn = 0;
    if (parser.getInt("max_connections", max_conn)) {
        cout << "Max connections: " << max_conn << endl;
    }
    
    cout << "\n✓ Configuration parsed successfully" << endl;
    
    return 0;
}
```

---

## Exercise 2: Real-time Data Logger (Embedded Systems/Backend)
**Context:** System that logs real-time sensor data with timestamps and formatting.

**Problem:**
```cpp
// Create a data logger that:
// 1. Writes to both console (cout) and file (ofstream)
// 2. Formats output with timestamps and precision
// 3. Uses stringstream for formatting complex data
// 4. Handles binary data logging
//
// Log format: [HH:MM:SS] SENSOR_ID: VALUE UNIT
```

**Solution:**
```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;

class DataLogger {
private:
    ofstream logfile;
    
public:
    DataLogger(const char *filename) {
        logfile.open(filename, ios::app);
        if (!logfile) {
            cerr << "Cannot open log file" << endl;
        }
    }
    
    ~DataLogger() {
        if (logfile.is_open()) {
            logfile.close();
        }
    }
    
    void logSensorData(int sensor_id, float value, const char *unit,
                       bool console_output = true) {
        time_t now = time(nullptr);
        struct tm *timeinfo = localtime(&now);
        
        // Create formatted output using stringstream
        stringstream ss;
        ss << "[" << setfill('0')
           << setw(2) << timeinfo->tm_hour << ":"
           << setw(2) << timeinfo->tm_min << ":"
           << setw(2) << timeinfo->tm_sec << "] "
           << "SENSOR_" << sensor_id << ": "
           << fixed << setprecision(2) << value << " " << unit;
        
        string output = ss.str();
        
        // Write to both console and file
        if (console_output) {
            cout << output << endl;
        }
        
        if (logfile.is_open()) {
            logfile << output << endl;
            logfile.flush();
        }
    }
    
    void logEvent(const char *event_type, const char *message) {
        time_t now = time(nullptr);
        struct tm *timeinfo = localtime(&now);
        
        stringstream ss;
        ss << "[" << setfill('0')
           << setw(2) << timeinfo->tm_hour << ":"
           << setw(2) << timeinfo->tm_min << ":"
           << setw(2) << timeinfo->tm_sec << "] "
           << "[" << event_type << "] "
           << message;
        
        string output = ss.str();
        cout << output << endl;
        
        if (logfile.is_open()) {
            logfile << output << endl;
            logfile.flush();
        }
    }
};

int main() {
    cout << "=== Real-time Data Logger ===" << endl;
    
    DataLogger logger("sensor_data.log");
    
    cout << "\n--- Logging sensor readings ---" << endl;
    
    logger.logEvent("SYSTEM", "Logger started");
    
    // Simulate sensor readings
    logger.logSensorData(1, 22.5, "°C");
    logger.logSensorData(2, 45.2, "%");
    logger.logSensorData(3, 101.3, "kPa");
    logger.logSensorData(1, 23.1, "°C");
    logger.logSensorData(2, 46.5, "%");
    
    logger.logEvent("ALARM", "Temperature threshold exceeded!");
    
    logger.logEvent("SYSTEM", "Logger stopped");
    
    cout << "\n✓ Logs saved to sensor_data.log" << endl;
    
    return 0;
}
```

---

## Exercise 3: Formatted Report Generation (Backend/Reporting)
**Context:** Generate formatted reports with aligned columns and tables.

**Problem:**
```cpp
// Generate a sales report with:
// 1. Column headers with proper alignment
// 2. Data rows with formatted numbers
// 3. Subtotals and grand totals
// 4. Output to both console and CSV file
//
// Format:
// Product    | Qty  | Price   | Total
// -----------+------+---------+----------
// Widget A   | 100  | $25.99  | $2599.00
```

**Solution:**
```cpp
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

struct SalesRecord {
    string product;
    int quantity;
    double price;
};

int main() {
    cout << "=== Sales Report Generator ===" << endl;
    
    SalesRecord sales[] = {
        {"Widget A", 100, 25.99},
        {"Gadget B", 50, 149.99},
        {"Tool C", 75, 89.50}
    };
    int num_items = 3;
    
    // Console output
    cout << "\n--- Formatted Console Report ---" << endl;
    cout << setw(15) << left << "Product"
         << setw(10) << "Quantity"
         << setw(12) << "Price"
         << setw(12) << "Total" << endl;
    cout << string(49, '-') << endl;
    
    double grand_total = 0;
    
    for (int i = 0; i < num_items; i++) {
        double total = sales[i].quantity * sales[i].price;
        grand_total += total;
        
        cout << setw(15) << left << sales[i].product
             << setw(10) << sales[i].quantity
             << "$" << fixed << setprecision(2) << setw(10) << sales[i].price
             << "$" << setw(10) << total << endl;
    }
    
    cout << string(49, '-') << endl;
    cout << setw(35) << right << "Grand Total: $"
         << fixed << setprecision(2) << grand_total << endl;
    
    // CSV file output
    ofstream csvfile("sales_report.csv");
    csvfile << "Product,Quantity,Price,Total\n";
    
    grand_total = 0;
    for (int i = 0; i < num_items; i++) {
        double total = sales[i].quantity * sales[i].price;
        grand_total += total;
        
        csvfile << sales[i].product << ","
                << sales[i].quantity << ","
                << fixed << setprecision(2) << sales[i].price << ","
                << total << "\n";
    }
    
    csvfile << ",,Grand Total," << fixed << setprecision(2) << grand_total << "\n";
    csvfile.close();
    
    cout << "\n✓ Report saved to sales_report.csv" << endl;
    
    return 0;
}
```
