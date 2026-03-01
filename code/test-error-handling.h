#ifndef TEST_ERROR_HANDLING_H
#define TEST_ERROR_HANDLING_H

#include <iostream>
#include <cassert>
#include <type_traits>
// #include <concepts>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <optional>
#include <map>
#include <vector>
#include <string>

using namespace std;

// ============================================================================
// 1. Basic Assertions
// ============================================================================
#if 0

void processArray(int* arr, int size) {
    assert(arr != nullptr);      // Check precondition
    assert(size > 0);            // Check precondition
    assert(size <= 1000);        // Reasonable size
    
    for (int i = 0; i < size; i++) {
        assert(i >= 0 && i < size);  // Loop invariant
        arr[i] *= 2;
    }
}

int main() {
    int arr[10] = {1, 2, 3};
    processArray(arr, 10);  // ✓ Works
    
    // processArray(nullptr, 10);  // ✗ Assertion fails!
    // processArray(arr, -1);      // ✗ Assertion fails!
    
    return 0;
}

#endif

// ============================================================================
// 2. Design by Contract with BankAccount
// ============================================================================
#if 0

class BankAccount {
private:
    double balance;
    
    // Class invariant: balance must always be >= 0
    bool invariant() const {
        return balance >= 0;
    }
    
public:
    BankAccount(double initial) : balance(initial) {
        assert(initial >= 0);  // Precondition
        assert(invariant());
    }
    
    void deposit(double amount) {
        // Precondition: amount must be positive
        assert(amount > 0);
        
        double oldBalance = balance;
        balance += amount;
        
        // Postcondition: balance increased by exactly amount
        assert(balance == oldBalance + amount);
        assert(invariant());
    }
    
    bool withdraw(double amount) {
        // Precondition
        assert(amount > 0);
        
        if (balance < amount) {
            return false;  // Not enough funds
        }
        
        balance -= amount;
        
        // Postcondition: balance decreased by exactly amount
        assert(balance == (balance + amount) - amount);
        assert(invariant());
        return true;
    }
};

#endif

// ============================================================================
// 3. static_assert Example
// ============================================================================
#if 0

// Ensure a type has specific properties
template<typename T>
class SmartPointer {
    static_assert(std::is_object_v<T>, "T must be an object type");
    
public:
    SmartPointer() {}
};

// Compile-time size checking
class DataBuffer {
    static_assert(sizeof(int) == 4, "This code assumes 32-bit integers");
    static_assert(sizeof(long) >= 8, "Requires 64-bit longs");
};

int main() {
    // ✓ Works with object types
    SmartPointer<int> sp1;
    SmartPointer<std::string> sp2;
    
    // ✗ Compilation error: void is not an object type
    // SmartPointer<void> sp3;
    
    return 0;
}

#endif

// ============================================================================
// 4. std::enable_if for Type-Safe Generics
// ============================================================================
#if 0

// Generic version for integral types
template<typename T>
typename std::enable_if<std::is_integral_v<T>, T>::type
add(T a, T b) {
    return a + b;
}

// Specialized version for floating-point types
template<typename T>
typename std::enable_if<std::is_floating_point_v<T>, T>::type
add(T a, T b) {
    return a + b;
}

// Version for arrays (not allowed)
template<typename T>
typename std::enable_if<std::is_array_v<T>>::type
add(T a, T b) {
    // This won't compile if T is an array
    static_assert(false, "Cannot add arrays");
}

int main() {
    cout << add(5, 10) << endl;           // Uses integral version: 15
    cout << add(3.5, 2.5) << endl;        // Uses floating-point version: 6
    
    // add(arr1, arr2);                   // ✗ Compilation error!
    
    return 0;
}

#endif

// ============================================================================
// 5. Concepts (C++20) Example
// ============================================================================
#if 0

// Define a concept for addable types
template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

// Function that requires Addable type
template<Addable T>
T safeAdd(T a, T b) {
    return a + b;
}

int main() {
    cout << safeAdd(5, 10) << endl;       // ✓ int is Addable
    cout << safeAdd(3.5, 2.5) << endl;    // ✓ double is Addable
    
    // safeAdd(std::string("a"), std::string("b"));  // May fail if not addable
    
    return 0;
}

#endif

// ============================================================================
// 6. Traditional Error Code Pattern
// ============================================================================
#if 0

enum class FileError {
    Success = 0,
    FileNotFound = 1,
    PermissionDenied = 2,
    IOError = 3,
    InvalidFormat = 4
};

class FileReader {
public:
    FileError readFile(const std::string& filename, std::string& content) {
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            return FileError::FileNotFound;
        }
        
        if (!file.good()) {
            return FileError::PermissionDenied;
        }
        
