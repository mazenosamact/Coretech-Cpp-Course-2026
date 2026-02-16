# Enums - Practical Exercises

## Exercise 1: LED and Motor Control State Machine (Embedded Systems)
**Context:** Industrial controller needs to track device states and transitions.

**Problem:**
```cpp
// Different device states:
// - IDLE: Device powered on but inactive
// - RUNNING: Device actively operating
// - ERROR: Fault detected
// - MAINTENANCE: Service mode
// - SHUTDOWN: Powering down
//
// Tasks:
// 1. Create enum for device states
// 2. Implement state transition logic
// 3. Create functions to handle each state
// 4. Detect invalid state transitions
// 5. Log state changes
```

**Solution:**
```cpp
#include <iostream>
#include <ctime>
using namespace std;

enum DeviceState {
    IDLE = 0,
    RUNNING = 1,
    ERROR = 2,
    MAINTENANCE = 3,
    SHUTDOWN = 4
};

const char *state_names[] = {
    "IDLE", "RUNNING", "ERROR", "MAINTENANCE", "SHUTDOWN"
};

class DeviceController {
private:
    DeviceState current_state;
    
public:
    DeviceController() : current_state(IDLE) {}
    
    bool transitionTo(DeviceState new_state) {
        // Define valid transitions
        bool valid = false;
        
        switch (current_state) {
            case IDLE:
                valid = (new_state == RUNNING || new_state == SHUTDOWN);
                break;
            case RUNNING:
                valid = (new_state == IDLE || new_state == ERROR || 
                        new_state == MAINTENANCE || new_state == SHUTDOWN);
                break;
            case ERROR:
                valid = (new_state == MAINTENANCE || new_state == SHUTDOWN);
                break;
            case MAINTENANCE:
                valid = (new_state == IDLE || new_state == SHUTDOWN);
                break;
            case SHUTDOWN:
                valid = (new_state == IDLE);
                break;
        }
        
        if (valid) {
            cout << "[" << time(nullptr) << "] Transition: " 
                 << state_names[current_state] << " -> " 
                 << state_names[new_state] << endl;
            current_state = new_state;
            handleState(new_state);
            return true;
        } else {
            cout << "✗ Invalid transition from " 
                 << state_names[current_state] << " to "
                 << state_names[new_state] << endl;
            return false;
        }
    }
    
    void handleState(DeviceState state) {
        switch (state) {
            case IDLE:
                cout << "  → Waiting for command" << endl;
                break;
            case RUNNING:
                cout << "  → Motor running, monitoring sensors" << endl;
                break;
            case ERROR:
                cout << "  → ALARM: Emergency stop activated" << endl;
                break;
            case MAINTENANCE:
                cout << "  → Service mode: Manual control enabled" << endl;
                break;
            case SHUTDOWN:
                cout << "  → Powering down..." << endl;
                break;
        }
    }
    
    DeviceState getState() const {
        return current_state;
    }
};

int main() {
    cout << "=== Device State Machine ===" << endl;
    
    DeviceController device;
    
    cout << "Initial state: " << state_names[device.getState()] << endl;
    
    cout << "\n--- Valid Transitions ---" << endl;
    device.transitionTo(RUNNING);
    device.transitionTo(MAINTENANCE);
    device.transitionTo(IDLE);
    
    cout << "\n--- Invalid Transition Attempt ---" << endl;
    device.transitionTo(RUNNING);
    device.transitionTo(SHUTDOWN);
    device.transitionTo(RUNNING);  // Invalid!
    
    cout << "\n✓ State machine working correctly" << endl;
    
    return 0;
}
```

---

## Exercise 2: HTTP Status Code Handling (Backend Development)
**Context:** Web server needs to return appropriate HTTP status codes.

**Problem:**
```cpp
// HTTP Status codes:
// 200-299: Success (OK=200, CREATED=201, ACCEPTED=202)
// 300-399: Redirect (MOVED=301, FOUND=302, NOT_MODIFIED=304)
// 400-499: Client Error (BAD_REQUEST=400, UNAUTHORIZED=401, FORBIDDEN=403, NOT_FOUND=404)
// 500-599: Server Error (INTERNAL_ERROR=500, NOT_IMPLEMENTED=501, SERVICE_UNAVAILABLE=503)
//
// Tasks:
// 1. Create enums for status code categories
// 2. Implement function to check if response is successful
// 3. Create message lookup function
// 4. Log status codes to file (simulated)
```

