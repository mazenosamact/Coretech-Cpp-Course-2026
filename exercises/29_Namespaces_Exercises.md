# Namespaces - Practical Exercises

## Exercise 1: Basic Namespace Organization (Avoiding Collisions)
**Context:** Organize code into logical namespaces to prevent naming conflicts.

**Problem:**
```cpp
// Use namespaces for:
// 1. Avoid naming conflicts
// 2. Organize by functionality
// 3. Clear code structure
// 4. Libraries and APIs
// 5. Version isolation
```

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

// Problems solved by namespaces:
// Without namespaces, both Log classes would conflict

namespace Logging {
    class Logger {
    public:
        void log(const string &msg) {
            cout << "[LOG] " << msg << endl;
        }
    };
    
    const string APP_NAME = "MyApp";
}

namespace Database {
    class Logger {  // Different Logger - no conflict!
    public:
        void log(const string &msg) {
            cout << "[DB] " << msg << endl;
        }
    };
    
    const string APP_NAME = "DatabaseService";
}

namespace Network {
    class Logger {  // Yet another Logger - still no conflict
    public:
        void log(const string &msg) {
            cout << "[NET] " << msg << endl;
        }
    };
}

// Global namespace
class Logger {  // Even a global one
public:
    void log(const string &msg) {
        cout << "[GLOBAL] " << msg << endl;
    }
};

int main() {
    cout << "=== Namespaces: Code Organization ===" << endl;
    
    cout << "\n--- Using different Logger classes ---" << endl;
    Logging::Logger app_logger;
    Database::Logger db_logger;
    Network::Logger net_logger;
    Logger global_logger;
    
    cout << "App name: " << Logging::APP_NAME << endl;
    cout << "DB name: " << Database::APP_NAME << endl;
    
    cout << "\nLogging from different modules:" << endl;
    app_logger.log("Application started");
    db_logger.log("Connected to database");
    net_logger.log("Server listening on port 8080");
    global_logger.log("System event");
    
    cout << "\n--- Using declaration (import into current scope) ---" << endl;
    using namespace Logging;
    Logger app2;
    app2.log("Using declaration makes Logger refer to Logging::Logger");
    
    cout << "\n✓ Namespace organization complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Nested Namespaces (Hierarchical Organization)
**Context:** Organize large projects with nested namespace hierarchies.

**Problem:**
```cpp
// Nested namespaces:
// 1. Project-level organization
// 2. Feature separation
// 3. Version management
// 4. Reduce collision risk
// 5. Logical grouping
```

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

namespace MyCompany {
    namespace Backend {
        namespace Database {
            class Connection {
            public:
                void connect(const string &host) {
                    cout << "✓ Connecting to " << host << endl;
                }
            };
        }
        
        namespace API {
            class Server {
            public:
                void start() {
                    cout << "✓ API Server started" << endl;
                }
            };
        }
    }
    
    namespace Frontend {
        class UI {
        public:
            void render() {
                cout << "✓ Rendering UI" << endl;
            }
        };
    }
}

// Alternative: inline namespace (flatten hierarchy in some contexts)
namespace v1 {
    class Service {};
}

namespace v2 {
    class Service {};  // Different Service class
};

int main() {
    cout << "=== Namespaces: Nested Hierarchies ===" << endl;
    
    cout << "\n--- Using nested namespaces ---" << endl;
    MyCompany::Backend::Database::Connection db;
    db.connect("db.example.com");
    
    MyCompany::Backend::API::Server server;
    server.start();
    
    MyCompany::Frontend::UI ui;
    ui.render();
    
    cout << "\n--- Using namespace aliases ---" << endl;
    namespace DB = MyCompany::Backend::Database;
    namespace API = MyCompany::Backend::API;
    
    DB::Connection db2;
    db2.connect("backup.example.com");
    
    cout << "\n--- Version management ---" << endl;
    cout << "v1 Service available" << endl;
    cout << "v2 Service available" << endl;
    
    cout << "\n✓ Nested namespaces complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Namespace Aliases and Scope (Advanced Usage)
**Context:** Manage complex namespace usage patterns.

**Problem:**
```cpp
// Advanced namespace usage:
// 1. Namespace aliases
// 2. Selective imports (using declarations)
// 3. Argument-dependent lookup (ADL)
// 4. Namespace resolution operator
// 5. Best practices
```

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

namespace Company {
    namespace Product {
        namespace Version {
            class Handler {
            public:
                void process() {
                    cout << "Processing with Handler" << endl;
                }
            };
        }
    }
}

namespace CP = Company::Product;
namespace CPV = Company::Product::Version;

// Demonstrate ADL
namespace FileSystem {
    class File {};
    
    void save(const File &f) {
        cout << "SaveFile::save called (via ADL)" << endl;
    }
}

int main() {
    cout << "=== Namespaces: Advanced Usage ===" << endl;
    
    cout << "\n--- Namespace aliases ---" << endl;
    CPV::Handler handler1;
    handler1.process();
    
    cout << "\n--- Comparing alias vs full path ---" << endl;
    // Using alias
    CPV::Handler handler2;
    
    // Using full path
    Company::Product::Version::Handler handler3;
    
    cout << "Both handlers ready" << endl;
    
    cout << "\n--- Using declarations (selective imports) ---" << endl;
    {
        using CPV::Handler;  // Only Handler is imported
        Handler h;
        h.process();
    }
    
    cout << "\n--- Argument-dependent lookup (ADL) ---" << endl;
    FileSystem::File f;
    save(f);  // Finds FileSystem::save due to ADL
    
    cout << "\n--- Scope control ---" << endl;
    {
        using namespace Company::Product;
        // Version::Handler is now accessible
    }
    // Outside the block, Version::Handler requires full qualification
    
    cout << "\n✓ Advanced namespace usage complete" << endl;
    
    return 0;
}
```
