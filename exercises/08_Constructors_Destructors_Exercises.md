# Constructors and Destructors - Practical Exercises

## Exercise 1: Resource Management with RAII (Embedded Systems)
**Context:** A hardware resource (like a file, network socket, and GPIO) requires proper initialization and cleanup.

**Problem:**
```cpp
// Create a FileHandler class:
// 1. Constructor: opens a file (simulated)
// 2. Destructor: closes the file
// 3. Write/Read operations
// 4. Track resource state
// 5. Demonstrate RAII principle
```

**Solution:**
```cpp
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class FileHandler {
private:
    ofstream file;
    bool is_open;
    char filename[256];
    
public:
    FileHandler(const char *fname) : is_open(false) {
        strcpy(filename, fname);
        file.open(fname, ios::app);
        if (file.is_open()) {
            is_open = true;
            cout << "✓ File opened: " << fname << endl;
        } else {
            cerr << "✗ Failed to open file: " << fname << endl;
        }
    }
    
    ~FileHandler() {
        if (is_open) {
            file.close();
            cout << "✓ File closed: " << filename << endl;
        }
    }
    
    bool write(const char *data) {
        if (!is_open) {
            cerr << "Error: File not open" << endl;
            return false;
        }
        file << data << endl;
        return true;
    }
    
    bool isOpen() const {
        return is_open;
    }
};

int main() {
    cout << "=== RAII: Resource Acquisition Is Initialization ===" << endl;
    
    {
        FileHandler log("output.log");
        
        if (log.isOpen()) {
            cout << "Writing to file..." << endl;
            log.write("Log entry 1: System started");
            log.write("Log entry 2: Processing data");
            log.write("Log entry 3: Operation complete");
        }
        
        cout << "Leaving scope..." << endl;
    }  // Destructor called automatically here
    
    cout << "\n✓ Automatic cleanup completed" << endl;
    
    return 0;
}
```

---

## Exercise 2: Multiple Constructors and Initialization (OOP Design)
**Context:** Create a vector class with multiple ways to initialize.

**Problem:**
```cpp
// Vector3D class:
// 1. Default constructor: (0,0,0)
// 2. Parameterized constructor: (x,y,z)
// 3. Copy constructor: copy from another vector
// 4. Methods: magnitude, print
// 5. Show initialization order
```

**Solution:**
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Vector3D {
private:
    float x, y, z;
    
public:
    // Default constructor
    Vector3D() : x(0), y(0), z(0) {
        cout << "Default constructor called" << endl;
    }
    
    // Parameterized constructor
    Vector3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {
        cout << "Parameterized constructor called" << endl;
    }
    
    // Copy constructor
    Vector3D(const Vector3D &v) : x(v.x), y(v.y), z(v.z) {
        cout << "Copy constructor called" << endl;
    }
    
    // Destructor
    ~Vector3D() {
        // cout << "Destructor called" << endl;
    }
    
    float magnitude() const {
        return sqrt(x*x + y*y + z*z);
    }
    
    void print() const {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }
};

int main() {
    cout << "=== Multiple Constructors ===" << endl;
    
    cout << "\n--- Default constructor ---" << endl;
    Vector3D v1;
    
    cout << "\n--- Parameterized constructor ---" << endl;
    Vector3D v2(3, 4, 0);
    
    cout << "\n--- Copy constructor ---" << endl;
    Vector3D v3 = v2;
    
    cout << "\n--- Vector values ---" << endl;
    cout << "v1: ";
    v1.print();
    cout << " | Magnitude: " << v1.magnitude() << endl;
    
    cout << "v2: ";
    v2.print();
    cout << " | Magnitude: " << v2.magnitude() << endl;
    
    cout << "v3: ";
    v3.print();
    cout << " | Magnitude: " << v3.magnitude() << endl;
    
    return 0;
}
```

---

## Exercise 3: Destructor Chain and Memory Cleanup (System Design)
**Context:** Complex system with nested objects that need proper cleanup sequence.

**Problem:**
```cpp
// Create a Device system:
// 1. Device class: name, id, status
// 2. DeviceRegistry class: manages multiple devices
// 3. Track construction and destruction order
// 4. Show destructor calling sequence
```

**Solution:**
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Device {
private:
    int id;
    char name[64];
    
public:
    Device(int id_, const char *name_) : id(id_) {
        strcpy(name, name_);
        cout << "  → Device constructor: " << name << " (ID: " << id << ")" << endl;
    }
    
    ~Device() {
        cout << "  ← Device destructor: " << name << " (ID: " << id << ")" << endl;
    }
    
    const char *getName() const {
        return name;
    }
};

class DeviceRegistry {
private:
    Device **devices;
    int count;
    int max_devices;
    
public:
    DeviceRegistry(int capacity = 10) : count(0), max_devices(capacity) {
        devices = new Device*[capacity];
        cout << "Registry constructor called" << endl;
    }
    
    ~DeviceRegistry() {
        cout << "Registry destructor: cleaning up " << count << " devices" << endl;
        for (int i = count - 1; i >= 0; i--) {
            delete devices[i];
        }
        delete[] devices;
        cout << "Registry destructor complete" << endl;
    }
    
    void addDevice(int id, const char *name) {
        if (count < max_devices) {
            devices[count++] = new Device(id, name);
        }
    }
    
    void listDevices() const {
        cout << "Registered devices: " << count << endl;
        for (int i = 0; i < count; i++) {
            cout << "  - " << devices[i]->getName() << endl;
        }
    }
};

int main() {
    cout << "=== Destructor Chain and Cleanup ===" << endl;
    
    cout << "\n--- Creating registry ---" << endl;
    DeviceRegistry *registry = new DeviceRegistry();
    
    cout << "\n--- Adding devices ---" << endl;
    registry->addDevice(1, "Temperature Sensor");
    registry->addDevice(2, "Humidity Sensor");
    registry->addDevice(3, "LED Controller");
    
    registry->listDevices();
    
    cout << "\n--- Deleting registry (triggers device cleanup) ---" << endl;
    delete registry;
    
    cout << "\n✓ All objects cleaned up in reverse order" << endl;
    
    return 0;
}
```