**Solution:**
```cpp
#include <iostream>
#include <fstream>
using namespace std;

enum HTTPStatusCode {
    // Success
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    
    // Redirect
    MOVED_PERMANENTLY = 301,
    FOUND = 302,
    NOT_MODIFIED = 304,
    
    // Client Error
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    CONFLICT = 409,
    
    // Server Error
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    SERVICE_UNAVAILABLE = 503
};

const char *getStatusMessage(HTTPStatusCode code) {
    switch (code) {
        case OK: return "200 OK";
        case CREATED: return "201 Created";
        case ACCEPTED: return "202 Accepted";
        case MOVED_PERMANENTLY: return "301 Moved Permanently";
        case FOUND: return "302 Found";
        case NOT_MODIFIED: return "304 Not Modified";
        case BAD_REQUEST: return "400 Bad Request";
        case UNAUTHORIZED: return "401 Unauthorized";
        case FORBIDDEN: return "403 Forbidden";
        case NOT_FOUND: return "404 Not Found";
        case CONFLICT: return "409 Conflict";
        case INTERNAL_SERVER_ERROR: return "500 Internal Server Error";
        case NOT_IMPLEMENTED: return "501 Not Implemented";
        case SERVICE_UNAVAILABLE: return "503 Service Unavailable";
        default: return "Unknown Status";
    }
}

bool isSuccessCode(HTTPStatusCode code) {
    return code >= 200 && code < 300;
}

bool isErrorCode(HTTPStatusCode code) {
    return code >= 400;
}

bool isClientError(HTTPStatusCode code) {
    return code >= 400 && code < 500;
}

bool isServerError(HTTPStatusCode code) {
    return code >= 500;
}

void logRequest(const char *method, const char *path, HTTPStatusCode code, 
                const char *client_ip) {
    cout << client_ip << " [" << getStatusMessage(code) << "] "
         << method << " " << path << endl;
}

int main() {
    cout << "=== HTTP Status Code Handling ===" << endl;
    
    cout << "\n--- Simulating Web Server Requests ---" << endl;
    
    // Successful requests
    logRequest("GET", "/api/data", OK, "192.168.1.100");
    logRequest("POST", "/api/users", CREATED, "192.168.1.101");
    
    // Client errors
    logRequest("GET", "/nonexistent", NOT_FOUND, "192.168.1.102");
    logRequest("POST", "/api/admin", UNAUTHORIZED, "192.168.1.103");
    logRequest("DELETE", "/protected", FORBIDDEN, "192.168.1.104");
    
    // Server error
    logRequest("GET", "/api/process", INTERNAL_SERVER_ERROR, "192.168.1.105");
    
    cout << "\n--- Status Analysis ---" << endl;
    HTTPStatusCode codes[] = {OK, NOT_FOUND, UNAUTHORIZED, INTERNAL_SERVER_ERROR};
    
    for (HTTPStatusCode code : codes) {
        cout << "Code " << code << ": ";
        if (isSuccessCode(code)) cout << "SUCCESS";
        else if (isClientError(code)) cout << "CLIENT ERROR";
        else if (isServerError(code)) cout << "SERVER ERROR";
        cout << " - " << getStatusMessage(code) << endl;
    }
    
    cout << "\n✓ HTTP status handling complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: System Log Severity Levels (System Administration)
**Context:** Logging system needs to categorize and filter messages by severity.

**Problem:**
```cpp
// Log levels:
// DEBUG (0): Detailed diagnostic information
// INFO (1): Informational messages
// WARNING (2): Warning conditions
// ERROR (3): Error conditions
// CRITICAL (4): Critical conditions requiring immediate action
//
// Tasks:
// 1. Create enum for log levels
// 2. Create logging function with filtering
// 3. Implement log filtering by minimum level
// 4. Demonstrate filtering at WARNING level
```

**Solution:**
```cpp
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

enum LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    CRITICAL = 4
};

const char *level_names[] = {
    "DEBUG", "INFO", "WARN", "ERROR", "CRIT"
};

const char *level_colors[] = {
    "\033[36m",    // Cyan for DEBUG
    "\033[32m",    // Green for INFO
    "\033[33m",    // Yellow for WARNING
    "\033[31m",    // Red for ERROR
    "\033[41m"     // Red background for CRITICAL
};
const char *color_reset = "\033[0m";

class Logger {
private:
    LogLevel min_level;
    
public:
    Logger(LogLevel level = DEBUG) : min_level(level) {}
    
    void setMinLevel(LogLevel level) {
        min_level = level;
    }
    
    void log(LogLevel level, const char *message) {
        if (level < min_level) {
            return;  // Skip logging if below threshold
        }
        
        time_t now = time(nullptr);
        struct tm *timeinfo = localtime(&now);
        
        cout << level_colors[level]
             << "[" << setfill('0') << setw(2) << timeinfo->tm_hour << ":"
             << setfill('0') << setw(2) << timeinfo->tm_min << ":"
             << setfill('0') << setw(2) << timeinfo->tm_sec << "] "
             << setfill(' ')
             << "[" << level_names[level] << "] "
             << message
             << color_reset << endl;
    }
};

int main() {
    cout << "=== System Logging with Severity Levels ===" << endl;
    
    Logger logger(INFO);  // Only INFO and above
    
    cout << "\n--- Logging all messages (threshold: INFO) ---" << endl;
    logger.log(DEBUG, "Application initialized");
    logger.log(INFO, "Server started on port 8080");
    logger.log(WARNING, "Memory usage at 85%");
    logger.log(ERROR, "Failed to connect to database");
    logger.log(CRITICAL, "SECURITY BREACH DETECTED!");
    
    cout << "\n--- Changing threshold to WARNING ---" << endl;
    logger.setMinLevel(WARNING);
    
    cout << "\n--- Logging with new threshold ---" << endl;
    logger.log(DEBUG, "This will not appear");
    logger.log(INFO, "This will not appear");
    logger.log(WARNING, "Disk usage at 90%");
    logger.log(ERROR, "Configuration file not found");
    logger.log(CRITICAL, "System shutdown initiated!");
    
    cout << "\n✓ Logging system working correctly" << endl;
    
    return 0;
}
```
