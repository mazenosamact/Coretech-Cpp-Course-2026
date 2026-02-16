# Structs - Practical Exercises

## Exercise 1: Embedded Device Configuration (Embedded Systems)
**Context:** Configuring an embedded device with multiple parameters that need to be read/written together.

**Problem:**
```cpp
// You need to create a structure to represent a device configuration
// that will be stored in EEPROM (persistent memory)
// 
// Requirements:
// 1. Device ID (4 bytes)
// 2. Firmware version (3 bytes: major.minor.patch)
// 3. Operation mode (1 byte: 0=sleep, 1=active, 2=test)
// 4. Sensor calibration values (4 float values)
// 5. Create a function to validate configuration
// 6. Create a function to save to a file (simulating EEPROM write)
```

**Solution:**
```cpp
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct DeviceConfig {
    uint32_t device_id;
    struct {
        uint8_t major;
        uint8_t minor;
        uint8_t patch;
    } firmware_version;
    uint8_t operation_mode;
    float calibration[4];
};

void validateConfig(const DeviceConfig &config) {
    cout << "Validating configuration..." << endl;
    
    if (config.operation_mode > 2) {
        cout << "✗ Invalid operation mode" << endl;
        return;
    }
    
    bool valid_calibration = true;
    for (int i = 0; i < 4; i++) {
        if (config.calibration[i] < 0 || config.calibration[i] > 100) {
            valid_calibration = false;
            break;
        }
    }
    
    if (valid_calibration) {
        cout << "✓ Configuration is valid" << endl;
    } else {
        cout << "✗ Calibration values out of range" << endl;
    }
}

void saveConfig(const DeviceConfig &config, const char *filename) {
    ofstream file(filename, ios::binary);
    file.write((char *)&config, sizeof(DeviceConfig));
    file.close();
    cout << "✓ Configuration saved to " << filename << endl;
}

int main() {
    // Create and configure device
    DeviceConfig dev_config;
    dev_config.device_id = 0x12345678;
    dev_config.firmware_version = {1, 2, 3};
    dev_config.operation_mode = 1;  // Active mode
    dev_config.calibration[0] = 25.5f;
    dev_config.calibration[1] = 30.2f;
    dev_config.calibration[2] = 45.8f;
    dev_config.calibration[3] = 12.3f;
    
    validateConfig(dev_config);
    saveConfig(dev_config, "device.cfg");
    
    cout << "\nDevice Configuration:" << endl;
    cout << "Device ID: 0x" << hex << dev_config.device_id << dec << endl;
    cout << "Firmware: " << (int)dev_config.firmware_version.major << "."
         << (int)dev_config.firmware_version.minor << "."
         << (int)dev_config.firmware_version.patch << endl;
    cout << "Mode: " << (int)dev_config.operation_mode << endl;
    
    return 0;
}
```

---

## Exercise 2: Nested Structures for Network Protocol (Backend Development)
**Context:** Parsing network packets that have nested headers.

**Problem:**
```cpp
// Create a structure to represent an IPv4 network packet
// with nested headers:
// - Ethernet frame (source/dest MAC, type)
// - IPv4 header (source/dest IP, protocol)
// - Port information (source/dest ports)
//
// Tasks:
// 1. Define all structures with correct field sizes
// 2. Create an instance representing a TCP packet
// 3. Print packet details in human-readable format
// 4. Verify packet checksum logic (simplified)
```

**Solution:**
```cpp
#include <iostream>
#include <cstdint>
#include <cstring>
using namespace std;

struct EthernetFrame {
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint16_t frame_type;  // 0x0800 for IPv4
};

struct IPv4Header {
    uint8_t version_ihl;
    uint8_t dscp_ecn;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags_fragment;
    uint8_t ttl;
    uint8_t protocol;  // 6 for TCP
    uint16_t checksum;
    uint32_t src_ip;
    uint32_t dest_ip;
};

struct TCPSegment {
    uint16_t src_port;
    uint16_t dest_port;
    uint32_t seq_number;
    uint32_t ack_number;
};

struct NetworkPacket {
    EthernetFrame eth;
    IPv4Header ipv4;
    TCPSegment tcp;
};

void printPacketInfo(const NetworkPacket &pkt) {
    cout << "=== Network Packet Analysis ===" << endl;
    
    cout << "\nEthernet Frame:" << endl;
    cout << "Dest MAC: ";
    for (int i = 0; i < 6; i++) {
        cout << hex << (int)pkt.eth.dest_mac[i];
        if (i < 5) cout << ":";
    }
    cout << dec << endl;
    
    cout << "\nIPv4 Header:" << endl;
    cout << "Source IP: " << ((pkt.ipv4.src_ip >> 24) & 0xFF) << "."
         << ((pkt.ipv4.src_ip >> 16) & 0xFF) << "."
         << ((pkt.ipv4.src_ip >> 8) & 0xFF) << "."
         << (pkt.ipv4.src_ip & 0xFF) << endl;
    cout << "TTL: " << (int)pkt.ipv4.ttl << endl;
    
    cout << "\nTCP Segment:" << endl;
    cout << "Source Port: " << pkt.tcp.src_port << endl;
    cout << "Dest Port: " << pkt.tcp.dest_port << endl;
}

int main() {
    NetworkPacket pkt = {};
    
    // Set Ethernet frame
    memset(pkt.eth.dest_mac, 0xFF, 6);  // Broadcast
    memset(pkt.eth.src_mac, 0x00, 6);
    pkt.eth.frame_type = 0x0800;
    
    // Set IPv4 header
    pkt.ipv4.version_ihl = 0x45;  // Version 4, IHL 5
    pkt.ipv4.protocol = 6;  // TCP
    pkt.ipv4.ttl = 64;
    pkt.ipv4.src_ip = 0xC0A80001;  // 192.168.0.1
    pkt.ipv4.dest_ip = 0x08080808; // 8.8.8.8
    
    // Set TCP segment
    pkt.tcp.src_port = 80;
    pkt.tcp.dest_port = 8080;
    
    printPacketInfo(pkt);
    
    cout << "\n✓ Packet structure created and displayed" << endl;
    
    return 0;
}
```