        std::stringstream buffer;
        if (!(buffer << file.rdbuf())) {
            return FileError::IOError;
        }
        
        content = buffer.str();
        return FileError::Success;
    }
};

// Traditional C-style: Check errno
void readFileC(const char* filename) {
    FILE* file = fopen(filename, "r");
    
    if (file == nullptr) {
        // errno is set by fopen() on failure
        printf("Error: %s\n", strerror(errno));  // Print human-readable error
    } else {
        fclose(file);
    }
}

int main() {
    FileReader reader;
    std::string content;
    
    FileError result = reader.readFile("data.txt", content);
    
    switch (result) {
        case FileError::Success:
            cout << "File read successfully" << endl;
            break;
        case FileError::FileNotFound:
            cout << "Error: File not found" << endl;
            break;
        case FileError::IOError:
            cout << "Error: IO error occurred" << endl;
            break;
        default:
            cout << "Unknown error" << endl;
    }
    
    return 0;
}

#endif

// ============================================================================
// 7. [[nodiscard]] Example with Error Codes
// ============================================================================
#if 0

enum class FileError {
    Success = 0,
    FileNotFound = 1,
    PermissionDenied = 2,
    IOError = 3
};

class FileReader {
public:
    // [[nodiscard]] forces caller to check the error code
    [[nodiscard]] FileError readFile(const std::string& filename, std::string& content) {
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            return FileError::FileNotFound;
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
        return FileError::Success;
    }
};

int main() {
    FileReader reader;
    std::string content;
    
    // ✓ Good: Error code is checked
    auto result = reader.readFile("data.txt", content);
    if (result != FileError::Success) {
        cout << "Error: " << static_cast<int>(result) << endl;
    }
    
    // ✗ Compiler warning: ignoring return value marked with [[nodiscard]]
    // reader.readFile("data.txt", content);
    
    return 0;
}

#endif

// ============================================================================
// 8. Basic Exception Handling
// ============================================================================
#if 0

class DivisionByZeroException : public std::runtime_error {
public:
    DivisionByZeroException() 
        : std::runtime_error("Division by zero") {}
};

double safeDivide(double dividend, double divisor) {
    if (divisor == 0) {
        throw DivisionByZeroException();
    }
    return dividend / divisor;
}

int main() {
    try {
        double result = safeDivide(10, 0);  // Throws exception
        cout << result << endl;
    } catch (const DivisionByZeroException& e) {
        cout << "Caught exception: " << e.what() << endl;
    } catch (const std::exception& e) {
        cout << "General exception: " << e.what() << endl;
    }
    
    return 0;
}
// Output: Caught exception: Division by zero

#endif

// ============================================================================
// 9. RAII and Exception Safety with FileHandle
// ============================================================================
#if 0

class FileHandle {
private:
    std::ifstream file;
    
public:
    FileHandle(const std::string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
    }
    
    // Destructor automatically closes file, even if exception occurs
    ~FileHandle() {
        if (file.is_open()) {
            file.close();
        }
    }
    
