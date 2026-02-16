# Classes and OOP - Practical Exercises

## Exercise 1: GPIO Controller Class (Embedded Systems)
**Context:** Encapsulate GPIO pin control with proper OOP design.

**Problem:**
```cpp
// Create a GPIOPin class:
// 1. Private: port address, pin number, mode
// 2. Constructor: initialize pin with port and number
// 3. Public methods:
//    - setMode(INPUT/OUTPUT)
//    - digitalWrite(HIGH/LOW)
//    - digitalRead() -> bool
// 4. Destructor: clean up resources
// 5. Private helper: validatePin()
```

**Solution:**
```cpp
#include <iostream>
#include <cstdint>
using namespace std;

enum PinMode { INPUT = 0, OUTPUT = 1 };
enum PinState { LOW = 0, HIGH = 1 };

class GPIOPin {
private:
    uint32_t port_base;
    uint8_t pin_number;
    PinMode mode;
    uint32_t *gpio_register;
    
    void validatePin() {
        if (pin_number > 15) {
            cerr << "Invalid pin number: " << (int)pin_number << endl;
        }
    }
    
public:
    GPIOPin(uint32_t port, uint8_t pin) 
        : port_base(port), pin_number(pin), mode(INPUT) {
        validatePin();
        gpio_register = reinterpret_cast<uint32_t *>(port_base);
        cout << "✓ GPIO Pin " << (int)pin << " initialized on port 0x"
             << hex << port << dec << endl;
    }
    
    ~GPIOPin() {
        cout << "✓ GPIO Pin " << (int)pin_number << " cleaned up" << endl;
    }
    
    void setMode(PinMode new_mode) {
        mode = new_mode;
        cout << "Pin " << (int)pin_number << " mode set to "
             << (mode == OUTPUT ? "OUTPUT" : "INPUT") << endl;
    }
    
    void digitalWrite(PinState state) {
        if (mode != OUTPUT) {
            cerr << "Error: Pin is not configured as OUTPUT" << endl;
            return;
        }
        
        if (state == HIGH) {
            *gpio_register |= (1 << pin_number);
        } else {
            *gpio_register &= ~(1 << pin_number);
        }
        
        cout << "Pin " << (int)pin_number << " set to "
             << (state == HIGH ? "HIGH" : "LOW") << endl;
    }
    
    bool digitalRead() {
        if (mode != INPUT) {
            cerr << "Error: Pin is not configured as INPUT" << endl;
            return false;
        }
        
        bool state = (*gpio_register >> pin_number) & 1;
        cout << "Pin " << (int)pin_number << " read: "
             << (state ? "HIGH" : "LOW") << endl;
        return state;
    }
};

int main() {
    cout << "=== GPIO Controller Class ===" << endl;
    
    // Create GPIO objects
    uint32_t simulated_register = 0;
    GPIOPin led(&simulated_register, 5);
    GPIOPin button(&simulated_register, 3);
    
    cout << "\n--- Configure pins ---" << endl;
    led.setMode(OUTPUT);
    button.setMode(INPUT);
    
    cout << "\n--- Control LED ---" << endl;
    led.digitalWrite(HIGH);
    cout << "Register value: 0x" << hex << simulated_register << dec << endl;
    
    led.digitalWrite(LOW);
    cout << "Register value: 0x" << hex << simulated_register << dec << endl;
    
    cout << "\n✓ GPIO operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Stack Data Structure Class (Backend/Algorithms)
**Context:** Implement a generic stack with encapsulation and proper error handling.

**Problem:**
```cpp
// Create a Stack class:
// 1. Private: dynamic array, top pointer, size, capacity
// 2. Constructor: initialize with capacity
// 3. Public methods:
//    - push(value)
//    - pop() -> value
//    - peek() -> value
//    - isEmpty(), isFull()
//    - getSize()
// 4. Destructor: cleanup memory
// 5. Handle overflow/underflow
```

**Solution:**
```cpp
#include <iostream>
using namespace std;

class Stack {
private:
    int *data;
    int top;
    int capacity;
    
public:
    Stack(int initial_capacity = 10) 
        : top(-1), capacity(initial_capacity) {
        data = new int[capacity];
        cout << "✓ Stack created with capacity " << capacity << endl;
    }
    
    ~Stack() {
        delete[] data;
        cout << "✓ Stack destroyed" << endl;
    }
    
    void push(int value) {
        if (isFull()) {
            cerr << "Error: Stack overflow" << endl;
            return;
        }
        
        data[++top] = value;
        cout << "Pushed: " << value << endl;
    }
    
