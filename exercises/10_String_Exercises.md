# std::string - Practical Exercises

## Exercise 1: String Manipulation and Parsing (Linux System Administration)
**Context:** Parse command-line arguments and configuration strings.

**Problem:**
```cpp
// Create a command parser:
// 1. Parse command: "command --arg1=value1 --arg2=value2"
// 2. Extract parameters
// 3. Find and replace patterns
// 4. Handle edge cases
```

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CommandParser {
private:
    string command;
    vector<pair<string, string>> arguments;
    
public:
    CommandParser(const string &cmd) : command(cmd) {
        parseCommand();
    }
    
    void parseCommand() {
        cout << "Parsing: " << command << endl;
        
        size_t pos = 0;
        while (pos < command.length()) {
            // Find next argument starting with --
            pos = command.find("--", pos);
            if (pos == string::npos) break;
            
            // Extract key=value
            size_t eq_pos = command.find('=', pos);
            size_t space_pos = command.find(' ', pos);
            
            if (eq_pos != string::npos) {
                string key = command.substr(pos + 2, eq_pos - pos - 2);
                size_t end = space_pos != string::npos ? space_pos : command.length();
                string value = command.substr(eq_pos + 1, end - eq_pos - 1);
                
                arguments.push_back({key, value});
                cout << "  Found: " << key << " = " << value << endl;
                
                pos = end;
            } else {
                pos++;
            }
        }
    }
    
    string getArgument(const string &key) {
        for (const auto &arg : arguments) {
            if (arg.first == key) {
                return arg.second;
            }
        }
        return "";
    }
    
    bool hasArgument(const string &key) {
        return !getArgument(key).empty();
    }
};

int main() {
    cout << "=== String Parsing and Manipulation ===" << endl;
    
    string cmd = "build --output=/bin/app --config=/etc/app.conf --debug=true";
    CommandParser parser(cmd);
    
    cout << "\n--- Extracting parameters ---" << endl;
    cout << "Output: " << parser.getArgument("output") << endl;
    cout << "Config: " << parser.getArgument("config") << endl;
    cout << "Debug: " << parser.getArgument("debug") << endl;
    
    return 0;
}
```

---

## Exercise 2: String Building and Formatting (Backend/Logging)
**Context:** Building log messages and database queries dynamically.

**Problem:**
```cpp
// Create SQL query builder:
// 1. Build INSERT statement
// 2. Build WHERE clauses
// 3. Escape special characters
// 4. Format for execution
```

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

class QueryBuilder {
private:
    string table;
    string columns;
    string values;
    string where_clause;
    
    string escapeString(const string &str) {
        string escaped;
        for (char c : str) {
            if (c == '\'') {
                escaped += "\\'";
            } else {
                escaped += c;
            }
        }
        return escaped;
    }
    
public:
    QueryBuilder(const string &tbl) : table(tbl) {}
    
    QueryBuilder &insert(const string &col, const string &val) {
        if (!columns.empty()) {
            columns += ", ";
            values += ", ";
        }
        columns += col;
        values += "'" + escapeString(val) + "'";
        return *this;
    }
    
    QueryBuilder &where(const string &condition) {
        where_clause = " WHERE " + condition;
        return *this;
    }
    
    string build() {
        string query = "INSERT INTO " + table + " (" + columns + ") VALUES (" + 
                      values + ")";
        if (!where_clause.empty()) {
            query += where_clause;
        }
        return query;
    }
};

int main() {
    cout << "=== SQL Query Building ===" << endl;
    
    QueryBuilder query1("users");
    query1.insert("name", "John O'Brien")
          .insert("email", "john@example.com")
          .insert("age", "25");
    
    cout << "\nGenerated query:" << endl;
    cout << query1.build() << endl;
    
    return 0;
}
```

---

## Exercise 3: String Comparison and Search (Data Processing)
**Context:** Processing log files with string matching and pattern detection.

**Problem:**
```cpp
// Create log filter:
// 1. Search for error patterns
// 2. Count occurrences
// 3. Extract matching lines
// 4. Generate statistics
```

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class LogAnalyzer {
private:
    vector<string> logs;
    
public:
    void addLog(const string &log) {
        logs.push_back(log);
    }
    
    int countOccurrences(const string &pattern) {
        int count = 0;
        for (const string &log : logs) {
            if (log.find(pattern) != string::npos) {
                count++;
            }
        }
        return count;
    }
    
    vector<string> filter(const string &pattern) {
        vector<string> results;
        for (const string &log : logs) {
            if (log.find(pattern) != string::npos) {
                results.push_back(log);
            }
        }
        return results;
    }
    
    void printStatistics(const string &pattern) {
        int count = countOccurrences(pattern);
        cout << "Pattern '" << pattern << "' found " << count << " times" << endl;
        
        vector<string> matches = filter(pattern);
        if (!matches.empty()) {
            cout << "Matching logs:" << endl;
            for (const string &log : matches) {
                cout << "  - " << log << endl;
            }
        }
    }
};

int main() {
    cout << "=== Log File Analysis ===" << endl;
    
    LogAnalyzer analyzer;
    
    analyzer.addLog("[INFO] Application started");
    analyzer.addLog("[ERROR] Connection failed");
    analyzer.addLog("[WARN] Memory usage high");
    analyzer.addLog("[ERROR] Database timeout");
    analyzer.addLog("[INFO] Operation complete");
    analyzer.addLog("[ERROR] Invalid input");
    
    cout << "\n--- Searching for errors ---" << endl;
    analyzer.printStatistics("[ERROR]");
    
    cout << "\n--- Searching for warnings ---" << endl;
    analyzer.printStatistics("[WARN]");
    
    cout << "\n--- All logs containing 'timeout' ---" << endl;
    vector<string> timeout_logs = analyzer.filter("timeout");
    for (const string &log : timeout_logs) {
        cout << "  " << log << endl;
    }
    
    return 0;
}
```

---

## Exercise 4: CSV Parsing (Data Import/Export)
**Context:** Parse CSV files split by comma delimiters.

**Problem:**
```cpp
// Create a simple CSV line parser:
// 1. Split CSV line by commas
// 2. Pair fields with headers
// 3. Print formatted output to stdout
```

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

void parseCSVLine(const string &headers, const string &data) {
    size_t h_pos = 0, d_pos = 0;
    
    while (h_pos < headers.length() && d_pos < data.length()) {
        // Find next comma in headers
        size_t h_comma = headers.find(',', h_pos);
        if (h_comma == string::npos) h_comma = headers.length();
        
        // Find next comma in data
        size_t d_comma = data.find(',', d_pos);
        if (d_comma == string::npos) d_comma = data.length();
        
        // Extract header and data field
        string header = headers.substr(h_pos, h_comma - h_pos);
        string value = data.substr(d_pos, d_comma - d_pos);
        
        // Print formatted output
        cout << header << ": " << value << endl;
        
        // Move to next field
        h_pos = h_comma + 1;
        d_pos = d_comma + 1;
    }
}

int main() {
    cout << "=== CSV Parsing ===" << endl;
    
    string headers = "Name,Email,City,Salary";
    
    cout << "\nRecord 1:" << endl;
    parseCSVLine(headers, "John Smith,john@example.com,New York,75000");
    
    cout << "\nRecord 2:" << endl;
    parseCSVLine(headers, "Jane Doe,jane@example.com,Los Angeles,82000");
    
    cout << "\nRecord 3:" << endl;
    parseCSVLine(headers, "Alice Johnson,alice@example.com,Chicago,95000");
    
    return 0;
}
```
