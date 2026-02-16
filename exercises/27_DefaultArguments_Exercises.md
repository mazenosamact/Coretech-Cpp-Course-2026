# Default Arguments - Practical Exercises

## Exercise 1: Function Parameter Defaults
**Context:** Reduce function overloading with default parameters.

**Problem:**
```cpp
// Implement defaults:
// 1. Simple parameter defaults
// 2. Multiple parameters
// 3. Type conversions with defaults
// 4. Better API design
// 5. Backward compatibility
```

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Logger {
public:
    // Default log level is INFO, default includes timestamp
    void log(const string &message, const string &level = "INFO", 
             bool include_timestamp = true) {
        cout << "[" << level << "]";
        
        if (include_timestamp) {
            cout << " [12:34:56]";
        }
        
        cout << " " << message << endl;
    }
};

class HTTPRequest {
public:
    // Method defaults to GET, timeout defaults to 30 seconds
    string sendRequest(const string &url, 
                      const string &method = "GET",
                      int timeout_seconds = 30,
                      bool follow_redirects = true) {
        cout << "✓ Sending " << method << " request to " << url << endl;
        cout << "  Timeout: " << timeout_seconds << "s" << endl;
        cout << "  Follow redirects: " << (follow_redirects ? "Yes" : "No") << endl;
        
        return "HTTP/200 OK";
    }
};

class Database {
public:
    // Default pool size, default port
    Database(const string &host, int port = 5432, int pool_size = 10) 
        : host(host), port(port), pool_size(pool_size) {
        cout << "✓ Database initialized:" << endl;
        cout << "  Host: " << host << endl;
        cout << "  Port: " << port << endl;
        cout << "  Pool size: " << pool_size << endl;
    }
    
private:
    string host;
    int port;
    int pool_size;
};

