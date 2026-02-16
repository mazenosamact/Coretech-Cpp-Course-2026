# Unions - Practical Exercises

## Exercise 1: Hardware Register View (Embedded Systems - Baremetal)
**Context:** In embedded systems, a single register often contains multiple fields that need to be accessed either as a whole or individually (e.g., control registers).

**Problem:**
```cpp
// An 8-bit control register has:
// Bits 7-6: Mode (00=idle, 01=run, 10=test, 11=error)
// Bits 5-3: Channel (0-7)
// Bits 2-1: Speed (00=slow, 01=normal, 10=fast, 11=max)
// Bit 0: Enable flag
//
// Tasks:
// 1. Create a union to access as both full byte and bit fields
// 2. Set mode to "run" and enable the device
// 3. Read individual fields from a raw register value
// 4. Compare union vs bit-shifting approach
```

**Solution:**
```cpp
#include <iostream>
#include <cstdint>
#include <iomanip>
using namespace std;

// Using struct with bitfields inside union
struct ControlFieldsStruct {
    uint8_t enable : 1;      // Bit 0
    uint8_t speed : 2;       // Bits 2-1
    uint8_t channel : 3;     // Bits 5-3
    uint8_t mode : 2;        // Bits 7-6
};

union ControlRegister {
    uint8_t raw_value;
    ControlFieldsStruct fields;
};

void printRegisterState(const ControlRegister &reg) {
    cout << "Register Value: 0x" << hex << (int)reg.raw_value << dec << endl;
    cout << "  Mode: " << (int)reg.fields.mode 
         << " (0=idle, 1=run, 2=test, 3=error)" << endl;
    cout << "  Channel: " << (int)reg.fields.channel << endl;
    cout << "  Speed: " << (int)reg.fields.speed 
         << " (0=slow, 1=normal, 2=fast, 3=max)" << endl;
    cout << "  Enable: " << (int)reg.fields.enable << endl;
}

int main() {
    ControlRegister ctrl = {};
    
    cout << "=== Hardware Register Control ===" << endl;
    
    // Task 2: Set mode to "run" (01) and enable
    ctrl.fields.mode = 1;      // Run mode
    ctrl.fields.channel = 5;   // Channel 5
    ctrl.fields.speed = 2;     // Fast
    ctrl.fields.enable = 1;    // Enabled
    
    cout << "\nAfter configuration:" << endl;
    printRegisterState(ctrl);
    
    // Task 3: Read from raw register value
    cout << "\n--- Reading from hardware (simulated) ---" << endl;
    ControlRegister hw_reg;
    hw_reg.raw_value = 0b11101101;  // Simulated register value
    
    cout << "\nHardware register state:" << endl;
    printRegisterState(hw_reg);
    
    // Task 4: Compare with bit-shifting approach
    cout << "\n--- Comparison: Bit-shifting approach ---" << endl;
    uint8_t raw = 0b11101101;
    
    uint8_t shift_mode = (raw >> 6) & 0x3;
    uint8_t shift_channel = (raw >> 3) & 0x7;
    uint8_t shift_speed = (raw >> 1) & 0x3;
    uint8_t shift_enable = raw & 0x1;
    
    cout << "Mode: " << (int)shift_mode << endl;
    cout << "Channel: " << (int)shift_channel << endl;
    cout << "Speed: " << (int)shift_speed << endl;
    cout << "Enable: " << (int)shift_enable << endl;
    
    cout << "\n✓ Union approach is cleaner and less error-prone" << endl;
    cout << "Union size: " << sizeof(ControlRegister) << " bytes" << endl;
    
    return 0;
}
```

---

## Exercise 2: Network Frame Type Handling (Backend/Protocol Processing)
**Context:** Processing different types of network frames where the content varies based on type.

**Problem:**
```cpp
// Network frames can be:
// - IPv4 (contains src/dest IP addresses)
// - IPv6 (contains src/dest IPv6 addresses)
// - ARP (contains hardware and protocol addresses)
//
// Tasks:
// 1. Create a union to hold different frame types
// 2. Populate IPv4 and ARP frame types
// 3. Create a function that processes frames based on type
// 4. Show memory efficiency of using union
```

