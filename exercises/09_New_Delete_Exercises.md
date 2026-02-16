# new and delete vs malloc/free - Practical Exercises

## Exercise 1: Object Creation and Cleanup (Embedded Systems)
**Context:** Microcontroller application needs to dynamically create device objects.

**Problem:**
```cpp
// Compare new/delete vs malloc/free:
// 1. Create Device objects using both methods
// 2. Show differences in initialization
// 3. Demonstrate constructor/destructor calls
// 4. Memory management safety
```

**Solution:**
```cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class Device {
private:
    int id;
    char *name;
    
public:
    Device(int id_, const char *name_) : id(id_) {
        name = new char[strlen(name_) + 1];
        strcpy(name, name_);
        cout << "✓ Device constructor: " << name << endl;
    }
    
    ~Device() {
        cout << "✓ Device destructor: " << name << endl;
        delete[] name;
    }
    
    void printInfo() {
        cout << "  [Device ID: " << id << ", Name: " << name << "]" << endl;
    }
};

int main() {
    cout << "=== new/delete vs malloc/free ===" << endl;
    
    cout << "\n--- Using new/delete (with constructors) ---" << endl;
    Device *dev1 = new Device(1, "Temperature Sensor");
    Device *dev2 = new Device(2, "Humidity Sensor");
    
    dev1->printInfo();
    dev2->printInfo();
    
    cout << "\nDeleting objects (destructors called):" << endl;
    delete dev1;
    delete dev2;
    
    cout << "\n--- Using malloc/free (no constructors) ---" << endl;
    
    // This is NOT recommended for C++ objects:
    Device *dev3 = (Device *)malloc(sizeof(Device));
    // Constructor NOT called! Memory not initialized properly.
    
    cout << "malloc allocated memory, but constructor not called" << endl;
    cout << "⚠️  This is UNSAFE for C++ objects!" << endl;
    
    free(dev3);  // Destructor NOT called! Memory leaks possible.
    
    cout << "\n✓ new/delete is the proper C++ way" << endl;
    
    return 0;
}
```

---

## Exercise 2: Array Allocation with Constructors (Backend Systems)
**Context:** Application needs to allocate arrays of complex objects.

**Problem:**
```cpp
// Create and manage arrays:
// 1. Allocate array of objects with new[]
// 2. Show constructor called for each element
// 3. Access objects in array
// 4. Deallocate with delete[]
// 5. Compare with malloc array
```

**Solution:**
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class SensorData {
private:
    int id;
    float value;
    
public:
    SensorData() : id(0), value(0.0) {
        cout << "  SensorData constructor (default)" << endl;
    }
    
    SensorData(int id_, float val) : id(id_), value(val) {
        cout << "  SensorData constructor (id=" << id_ << ", val=" << val << ")" << endl;
    }
    
    ~SensorData() {
        cout << "  SensorData destructor (id=" << id_ << ")" << endl;
    }
    
    void print() {
        cout << "    Sensor " << id << ": " << value << endl;
    }
};

int main() {
    cout << "=== Array Allocation with new[] ===" << endl;
    
    const int ARRAY_SIZE = 3;
    
    cout << "\n--- Allocating array (calls default constructor) ---" << endl;
    SensorData *sensors = new SensorData[ARRAY_SIZE];
    
    cout << "\n--- Manually initializing elements ---" << endl;
    sensors[0] = SensorData(1, 22.5);
    sensors[1] = SensorData(2, 45.2);
    sensors[2] = SensorData(3, 101.3);
    
    cout << "\n--- Accessing array elements ---" << endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sensors[i].print();
    }
    
    cout << "\n--- Deallocating array (destructors called in reverse) ---" << endl;
    delete[] sensors;
    
    cout << "\n⚠️  Note: delete[] not delete[] will cause memory issues!" << endl;
    
    return 0;
}
```

---

## Exercise 3: Pointer Safety and Memory Management (Production Code)
**Context:** Real-world application with multiple allocations and deallocations.

**Problem:**
```cpp
// Create a resource manager:
// 1. Allocate multiple different-sized objects
// 2. Track allocations
// 3. Implement safe cleanup
// 4. Demonstrate memory safety
```

**Solution:**
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Resource {
private:
    char name[64];
    int size;
    
public:
    Resource(const char *n, int s) : size(s) {
        strcpy(name, n);
        cout << "✓ Allocated: " << name << " (" << size << " bytes)" << endl;
    }
    
    ~Resource() {
        cout << "✓ Released: " << name << endl;
    }
    
    void info() {
        cout << "  " << name << ": " << size << " bytes" << endl;
    }
};

class ResourceManager {
private:
    Resource **resources;
    int count;
    int max_count;
    
public:
    ResourceManager(int capacity = 10) : count(0), max_count(capacity) {
        resources = new Resource*[capacity];
        cout << "ResourceManager initialized" << endl;
    }
    
    ~ResourceManager() {
        cout << "\nCleaning up " << count << " resources:" << endl;
        for (int i = count - 1; i >= 0; i--) {
            delete resources[i];
        }
        delete[] resources;
        cout << "ResourceManager cleaned up" << endl;
    }
    
    void allocate(const char *name, int size) {
        if (count < max_count) {
            resources[count++] = new Resource(name, size);
        } else {
            cerr << "Cannot allocate more resources" << endl;
        }
    }
    
    void listResources() {
        cout << "\nAllocated resources: " << count << endl;
        for (int i = 0; i < count; i++) {
            resources[i]->info();
        }
    }
};

int main() {
    cout << "=== Safe Memory Management ===" << endl;
    
    ResourceManager manager;
    
    cout << "\n--- Allocating resources ---" << endl;
    manager.allocate("ConfigBuffer", 4096);
    manager.allocate("DataBuffer", 8192);
    manager.allocate("LogBuffer", 2048);
    manager.allocate("TempBuffer", 1024);
    
    manager.listResources();
    
    cout << "\n--- Automatic cleanup on exit ---" << endl;
    
    return 0;
}
```