---

## Exercise 3: Sensor Data Aggregation (IoT/Backend)
**Context:** Collecting data from multiple sensors and aggregating them.

**Problem:**
```cpp
// Create nested structures for a sensor network:
// - SensorReading: timestamp, value, unit
// - SensorNode: id, location, array of readings
// - GatewayData: array of sensor nodes
//
// Tasks:
// 1. Create 3 sensor nodes with 5 readings each
// 2. Find the sensor with highest average reading
// 3. Calculate statistics (min, max, avg) for each sensor
// 4. Write aggregated data to JSON-like format
```

**Solution:**
```cpp
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

struct SensorReading {
    time_t timestamp;
    float value;
    const char *unit;
};

struct SensorNode {
    int id;
    const char *location;
    SensorReading readings[5];
    int reading_count;
};

struct GatewayData {
    SensorNode nodes[3];
    int node_count;
};

float calculateAverage(const SensorNode &node) {
    float sum = 0;
    for (int i = 0; i < node.reading_count; i++) {
        sum += node.readings[i].value;
    }
    return sum / node.reading_count;
}

void printSensorStats(const SensorNode &node) {
    float min_val = node.readings[0].value;
    float max_val = node.readings[0].value;
    float sum = 0;
    
    for (int i = 0; i < node.reading_count; i++) {
        if (node.readings[i].value < min_val) min_val = node.readings[i].value;
        if (node.readings[i].value > max_val) max_val = node.readings[i].value;
        sum += node.readings[i].value;
    }
    
    cout << "\nSensor " << node.id << " (" << node.location << "):" << endl;
    cout << "  Min: " << min_val << " " << node.readings[0].unit << endl;
    cout << "  Max: " << max_val << " " << node.readings[0].unit << endl;
    cout << "  Avg: " << (sum / node.reading_count) << " " << node.readings[0].unit << endl;
}

int main() {
    GatewayData gateway = {};
    
    // Initialize sensor 1: Temperature
    gateway.nodes[0].id = 1;
    gateway.nodes[0].location = "Room A";
    gateway.nodes[0].reading_count = 5;
    float temps[] = {22.5, 23.1, 22.8, 23.5, 22.9};
    for (int i = 0; i < 5; i++) {
        gateway.nodes[0].readings[i] = {time(nullptr), temps[i], "°C"};
    }
    
    // Initialize sensor 2: Humidity
    gateway.nodes[1].id = 2;
    gateway.nodes[1].location = "Room B";
    gateway.nodes[1].reading_count = 5;
    float humidity[] = {45.2, 46.1, 45.8, 47.2, 46.5};
    for (int i = 0; i < 5; i++) {
        gateway.nodes[1].readings[i] = {time(nullptr), humidity[i], "%"};
    }
    
    // Initialize sensor 3: Pressure
    gateway.nodes[2].id = 3;
    gateway.nodes[2].location = "Outdoor";
    gateway.nodes[2].reading_count = 5;
    float pressure[] = {1013.25, 1013.30, 1013.28, 1013.35, 1013.32};
    for (int i = 0; i < 5; i++) {
        gateway.nodes[2].readings[i] = {time(nullptr), pressure[i], "hPa"};
    }
    
    gateway.node_count = 3;
    
    // Find sensor with highest average
    int best_sensor = 0;
    float best_avg = calculateAverage(gateway.nodes[0]);
    
    for (int i = 1; i < gateway.node_count; i++) {
        float avg = calculateAverage(gateway.nodes[i]);
        if (avg > best_avg) {
            best_avg = avg;
            best_sensor = i;
        }
    }
    
    cout << "Sensor Statistics:" << endl;
    for (int i = 0; i < gateway.node_count; i++) {
        printSensorStats(gateway.nodes[i]);
    }
    
    cout << "\n✓ Analysis complete" << endl;
    
    return 0;
}
```
