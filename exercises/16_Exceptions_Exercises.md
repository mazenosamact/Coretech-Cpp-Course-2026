# Exceptions - Practical Exercises

## Exercise 1: Exception Hierarchy (Error Handling)
**Context:** Backend server needs proper error handling and recovery.

**Problem:**
```cpp
// Create exception hierarchy:
// 1. Base exception class
// 2. Specific exceptions (FileError, ValidationError, NetworkError)
// 3. Try-catch with hierarchy
// 4. Proper error reporting
// 5. Resource cleanup in catch blocks
```

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <exception>
#include <fstream>
using namespace std;

// Exception hierarchy
class AppException : public exception {
protected:
    string message;
    
public:
    AppException(const string &msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class FileException : public AppException {
public:
    FileException(const string &msg) : AppException("FileError: " + msg) {}
};

class ValidationException : public AppException {
public:
    ValidationException(const string &msg) : AppException("ValidationError: " + msg) {}
};

class NetworkException : public AppException {
public:
    NetworkException(const string &msg) : AppException("NetworkError: " + msg) {}
};

class FileHandler {
private:
    string filename;
    ifstream file;
    
public:
    FileHandler(const string &fname) : filename(fname) {
        file.open(fname);
        if (!file.is_open()) {
            throw FileException("Cannot open file: " + fname);
        }
        cout << "✓ File opened: " << fname << endl;
    }
    
    ~FileHandler() {
        if (file.is_open()) {
            file.close();
            cout << "✓ File closed: " << filename << endl;
        }
    }
    
    string readLine() {
        if (!file.is_open()) {
            throw FileException("File not opened");
        }
        
        string line;
        if (!getline(file, line)) {
            throw FileException("Error reading file");
        }
        return line;
    }
};

class Config {
public:
    void validatePort(int port) {
        if (port < 1 || port > 65535) {
            throw ValidationException("Port out of range: " + to_string(port));
        }
    }
    
    void validateIP(const string &ip) {
        if (ip.empty()) {
            throw ValidationException("IP cannot be empty");
        }
    }
};

int main() {
    cout << "=== Exception Hierarchy: Error Handling ===" << endl;
    
    cout << "\n--- Testing file exception ---" << endl;
    try {
        FileHandler fh("nonexistent.txt");
    }
    catch (const FileException &e) {
        cout << "Caught: " << e.what() << endl;
    }
    
    cout << "\n--- Testing validation exception ---" << endl;
    Config cfg;
    try {
        cout << "Validating port 9000..." << endl;
        cfg.validatePort(9000);
        cout << "✓ Port valid" << endl;
        
        cout << "Validating port 99999..." << endl;
        cfg.validatePort(99999);
    }
    catch (const ValidationException &e) {
        cout << "Caught: " << e.what() << endl;
    }
    
    cout << "\n--- Testing IP validation ---" << endl;
    try {
        cfg.validateIP("192.168.1.1");
        cout << "✓ IP valid" << endl;
        
        cfg.validateIP("");
    }
    catch (const ValidationException &e) {
        cout << "Caught: " << e.what() << endl;
    }
    
    cout << "\n✓ Exception handling complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: RAII with Exceptions (Resource Management)
**Context:** Ensure resources are cleaned up even when exceptions occur.

**Problem:**
```cpp
// Implement RAII pattern:
// 1. Resource acquired in constructor
// 2. Resource released in destructor
// 3. Throw exceptions in operations
// 4. Verify cleanup happens
// 5. No resource leaks
```

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <exception>
using namespace std;

class DatabaseConnection {
private:
    string connection_id;
    bool is_connected;
    
public:
    DatabaseConnection(const string &id) : connection_id(id), is_connected(true) {
        cout << "✓ Database connection " << connection_id << " established" << endl;
    }
    
    ~DatabaseConnection() {
        if (is_connected) {
            is_connected = false;
            cout << "✓ Database connection " << connection_id << " closed" << endl;
        }
    }
    
    void executeQuery(const string &query) {
        if (!is_connected) {
            throw runtime_error("Connection not active");
        }
        
        cout << "Executing: " << query << endl;
        
        // Simulate query that might fail
        if (query.find("ERROR") != string::npos) {
            throw runtime_error("Query execution failed");
        }
    }
    
    void beginTransaction() {
        cout << "Transaction started" << endl;
    }
    
    void commit() {
        cout << "Transaction committed" << endl;
    }
    
    void rollback() {
        cout << "Transaction rolled back" << endl;
    }
};

int main() {
    cout << "=== RAII with Exceptions ===" << endl;
    
    cout << "\n--- Successful transaction ---" << endl;
    try {
        DatabaseConnection db("DB1");
        db.beginTransaction();
        db.executeQuery("INSERT INTO users...");
        db.executeQuery("UPDATE logs...");
        db.commit();
    }
    catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    
    cout << "\n--- Failed transaction with automatic cleanup ---" << endl;
    try {
        DatabaseConnection db("DB2");
        db.beginTransaction();
        db.executeQuery("INSERT INTO users...");
        db.executeQuery("ERROR QUERY");  // This will throw
        db.commit();
    }
    catch (const exception &e) {
        cout << "Caught: " << e.what() << endl;
        cout << "(Connection cleaned up automatically)" << endl;
    }
    
    cout << "\n✓ All resources properly cleaned up" << endl;
    
    return 0;
}
```

---

## Exercise 3: Exception Specifications (Function Contracts)
**Context:** Document and enforce exception guarantees.

**Problem:**
```cpp
// Create functions with exception guarantees:
// 1. noexcept functions (no exceptions)
// 2. Functions that can throw specific types
// 3. No-throw guarantee documentation
// 4. Strong exception safety
```

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class SafeArray {
private:
    vector<int> data;
    
public:
    // This function never throws
    int getSize() const noexcept {
        return data.size();
    }
    
    // This function might throw
    int &at(size_t index) {
        if (index >= data.size()) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    // noexcept swap
    void swap(SafeArray &other) noexcept {
        data.swap(other.data);
    }
    
    // Can throw bad_alloc
    void addElement(int value) {
        data.push_back(value);  // Might throw if allocation fails
        cout << "✓ Added: " << value << endl;
    }
    
    // Strong exception safety
    void insertAt(size_t index, int value) {
        if (index > data.size()) {
            throw out_of_range("Invalid insertion position");
        }
        
        // Create temporary with new element
        vector<int> temp = data;
        temp.insert(temp.begin() + index, value);
        
        // If we reach here, swap is guaranteed not to throw
        data = temp;
        cout << "✓ Inserted " << value << " at position " << index << endl;
    }
};

int main() {
    cout << "=== Exception Specifications ===" << endl;
    
    SafeArray arr;
    
    cout << "\n--- Safe operations ---" << endl;
    arr.addElement(10);
    arr.addElement(20);
    arr.addElement(30);
    
    cout << "Size (noexcept): " << arr.getSize() << endl;
    
    cout << "\n--- Using at() with safety ---" << endl;
    try {
        cout << "Element at 1: " << arr.at(1) << endl;
        
        cout << "Accessing invalid index..." << endl;
        arr.at(10);
    }
    catch (const out_of_range &e) {
        cout << "Caught: " << e.what() << endl;
    }
    
    cout << "\n--- Insert with strong exception safety ---" << endl;
    try {
        arr.insertAt(1, 15);
        arr.insertAt(0, 5);
        arr.insertAt(100, 999);  // Will throw before modifying
    }
    catch (const out_of_range &e) {
        cout << "Caught: " << e.what() << endl;
    }
    
    cout << "\n✓ Exception safety guarantees enforced" << endl;
    
    return 0;
}
```