int main() {
    cout << "=== Default Arguments: Function Defaults ===" << endl;
    
    Logger logger;
    
    cout << "\n--- Using defaults ---" << endl;
    logger.log("Application started");
    
    cout << "\n--- Overriding one default ---" << endl;
    logger.log("Critical error occurred", "ERROR");
    
    cout << "\n--- Overriding multiple defaults ---" << endl;
    logger.log("Debug trace", "DEBUG", false);
    
    cout << "\n--- HTTP Requests ---" << endl;
    HTTPRequest http;
    
    http.sendRequest("https://api.example.com/users");
    
    cout << endl;
    http.sendRequest("https://api.example.com/data", "POST");
    
    cout << endl;
    http.sendRequest("https://internal.company.com/service", 
                     "PUT", 60, false);
    
    cout << "\n--- Database initialization ---" << endl;
    Database db1("localhost");
    
    cout << endl;
    Database db2("db.production.com", 3306, 50);
    
    cout << "\n✓ Default arguments complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Overloading vs Defaults (Design Comparison)
**Context:** Understand when to use defaults vs overloading.

**Problem:**
```cpp
// Compare approaches:
// 1. Overloaded functions
// 2. Default parameters
// 3. Hybrid approach
// 4. Maintainability
// 5. Code readability
```

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

// --- Approach 1: Overloading ---
class FileReaderOverload {
public:
    // Three overloaded versions
    void readFile(const string &path) {
        readFile(path, "utf-8");
    }
    
    void readFile(const string &path, const string &encoding) {
        readFile(path, encoding, 1024);
    }
    
    void readFile(const string &path, const string &encoding, int buffer_size) {
        cout << "Reading file:" << endl;
        cout << "  Path: " << path << endl;
        cout << "  Encoding: " << encoding << endl;
        cout << "  Buffer: " << buffer_size << " bytes" << endl;
    }
};

// --- Approach 2: Default Parameters ---
class FileReaderDefaults {
public:
    void readFile(const string &path, 
                  const string &encoding = "utf-8",
                  int buffer_size = 1024) {
        cout << "Reading file:" << endl;
        cout << "  Path: " << path << endl;
        cout << "  Encoding: " << encoding << endl;
        cout << "  Buffer: " << buffer_size << " bytes" << endl;
    }
};

// --- Approach 3: Hybrid (recommended) ---
class FileReaderHybrid {
public:
    // Common case: just path
    void readFile(const string &path) {
        readFile(path, "utf-8", 1024);
    }
    
    // Most common variant: path and encoding
    void readFile(const string &path, const string &encoding) {
        readFile(path, encoding, 1024);
    }
    
    // Full control: all parameters
    void readFile(const string &path, 
                  const string &encoding,
                  int buffer_size) {
        cout << "Reading file:" << endl;
        cout << "  Path: " << path << endl;
        cout << "  Encoding: " << encoding << endl;
        cout << "  Buffer: " << buffer_size << " bytes" << endl;
    }
};

int main() {
    cout << "=== Default Arguments: Overloading vs Defaults ===" << endl;
    
    cout << "\n--- Overload approach (3 functions) ---" << endl;
    FileReaderOverload reader1;
    reader1.readFile("file.txt");
    reader1.readFile("file.txt", "utf-16");
    reader1.readFile("file.txt", "utf-16", 2048);
    
    cout << "\n--- Default parameters approach (1 function) ---" << endl;
    FileReaderDefaults reader2;
    reader2.readFile("file.txt");
    reader2.readFile("file.txt", "utf-16");
    reader2.readFile("file.txt", "utf-16", 2048);
    
    cout << "\n--- Hybrid approach (recommended) ---" << endl;
    FileReaderHybrid reader3;
    reader3.readFile("file.txt");
    reader3.readFile("file.txt", "utf-16");
    reader3.readFile("file.txt", "utf-16", 2048);
    
    cout << "\n--- Comparison ---" << endl;
    cout << "Overloading: More explicit, but code duplication" << endl;
    cout << "Defaults: Simpler, but less control over combinations" << endl;
    cout << "Hybrid: Best of both - common cases optimized" << endl;
    
    cout << "\n✓ Comparison complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Advanced Defaults (Policy Pattern)
**Context:** Use defaults to implement policy pattern.

**Problem:**
```cpp
// Use defaults for policies:
// 1. Configure behavior through defaults
// 2. Policy-based design
// 3. Template strategies
// 4. Plugin architecture
// 5. Extensibility
```

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <functional>
using namespace std;

class DataProcessor {
public:
    // Policies as function defaults
    void process(const string &data,
                 bool validate = true,
                 bool compress = false,
                 bool encrypt = false) {
        
        cout << "Processing data..." << endl;
        
        if (validate) {
            cout << "  ✓ Validating..." << endl;
        }
        
        if (compress) {
            cout << "  ✓ Compressing..." << endl;
        }
        
        if (encrypt) {
            cout << "  ✓ Encrypting..." << endl;
        }
        
        cout << "  ✓ Processing complete" << endl;
    }
};

class APIResponse {
public:
    enum class Format { JSON = 0, XML = 1, CSV = 2 };
    
    // Format and pagination as default policies
    void send(int user_id,
              Format format = Format::JSON,
              int page = 1,
              int page_size = 10,
              bool include_metadata = true) {
        
        cout << "Sending response for user " << user_id << ":" << endl;
        
        string format_str = (format == Format::JSON) ? "JSON" :
                           (format == Format::XML) ? "XML" : "CSV";
        cout << "  Format: " << format_str << endl;
        cout << "  Page: " << page << " (" << page_size << " items)" << endl;
        cout << "  Metadata: " << (include_metadata ? "Yes" : "No") << endl;
    }
};

int main() {
    cout << "=== Default Arguments: Policy Pattern ===" << endl;
    
    DataProcessor processor;
    
    cout << "\n--- Default policy (validate only) ---" << endl;
    processor.process("data123");
    
    cout << "\n--- Security policy (validate, encrypt) ---" << endl;
    processor.process("sensitive_data", true, false, true);
    
    cout << "\n--- Performance policy (no validation, compress) ---" << endl;
    processor.process("large_data", false, true, false);
    
    cout << "\n--- Full policy (all features) ---" << endl;
    processor.process("critical_data", true, true, true);
    
    cout << "\n--- API Response policies ---" << endl;
    APIResponse api;
    
    api.send(101);  // Default: JSON, page 1, 10 items, with metadata
    
    cout << endl;
    api.send(102, APIResponse::Format::XML, 1, 20, false);  // Custom format and size
    
    cout << "\n✓ Policy pattern complete" << endl;
    
    return 0;
}
```