    int pop() {
        if (isEmpty()) {
            cerr << "Error: Stack underflow" << endl;
            return -1;
        }
        
        int value = data[top--];
        cout << "Popped: " << value << endl;
        return value;
    }
    
    int peek() {
        if (isEmpty()) {
            cerr << "Error: Stack is empty" << endl;
            return -1;
        }
        return data[top];
    }
    
    bool isEmpty() const {
        return top == -1;
    }
    
    bool isFull() const {
        return top == capacity - 1;
    }
    
    int getSize() const {
        return top + 1;
    }
};

int main() {
    cout << "=== Stack Implementation ===" << endl;
    
    Stack s(5);
    
    cout << "\n--- Push operations ---" << endl;
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);
    
    cout << "\nStack size: " << s.getSize() << endl;
    cout << "Top element: " << s.peek() << endl;
    
    cout << "\n--- Overflow test ---" << endl;
    s.push(60);  // Should fail
    
    cout << "\n--- Pop operations ---" << endl;
    s.pop();
    s.pop();
    s.pop();
    
    cout << "\nStack size: " << s.getSize() << endl;
    
    cout << "\n✓ Stack operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Device Manager with Encapsulation (System Programming)
**Context:** Multi-device manager tracking device state and operations.

**Problem:**
```cpp
// Create a DeviceManager class:
// 1. Private: array of devices, device count
// 2. Encapsule device details
// 3. Methods:
//    - registerDevice(id, name)
//    - getDevice(id)
//    - listDevices()
//    - removeDevice(id)
// 4. Proper constructor/destructor
// 5. Const correctness
```

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct Device {
    int id;
    char name[64];
    bool active;
};

class DeviceManager {
private:
    Device *devices;
    int device_count;
    int max_devices;
    
    bool findDeviceIndex(int id, int &index) const {
        for (int i = 0; i < device_count; i++) {
            if (devices[i].id == id) {
                index = i;
                return true;
            }
        }
        return false;
    }
    
public:
    DeviceManager(int capacity = 10) 
        : device_count(0), max_devices(capacity) {
        devices = new Device[max_devices];
        cout << "✓ DeviceManager created" << endl;
    }
    
    ~DeviceManager() {
        delete[] devices;
        cout << "✓ DeviceManager destroyed" << endl;
    }
    
    bool registerDevice(int id, const char *name) {
        if (device_count >= max_devices) {
            cerr << "Error: Max devices reached" << endl;
            return false;
        }
        
        devices[device_count].id = id;
        strcpy(devices[device_count].name, name);
        devices[device_count].active = true;
        
        cout << "✓ Device registered: " << name << " (ID: " << id << ")" << endl;
        device_count++;
        return true;
    }
    
    const Device *getDevice(int id) const {
        int index;
        if (findDeviceIndex(id, index)) {
            return &devices[index];
        }
        return nullptr;
    }
    
    void listDevices() const {
        cout << "\n=== Registered Devices ===" << endl;
        for (int i = 0; i < device_count; i++) {
            cout << "ID: " << devices[i].id
                 << " | Name: " << devices[i].name
                 << " | Status: " << (devices[i].active ? "Active" : "Inactive")
                 << endl;
        }
    }
    
    bool activateDevice(int id) {
        int index;
        if (findDeviceIndex(id, index)) {
            devices[index].active = true;
            cout << "✓ Device " << id << " activated" << endl;
            return true;
        }
        return false;
    }
    
    bool deactivateDevice(int id) {
        int index;
        if (findDeviceIndex(id, index)) {
            devices[index].active = false;
            cout << "✓ Device " << id << " deactivated" << endl;
            return true;
        }
        return false;
    }
    
    int getDeviceCount() const {
        return device_count;
    }
};

int main() {
    cout << "=== Device Manager System ===" << endl;
    
    DeviceManager manager(5);
    
    cout << "\n--- Register devices ---" << endl;
    manager.registerDevice(1, "Temperature Sensor");
    manager.registerDevice(2, "Humidity Sensor");
    manager.registerDevice(3, "LED Controller");
    manager.registerDevice(4, "Motor Driver");
    
    manager.listDevices();
    
    cout << "\n--- Device operations ---" << endl;
    manager.deactivateDevice(3);
    manager.activateDevice(3);
    
    const Device *led = manager.getDevice(3);
    if (led) {
        cout << "Found device: " << led->name << endl;
    }
    
    cout << "\nTotal devices: " << manager.getDeviceCount() << endl;
    
    return 0;
}
```
