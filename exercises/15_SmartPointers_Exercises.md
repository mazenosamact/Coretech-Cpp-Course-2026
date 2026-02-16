# Smart Pointers - Practical Exercises

## Exercise 1: Unique Ownership (Resource Management)
**Context:** Embedded system with exclusive resource ownership.

**Problem:**
```cpp
// Create device controller:
// 1. Use unique_ptr for exclusive ownership
// 2. Implement move semantics
// 3. Show automatic cleanup
// 4. Prevent copying
```

**Solution:**
```cpp
#include <iostream>
#include <memory>
using namespace std;

class SerialPort {
private:
    int port_number;
    
public:
    SerialPort(int port) : port_number(port) {
        cout << "✓ SerialPort " << port << " opened" << endl;
    }
    
    ~SerialPort() {
        cout << "✓ SerialPort " << port_number << " closed" << endl;
    }
    
    void send(const char *data) {
        cout << "Sending on port " << port_number << ": " << data << endl;
    }
};

class Device {
private:
    unique_ptr<SerialPort> port;
    string name;
    
public:
    Device(const string &n) : name(n) {
        port = make_unique<SerialPort>(1);
        cout << "Device " << name << " created" << endl;
    }
    
    ~Device() {
        cout << "Device " << name << " destroyed" << endl;
    }
    
    void communicate(const char *msg) {
        if (port) {
            port->send(msg);
        }
    }
    
    // Move constructor
    Device(Device &&other) : port(move(other.port)), name(move(other.name)) {
        cout << "Device move constructor" << endl;
    }
    
    // Delete copy constructor
    Device(const Device &) = delete;
};

int main() {
    cout << "=== unique_ptr: Exclusive Ownership ===" << endl;
    
    {
        cout << "\n--- Creating device ---" << endl;
        Device dev("Sensor1");
        dev.communicate("Read temperature");
        
        cout << "\n--- Moving ownership ---" << endl;
        Device dev2 = move(dev);
        dev2.communicate("Configuration request");
        
        cout << "\n--- Leaving scope ---" << endl;
    }
    
    cout << "\n✓ Resources cleaned up automatically" << endl;
    
    return 0;
}
```

---

## Exercise 2: Shared Ownership (Reference Counting)
**Context:** Multiple objects need to share ownership of a resource.

**Problem:**
```cpp
// Create sensor network:
// 1. Multiple controllers share one sensor
// 2. Use shared_ptr for reference counting
// 3. Show automatic cleanup when last owner drops
// 4. Track reference count
```

**Solution:**
```cpp
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Sensor {
private:
    int sensor_id;
    float last_reading;
    
public:
    Sensor(int id) : sensor_id(id), last_reading(0.0) {
        cout << "✓ Sensor " << sensor_id << " created" << endl;
    }
    
    ~Sensor() {
        cout << "✓ Sensor " << sensor_id << " destroyed" << endl;
    }
    
    void takeMeasurement(float value) {
        last_reading = value;
        cout << "Sensor " << sensor_id << " reading: " << value << endl;
    }
    
    float getReading() const {
        return last_reading;
    }
};

class Controller {
private:
    shared_ptr<Sensor> sensor;
    string name;
    
public:
    Controller(const string &n, shared_ptr<Sensor> s) 
        : sensor(s), name(n) {
        cout << "Controller " << name << " created" << endl;
    }
    
    ~Controller() {
        cout << "Controller " << name << " destroyed" << endl;
    }
    
    void update() {
        if (sensor) {
            cout << name << " reading from sensor: " << sensor->getReading() << endl;
        }
    }
    
    long getRefCount() {
        return sensor.use_count();
    }
};

int main() {
    cout << "=== shared_ptr: Shared Ownership ===" << endl;
    
    cout << "\n--- Creating sensor ---" << endl;
    auto temp_sensor = make_shared<Sensor>(1);
    cout << "Reference count: " << temp_sensor.use_count() << endl;
    
    {
        cout << "\n--- Creating controllers sharing same sensor ---" << endl;
        Controller ctrl1("Monitor1", temp_sensor);
        cout << "Reference count: " << temp_sensor.use_count() << endl;
        
        Controller ctrl2("Monitor2", temp_sensor);
        cout << "Reference count: " << temp_sensor.use_count() << endl;
        
        temp_sensor->takeMeasurement(22.5);
        ctrl1.update();
        ctrl2.update();
        
        cout << "\n--- First controller destroyed ---" << endl;
    }
    
    cout << "Reference count: " << temp_sensor.use_count() << endl;
    
    cout << "\n✓ Sensor cleaned up when all owners destroyed" << endl;
    
    return 0;
}
```

---

## Exercise 3: Preventing Memory Leaks (Circular References)
**Context:** Detect and fix circular reference issues.

**Problem:**
```cpp
// Create parent-child relationship:
// 1. Show circular reference leak with shared_ptr
// 2. Fix with weak_ptr
// 3. Track object lifecycle
// 4. Demonstrate proper cleanup
```

**Solution:**
```cpp
#include <iostream>
#include <memory>
using namespace std;

// Forward declaration
class Child;

class Parent {
private:
    string name;
    shared_ptr<Child> child;
    
public:
    Parent(const string &n) : name(n) {
        cout << "Parent " << name << " created" << endl;
    }
    
    ~Parent() {
        cout << "Parent " << name << " destroyed" << endl;
    }
    
    void setChild(shared_ptr<Child> c) {
        child = c;
    }
};

class Child {
private:
    string name;
    weak_ptr<Parent> parent;  // Use weak_ptr to avoid circular reference
    
public:
    Child(const string &n) : name(n) {
        cout << "Child " << name << " created" << endl;
    }
    
    ~Child() {
        cout << "Child " << name << " destroyed" << endl;
    }
    
    void setParent(shared_ptr<Parent> p) {
        parent = p;
    }
    
    void printParent() {
        if (auto p = parent.lock()) {
            cout << "Child " << name << " has parent" << endl;
        } else {
            cout << "Child " << name << " parent is gone" << endl;
        }
    }
};

int main() {
    cout << "=== Preventing Circular References ===" << endl;
    
    cout << "\n--- Creating parent-child relationship ---" << endl;
    {
        auto parent = make_shared<Parent>("Alice");
        auto child = make_shared<Child>("Bob");
        
        parent->setChild(child);
        child->setParent(parent);
        
        cout << "Parent refcount: " << parent.use_count() << endl;
        cout << "Child refcount: " << child.use_count() << endl;
        
        child->printParent();
        
        cout << "\n--- Exiting scope ---" << endl;
    }
    
    cout << "\n✓ No memory leak! weak_ptr prevented circular reference" << endl;
    
    return 0;
}
```