    std::string readContent() {
        if (!file.good()) {
            throw std::runtime_error("File stream is not in good state");
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};

int main() {
    try {
        FileHandle fileHandle("data.txt");
        std::string content = fileHandle.readContent();
        cout << "File content: " << content << endl;
        // File automatically closed here by destructor
    } catch (const std::exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    return 0;
}

#endif

// ============================================================================
// 10. Exception Processing with Standard Hierarchy
// ============================================================================
#if 0

void processInput(int value) {
    if (value < 0) {
        throw std::invalid_argument("Value must be non-negative");
    }
    if (value > 100) {
        throw std::out_of_range("Value must be <= 100");
    }
}

#endif

// ============================================================================
// 11. Exception Safety Guarantees with Stack
// ============================================================================
#if 0

class Stack {
private:
    std::vector<int> data;
    
public:
    // Strong exception safety: Either succeeds or leaves state unchanged
    void push(int value) {
        std::vector<int> backup = data;  // Backup
        try {
            data.push_back(value);  // Might throw
        } catch (...) {
            data = backup;  // Restore on failure
            throw;
        }
    }
    
    // No-throw guarantee: Never throws exceptions
    int pop() noexcept {
        if (data.empty()) {
            return -1;  // Return error code instead of throwing
        }
        int value = data.back();
        data.pop_back();
        return value;
    }
};

#endif

// ============================================================================
// 12. std::optional Basic Usage
// ============================================================================
#if 0

std::optional<int> stringToInt(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (const std::exception&) {
        return std::nullopt;  // Return "no value"
    }
}

int main() {
    std::optional<int> result = stringToInt("42");
    
    if (result.has_value()) {
        cout << "Converted value: " << result.value() << endl;
    } else {
        cout << "Conversion failed" << endl;
    }
    
    // Alternative syntax using operator*
    if (result) {
        cout << "Value: " << *result << endl;
    }
    
    // With default value
    cout << "Value or default: " << result.value_or(0) << endl;
    
    return 0;
}

#endif

// ============================================================================
// 13. std::optional Database Query Example
// ============================================================================
#if 0

struct User {
    int id;
    std::string name;
    std::string email;
};

class UserDatabase {
private:
    std::map<int, User> users;
    
public:
    // Returns std::optional - either a User or nothing
    std::optional<User> findUserById(int id) const {
        auto it = users.find(id);
        if (it != users.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
    std::optional<User> findUserByEmail(const std::string& email) const {
        for (const auto& [id, user] : users) {
            if (user.email == email) {
                return user;
            }
        }
        return std::nullopt;
    }
};

int main() {
    UserDatabase db;
    
    std::optional<User> user = db.findUserById(123);
    
    if (user) {
        cout << "Found user: " << user->name << endl;
    } else {
        cout << "User not found" << endl;
    }
    
    // Using value_or() with default
    auto foundUser = db.findUserByEmail("john@example.com")
        .value_or(User{-1, "Unknown", ""});
    
    return 0;
}

#endif

// ============================================================================
// 14. std::expected Basic Usage
// ============================================================================
#if 0

enum class ParseError {
    InvalidFormat,
    ValueOutOfRange,
    EmptyString
};

std::expected<int, ParseError> parseInteger(const std::string& str) {
    if (str.empty()) {
        return std::unexpected(ParseError::EmptyString);
    }
    
    try {
        int value = std::stoi(str);
        if (value < 0 || value > 100) {
            return std::unexpected(ParseError::ValueOutOfRange);
        }
        return value;
    } catch (const std::invalid_argument&) {
        return std::unexpected(ParseError::InvalidFormat);
    }
}

int main() {
    auto result = parseInteger("42");
    
    if (result.has_value()) {
        cout << "Parsed value: " << result.value() << endl;
    } else {
        ParseError error = result.error();
        switch (error) {
            case ParseError::InvalidFormat:
                cout << "Error: Invalid format" << endl;
                break;
            case ParseError::ValueOutOfRange:
                cout << "Error: Value out of range" << endl;
                break;
            case ParseError::EmptyString:
                cout << "Error: Empty string" << endl;
                break;
        }
    }
    
    return 0;
}

#endif

// ============================================================================
// 15. std::expected Chaining Operations
// ============================================================================
#if 0

std::expected<int, std::string> safeDivide(int a, int b) {
    if (b == 0) {
        return std::unexpected("Division by zero");
    }
    return a / b;
}

std::expected<int, std::string> processData(int a, int b, int c) {
    // Chain operations - stops at first error
    return safeDivide(a, b)
        .and_then([c](int intermediate) {
            return safeDivide(intermediate, c);
        });
}

int main() {
    auto result = processData(10, 2, 0);
    
    if (result) {
        cout << "Result: " << result.value() << endl;
    } else {
        cout << "Error: " << result.error() << endl;  // "Division by zero"
    }
    
    return 0;
}

#endif

// ============================================================================
// 16. std::expected Real-World API Example
// ============================================================================
#if 0

enum class APIError {
    NetworkError,
    InvalidResponse,
    AuthenticationFailed,
    ServerError,
    NotFound
};

struct APIResponse {
    int statusCode;
    std::string body;
};

std::expected<APIResponse, APIError> fetchUserData(int userId, const std::string& token) {
    // Validate token
    if (token.empty()) {
        return std::unexpected(APIError::AuthenticationFailed);
    }
    
    // Simulate API call
    // ... network request code ...
    
    // Check response
    APIResponse response{200, R"({"id": 1, "name": "John"})"};
    
    if (response.statusCode >= 500) {
        return std::unexpected(APIError::ServerError);
    }
    if (response.statusCode == 404) {
        return std::unexpected(APIError::NotFound);
    }
    if (response.statusCode != 200) {
        return std::unexpected(APIError::InvalidResponse);
    }
    
    return response;
}

int main() {
    auto result = fetchUserData(123, "valid_token");
    
    result
        .and_then([](const APIResponse& response) -> std::expected<bool, APIError> {
            cout << "Response: " << response.body << endl;
            return true;
        })
        .or_else([](APIError error) -> std::expected<bool, APIError> {
            cout << "API Error: " << static_cast<int>(error) << endl;
            return std::unexpected(error);
        });
    
    return 0;
}

#endif

#endif // TEST_ERROR_HANDLING_H
