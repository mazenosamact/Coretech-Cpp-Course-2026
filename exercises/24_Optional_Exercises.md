# Optional Type - Practical Exercises

## Exercise 1: Optional Return Values (Safe Alternatives)
**Context:** Functions that might not find a result should return optional instead of throwing or using sentinel values.

**Problem:**
```cpp
// Implement optional results:
// 1. Return optional from search
// 2. Check if value exists
// 3. Get value with default
// 4. Chain operations
// 5. Error handling without exceptions
```

**Solution:**
```cpp
#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct User {
    int id;
    string name;
    string email;
    
    User(int i, const string &n, const string &e) 
        : id(i), name(n), email(e) {}
};

class UserDatabase {
private:
    vector<User> users = {
        User(1, "Alice", "alice@example.com"),
        User(2, "Bob", "bob@example.com"),
        User(3, "Charlie", "charlie@example.com")
    };
    
public:
    optional<User> findUserById(int id) {
        auto it = find_if(users.begin(), users.end(),
                         [id](const User &u) { return u.id == id; });
        
        if (it != users.end()) {
            return *it;
        }
        return nullopt;  // Return "nothing"
    }
    
    optional<User> findUserByName(const string &name) {
        auto it = find_if(users.begin(), users.end(),
                         [&name](const User &u) { return u.name == name; });
        
        if (it != users.end()) {
            return *it;
        }
        return nullopt;
    }
    
    optional<string> getEmail(int id) {
        auto user = findUserById(id);
        
        if (user) {
            return user->email;
        }
        return nullopt;
    }
};

int main() {
    cout << "=== Optional: Safe Return Values ===" << endl;
    
    UserDatabase db;
    
    cout << "\n--- Finding existing user ---" << endl;
    auto user = db.findUserById(1);
    
    if (user) {
        cout << "✓ Found user: " << user->name 
             << " (" << user->email << ")" << endl;
    } else {
        cout << "✗ User not found" << endl;
    }
    
    cout << "\n--- Finding non-existing user ---" << endl;
    auto missing = db.findUserById(999);
    
    if (missing) {
        cout << "✓ Found user: " << missing->name << endl;
    } else {
        cout << "✗ User not found" << endl;
    }
    
    cout << "\n--- Using value_or() ---" << endl;
    User default_user(0, "Unknown", "unknown@example.com");
    auto result = db.findUserById(2);
    User found = result.value_or(default_user);
    cout << "User: " << found.name << endl;
    
    cout << "\n--- Chaining optional operations ---" << endl;
    auto email = db.getEmail(2);
    if (email) {
        cout << "✓ Email for user 2: " << *email << endl;
    }
    
    auto invalid_email = db.getEmail(999);
    cout << "Email for user 999: " 
         << invalid_email.value_or("not found") << endl;
    
    cout << "\n✓ Optional operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Optional Configuration (Default Values)
**Context:** Configuration system with optional parameters.

**Problem:**
```cpp
// Create config with optionals:
// 1. Some settings are optional
// 2. Provide sensible defaults
// 3. Allow overriding defaults
// 4. Display actual values
// 5. Validate required fields
```

**Solution:**
```cpp
#include <iostream>
#include <optional>
#include <string>
using namespace std;

struct ServerConfig {
    string hostname;
    int port = 8080;
    optional<string> ssl_cert;
    optional<int> timeout;
    optional<int> max_connections;
    
    ServerConfig(const string &host) : hostname(host) {}
    
    void display() {
        cout << "Server Configuration:" << endl;
        cout << "  Hostname: " << hostname << endl;
        cout << "  Port: " << port << endl;
        
        cout << "  SSL Certificate: " 
             << (ssl_cert ? *ssl_cert : "Not configured") << endl;
        
        cout << "  Timeout: " 
             << (timeout ? to_string(*timeout) + "s" : "Default (30s)") << endl;
        
        cout << "  Max Connections: " 
             << (max_connections ? to_string(*max_connections) : "Unlimited") << endl;
    }
};

int main() {
    cout << "=== Optional: Configuration System ===" << endl;
    
    cout << "\n--- Default configuration ---" << endl;
    ServerConfig config1("localhost");
    config1.display();
    
    cout << "\n--- Custom configuration ---" << endl;
    ServerConfig config2("api.example.com");
    config2.port = 443;
    config2.ssl_cert = "/etc/ssl/certs/server.crt";
    config2.timeout = 60;
    config2.max_connections = 500;
    
    config2.display();
    
    cout << "\n--- Partial configuration ---" << endl;
    ServerConfig config3("internal.example.com");
    config3.timeout = 120;
    
    config3.display();
    
    cout << "\n✓ Configuration complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Optional Pointer Alternative (Nullable References)
**Context:** Function parameters that might be null.

**Problem:**
```cpp
// Use optional instead of pointers:
// 1. Function takes optional parameter
// 2. Safer than nullptr
// 3. More semantic meaning
// 4. Chaining operations
// 5. Type safety
```

**Solution:**
```cpp
#include <iostream>
#include <optional>
#include <string>
using namespace std;

struct Document {
    string title;
    int pages;
    
    Document(const string &t, int p) : title(t), pages(p) {}
};

class DocumentProcessor {
public:
    void process(const optional<Document> &doc) {
        if (!doc) {
            cout << "✗ No document to process" << endl;
            return;
        }
        
        cout << "✓ Processing document: " << doc->title 
             << " (" << doc->pages << " pages)" << endl;
    }
    
    optional<string> extractTitle(const optional<Document> &doc) {
        if (doc) {
            return doc->title;
        }
        return nullopt;
    }
    
    int countPages(const optional<Document> &doc) {
        return doc ? doc->pages : 0;
    }
};

int main() {
    cout << "=== Optional: Pointer Alternative ===" << endl;
    
    DocumentProcessor proc;
    
    cout << "\n--- Processing with valid document ---" << endl;
    Document doc("Report.pdf", 25);
    proc.process(doc);
    
    cout << "\n--- Processing without document ---" << endl;
    optional<Document> empty;
    proc.process(empty);
    
    cout << "\n--- Extracting title ---" << endl;
    auto title = proc.extractTitle(doc);
    if (title) {
        cout << "Title: " << *title << endl;
    }
    
    auto missing_title = proc.extractTitle(empty);
    cout << "Missing title: " << missing_title.value_or("<none>") << endl;
    
    cout << "\n--- Getting page counts ---" << endl;
    cout << "Document pages: " << proc.countPages(optional<Document>(doc)) << endl;
    cout << "Missing pages: " << proc.countPages(empty) << endl;
    
    cout << "\n✓ Optional usage complete" << endl;
    
    return 0;
}
```