**Solution:**
```cpp
#include <iostream>
#include <cstdint>
#include <cstring>
using namespace std;

struct IPv4Frame {
    uint32_t src_ip;
    uint32_t dest_ip;
    uint16_t src_port;
    uint16_t dest_port;
};

struct ARPFrame {
    uint8_t hw_addr[6];   // Hardware address (MAC)
    uint8_t proto_addr[4]; // Protocol address (IP)
    uint8_t target_hw[6];
    uint8_t target_proto[4];
};

struct IPv6Frame {
    uint8_t src_ip[16];
    uint8_t dest_ip[16];
};

union NetworkFrame {
    IPv4Frame ipv4;
    IPv6Frame ipv6;
    ARPFrame arp;
};

struct FramePacket {
    uint8_t frame_type;  // 0=IPv4, 1=IPv6, 2=ARP
    NetworkFrame frame;
};

void processFrame(const FramePacket &pkt) {
    switch (pkt.frame_type) {
        case 0:  // IPv4
            cout << "IPv4 Frame Detected" << endl;
            cout << "  Source IP: " << ((pkt.frame.ipv4.src_ip >> 24) & 0xFF)
                 << "." << ((pkt.frame.ipv4.src_ip >> 16) & 0xFF)
                 << "." << ((pkt.frame.ipv4.src_ip >> 8) & 0xFF)
                 << "." << (pkt.frame.ipv4.src_ip & 0xFF) << endl;
            cout << "  Port: " << pkt.frame.ipv4.src_port << endl;
            break;
            
        case 1:  // IPv6
            cout << "IPv6 Frame Detected" << endl;
            cout << "  Source: IPv6 Address" << endl;
            break;
            
        case 2:  // ARP
            cout << "ARP Frame Detected" << endl;
            cout << "  Hardware Address: ";
            for (int i = 0; i < 6; i++) {
                printf("%02X", pkt.frame.arp.hw_addr[i]);
                if (i < 5) cout << ":";
            }
            cout << endl;
            break;
    }
}

int main() {
    cout << "=== Network Frame Type Handling ===" << endl;
    
    // Create IPv4 frame
    FramePacket ipv4_pkt;
    ipv4_pkt.frame_type = 0;
    ipv4_pkt.frame.ipv4.src_ip = 0xC0A80001;  // 192.168.0.1
    ipv4_pkt.frame.ipv4.dest_ip = 0x08080808; // 8.8.8.8
    ipv4_pkt.frame.ipv4.src_port = 5000;
    ipv4_pkt.frame.ipv4.dest_port = 80;
    
    // Create ARP frame
    FramePacket arp_pkt;
    arp_pkt.frame_type = 2;
    uint8_t mac[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    memcpy(arp_pkt.frame.arp.hw_addr, mac, 6);
    
    cout << "\n--- Frame 1 ---" << endl;
    processFrame(ipv4_pkt);
    
    cout << "\n--- Frame 2 ---" << endl;
    processFrame(arp_pkt);
    
    cout << "\n--- Memory Analysis ---" << endl;
    cout << "IPv4Frame size: " << sizeof(IPv4Frame) << " bytes" << endl;
    cout << "ARPFrame size: " << sizeof(ARPFrame) << " bytes" << endl;
    cout << "Union size: " << sizeof(NetworkFrame) << " bytes" << endl;
    cout << "Total packet size: " << sizeof(FramePacket) << " bytes" << endl;
    
    cout << "\n✓ Union saves memory by sharing space among frame types" << endl;
    
    return 0;
}
```

---

## Exercise 3: Sensor Data Type Conversion (Embedded IoT)
**Context:** Multiple sensors report different data types that need flexible storage.

**Problem:**
```cpp
// Sensors return data as:
// - Digital: boolean (on/off)
// - Analog: voltage (float)
// - Counter: pulse count (int)
// - String: status message
//
// Tasks:
// 1. Create a union to store different sensor types
// 2. Create sensor readings with different types
// 3. Display data based on sensor type
// 4. Demonstrate potential pitfalls of union misuse
```

**Solution:**
```cpp
#include <iostream>
#include <cstdint>
#include <cstring>
using namespace std;

union SensorData {
    bool digital;
    float analog;
    int32_t counter;
    char status[16];
};

struct SensorReading {
    int sensor_id;
    uint8_t data_type;  // 0=digital, 1=analog, 2=counter, 3=string
    SensorData data;
};

void displaySensorReading(const SensorReading &reading) {
    cout << "Sensor " << reading.sensor_id << ": ";
    
    switch (reading.data_type) {
        case 0:  // Digital
            cout << "Digital = " << (reading.data.digital ? "ON" : "OFF") << endl;
            break;
        case 1:  // Analog
            cout << "Voltage = " << reading.data.analog << "V" << endl;
            break;
        case 2:  // Counter
            cout << "Pulses = " << reading.data.counter << endl;
            break;
        case 3:  // String
            cout << "Status = " << reading.data.status << endl;
            break;
    }
}

int main() {
    cout << "=== Sensor Data Type Handling ===" << endl;
    
    // Create different sensor readings
    SensorReading motion_sensor;
    motion_sensor.sensor_id = 1;
    motion_sensor.data_type = 0;  // Digital
    motion_sensor.data.digital = true;
    
    SensorReading temperature_sensor;
    temperature_sensor.sensor_id = 2;
    temperature_sensor.data_type = 1;  // Analog
    temperature_sensor.data.analog = 3.3f;  // 3.3V
    
    SensorReading flow_meter;
    flow_meter.sensor_id = 3;
    flow_meter.data_type = 2;  // Counter
    flow_meter.data.counter = 12345;
    
    SensorReading status_sensor;
    status_sensor.sensor_id = 4;
    status_sensor.data_type = 3;  // String
    strcpy(status_sensor.data.status, "OPERATIONAL");
    
    cout << "\n--- Sensor Readings ---" << endl;
    displaySensorReading(motion_sensor);
    displaySensorReading(temperature_sensor);
    displaySensorReading(flow_meter);
    displaySensorReading(status_sensor);
    
    cout << "\n--- Memory Efficiency ---" << endl;
    cout << "If using separate variables: " << endl;
    cout << "  bool (1) + float (4) + int (4) + string[16] (16) = 25 bytes" << endl;
    cout << "Using union: " << sizeof(SensorData) << " bytes" << endl;
    
    cout << "\n⚠️  WARNING: Be careful not to mix data types!" << endl;
    cout << "Reading wrong type can give garbage values." << endl;
    
    cout << "\n✓ Union allows flexible sensor data storage" << endl;
    
    return 0;
}
```
