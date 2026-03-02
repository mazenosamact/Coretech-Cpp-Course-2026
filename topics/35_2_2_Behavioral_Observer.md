# Behavioral Patterns: Observer Pattern in C++

## Introduction to Observer Pattern

The **Observer pattern** is a behavioral design pattern that defines a one-to-many dependency between objects. When one object (the **subject**) changes state, all dependent objects (the **observers**) are notified automatically.

### Real-World Analogy

Think of a newspaper subscription:
- **Subject**: Newspaper publisher
- **Observers**: Subscribers
- **Event**: New edition published
- **Notification**: Subscribers receive the newspaper automatically

### Key Characteristics

- **Loose Coupling**: Subject doesn't need to know details about observers
- **Dynamic Relationships**: Observers can subscribe/unsubscribe at runtime
- **One-to-Many**: One subject notifies multiple observers
- **Automatic Notification**: Changes propagate automatically

### When to Use Observer Pattern

✓ A change in one object requires changing unknown number of others
✓ An object should notify others without knowing who they are
✓ Multiple objects must respond to state changes
✓ Event-driven architecture needed
✓ Real-time systems with multiple consumers of events

---

## Basic Observer Pattern Architecture

```
┌─────────────────┐
│    Subject      │ (Observable)
│  - observers[]  │
│  - state        │
├─────────────────┤
│ + attach()      │
│ + detach()      │
│ + notify()      │
│ + getState()    │
└────────┬────────┘
         │
         │ notifies
         │
    ┌────┴──────────────┬──────────────┐
    │                   │              │
┌───────────────┐  ┌───────────────┐  ┌───────────────┐
│   Observer A  │  │   Observer B  │  │   Observer C  │
├───────────────┤  ├───────────────┤  ├───────────────┤
│ + update()    │  │ + update()    │  │ + update()    │
└───────────────┘  └───────────────┘  └───────────────┘
```

---

## C++ Implementation

### Basic Observer Interface

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const string& event, const string& data) = 0;
};

// Subject (Observable)
class Subject {
private:
    vector<shared_ptr<Observer>> observers;
    string state;

public:
    // Subscribe an observer
    void attach(shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }
    
    // Unsubscribe an observer
    void detach(shared_ptr<Observer> observer) {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }
    
    // Notify all observers
    void notify(const string& event, const string& data) {
        for (auto& observer : observers) {
            observer->update(event, data);
        }
    }
    
    // Change state and notify
    void setState(const string& newState) {
        state = newState;
        notify("StateChanged", state);
    }
    
    string getState() const {
        return state;
    }
};

// Concrete observers
class ConcreteObserverA : public Observer {
public:
    void update(const string& event, const string& data) override {
        cout << "Observer A: " << event << " - " << data << endl;
    }
};

class ConcreteObserverB : public Observer {
public:
    void update(const string& event, const string& data) override {
        cout << "Observer B: " << event << " - " << data << endl;
    }
};

// Usage
int main() {
    auto subject = make_shared<Subject>();
    auto observerA = make_shared<ConcreteObserverA>();
    auto observerB = make_shared<ConcreteObserverB>();
    
    subject->attach(observerA);
    subject->attach(observerB);
    
    subject->setState("Active");     // Both observers notified
    subject->setState("Inactive");   // Both observers notified
    
    subject->detach(observerA);
    subject->setState("Restarting"); // Only B notified
    
    return 0;
}

// Output:
// Observer A: StateChanged - Active
// Observer B: StateChanged - Active
// Observer A: StateChanged - Inactive
// Observer B: StateChanged - Inactive
// Observer B: StateChanged - Restarting
```

---

## Embedded Systems Example: Sensor Monitoring System

### Scenario

An embedded system with multiple sensors (temperature, pressure, humidity) that need to notify various consumers (logging, alerts, display, data recording).

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <ctime>

using namespace std;

// Observer interface for sensor events
class SensorObserver {
public:
    virtual ~SensorObserver() = default;
    virtual void onSensorReading(float value, const string& unit) = 0;
    virtual void onSensorError(const string& errorMsg) = 0;
};

// Sensor subject
class Sensor {
private:
    string sensorName;
    float currentValue;
    vector<shared_ptr<SensorObserver>> observers;
    
public:
    Sensor(const string& name) : sensorName(name), currentValue(0.0f) {}
    
    void attach(shared_ptr<SensorObserver> observer) {
        observers.push_back(observer);
    }
    
    void detach(shared_ptr<SensorObserver> observer) {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }
    
    void readSensor(float value) {
        if (value < -50 || value > 150) {
            notifyError("Value out of range: " + to_string(value));
            return;
        }
        
        currentValue = value;
        notifyReading(value);
    }
    
    void notifyReading(float value) {
        for (auto& observer : observers) {
            observer->onSensorReading(value, getSensorUnit());
        }
    }
    
    void notifyError(const string& errorMsg) {
        for (auto& observer : observers) {
            observer->onSensorError(errorMsg);
        }
    }
    
    float getValue() const { return currentValue; }
    string getName() const { return sensorName; }
    
private:
    string getSensorUnit() const {
        if (sensorName.find("Temperature") != string::npos) return "°C";
        if (sensorName.find("Pressure") != string::npos) return "hPa";
        if (sensorName.find("Humidity") != string::npos) return "%";
        return "units";
    }
};

// Concrete observers
class TemperatureDisplay : public SensorObserver {
public:
    void onSensorReading(float value, const string& unit) override {
        cout << "[DISPLAY] Temperature: " << fixed << setprecision(2) 
             << value << " " << unit << endl;
    }
    
    void onSensorError(const string& errorMsg) override {
        cout << "[DISPLAY] Error: " << errorMsg << endl;
    }
};

class DataLogger : public SensorObserver {
private:
    int readingCount = 0;
    
public:
    void onSensorReading(float value, const string& unit) override {
        readingCount++;
        cout << "[LOGGER] Reading #" << readingCount << ": " 
             << value << " " << unit << endl;
    }
    
    void onSensorError(const string& errorMsg) override {
        cout << "[LOGGER] ERROR RECORDED: " << errorMsg << endl;
    }
};

class AlertSystem : public SensorObserver {
private:
    float threshold = 35.0f;
    
public:
    void onSensorReading(float value, const string& unit) override {
        if (value > threshold) {
            cout << "[ALERT] HIGH TEMPERATURE ALERT: " << value 
                 << " " << unit << " (Threshold: " << threshold << ")" << endl;
        }
    }
    
    void onSensorError(const string& errorMsg) override {
        cout << "[ALERT] CRITICAL ERROR: " << errorMsg << endl;
    }
};

// Usage
int main() {
    // Create sensor
    auto tempSensor = make_shared<Sensor>("Temperature Sensor");
    
    // Create observers
    auto display = make_shared<TemperatureDisplay>();
    auto logger = make_shared<DataLogger>();
    auto alerts = make_shared<AlertSystem>();
    
    // Subscribe observers
    tempSensor->attach(display);
    tempSensor->attach(logger);
    tempSensor->attach(alerts);
    
    cout << "=== Normal Readings ===\n";
    tempSensor->readSensor(22.5f);
    tempSensor->readSensor(28.3f);
    tempSensor->readSensor(36.1f);  // Triggers alert
    
    cout << "\n=== Error Handling ===\n";
    tempSensor->readSensor(200.0f);  // Out of range
    
    cout << "\n=== Detach Display ===\n";
    tempSensor->detach(display);
    tempSensor->readSensor(37.2f);   // Logger and alerts only
    
    return 0;
}

// Output:
// === Normal Readings ===
// [DISPLAY] Temperature: 22.50 °C
// [LOGGER] Reading #1: 22.5 °C
// [DISPLAY] Temperature: 28.30 °C
// [LOGGER] Reading #2: 28.3 °C
// [DISPLAY] Temperature: 36.10 °C
// [LOGGER] Reading #3: 36.1 °C
// [ALERT] HIGH TEMPERATURE ALERT: 36.1 °C (Threshold: 35)
//
// === Error Handling ===
// [LOGGER] ERROR RECORDED: Value out of range: 200.000000
// [ALERT] CRITICAL ERROR: Value out of range: 200.000000
//
// === Detach Display ===
// [LOGGER] Reading #4: 37.2 °C
// [ALERT] HIGH TEMPERATURE ALERT: 37.2 °C (Threshold: 35)
```

---

## Embedded Linux System Example: File System Events

### Scenario

An Embedded Linux application monitoring file system changes and notifying different subsystems (backup service, indexing service, cache invalidation).

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

// File system event observer
class FileSystemObserver {
public:
    virtual ~FileSystemObserver() = default;
    virtual void onFileCreated(const string& filepath) = 0;
    virtual void onFileModified(const string& filepath) = 0;
    virtual void onFileDeleted(const string& filepath) = 0;
};

// File system monitor (subject)
class FileSystemMonitor {
private:
    string watchPath;
    vector<shared_ptr<FileSystemObserver>> observers;
    
public:
    FileSystemMonitor(const string& path) : watchPath(path) {}
    
    void subscribe(shared_ptr<FileSystemObserver> observer) {
        observers.push_back(observer);
    }
    
    void unsubscribe(shared_ptr<FileSystemObserver> observer) {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }
    
    // Simulate file creation event
    void simulateFileCreated(const string& filename) {
        cout << "[FS Event] File created: " << watchPath << "/" << filename << "\n";
        notifyFileCreated(filename);
    }
    
    // Simulate file modification event
    void simulateFileModified(const string& filename) {
        cout << "[FS Event] File modified: " << watchPath << "/" << filename << "\n";
        notifyFileModified(filename);
    }
    
    // Simulate file deletion event
    void simulateFileDeleted(const string& filename) {
        cout << "[FS Event] File deleted: " << watchPath << "/" << filename << "\n";
        notifyFileDeleted(filename);
    }
    
private:
    void notifyFileCreated(const string& filename) {
        for (auto& observer : observers) {
            observer->onFileCreated(watchPath + "/" + filename);
        }
    }
    
    void notifyFileModified(const string& filename) {
        for (auto& observer : observers) {
            observer->onFileModified(watchPath + "/" + filename);
        }
    }
    
    void notifyFileDeleted(const string& filename) {
        for (auto& observer : observers) {
            observer->onFileDeleted(watchPath + "/" + filename);
        }
    }
};

// Concrete observers
class BackupService : public FileSystemObserver {
public:
    void onFileCreated(const string& filepath) override {
        cout << "[BACKUP] Queued for backup: " << filepath << "\n";
    }
    
    void onFileModified(const string& filepath) override {
        cout << "[BACKUP] Updated backup: " << filepath << "\n";
    }
    
    void onFileDeleted(const string& filepath) override {
        cout << "[BACKUP] Marked as deleted: " << filepath << "\n";
    }
};

class IndexingService : public FileSystemObserver {
public:
    void onFileCreated(const string& filepath) override {
        cout << "[INDEX] Indexing new file: " << filepath << "\n";
    }
    
    void onFileModified(const string& filepath) override {
        cout << "[INDEX] Re-indexing modified file: " << filepath << "\n";
    }
    
    void onFileDeleted(const string& filepath) override {
        cout << "[INDEX] Removing from index: " << filepath << "\n";
    }
};

class CacheInvalidator : public FileSystemObserver {
public:
    void onFileCreated(const string& filepath) override {
        cout << "[CACHE] No cache entry to invalidate: " << filepath << "\n";
    }
    
    void onFileModified(const string& filepath) override {
        cout << "[CACHE] Invalidating cache for: " << filepath << "\n";
    }
    
    void onFileDeleted(const string& filepath) override {
        cout << "[CACHE] Cleared cache for: " << filepath << "\n";
    }
};

// Usage
int main() {
    auto fsMonitor = make_shared<FileSystemMonitor>("/data");
    
    auto backup = make_shared<BackupService>();
    auto indexing = make_shared<IndexingService>();
    auto cache = make_shared<CacheInvalidator>();
    
    fsMonitor->subscribe(backup);
    fsMonitor->subscribe(indexing);
    fsMonitor->subscribe(cache);
    
    cout << "=== File Operations ===\n";
    fsMonitor->simulateFileCreated("config.json");
    cout << "\n";
    fsMonitor->simulateFileModified("config.json");
    cout << "\n";
    fsMonitor->simulateFileDeleted("config.json");
    
    cout << "\n=== Detach Indexing Service ===\n";
    fsMonitor->unsubscribe(indexing);
    fsMonitor->simulateFileCreated("data.bin");
    
    return 0;
}

// Output:
// === File Operations ===
// [FS Event] File created: /data/config.json
// [BACKUP] Queued for backup: /data/config.json
// [INDEX] Indexing new file: /data/config.json
// [CACHE] No cache entry to invalidate: /data/config.json
//
// [FS Event] File modified: /data/config.json
// [BACKUP] Updated backup: /data/config.json
// [INDEX] Re-indexing modified file: /data/config.json
// [CACHE] Invalidating cache for: /data/config.json
//
// [FS Event] File deleted: /data/config.json
// [BACKUP] Marked as deleted: /data/config.json
// [INDEX] Removing from index: /data/config.json
// [CACHE] Cleared cache for: /data/config.json
//
// === Detach Indexing Service ===
// [FS Event] File created: /data/data.bin
// [BACKUP] Queued for backup: /data/data.bin
// [CACHE] No cache entry to invalidate: /data/data.bin
```

---

## Observer vs Publisher-Subscriber Pattern

### Core Differences

| Aspect | Observer | Publisher-Subscriber |
|--------|----------|---------------------|
| **Coupling** | Direct (subject knows observers) | Decoupled (via broker) |
| **Communication** | Synchronous (direct call) | Asynchronous (via broker) |
| **Broker** | Not needed | Required (message broker) |
| **Complexity** | Simple | More complex |
| **Scalability** | Limited (all in same process) | High (distributed systems) |
| **Latency** | Low | Higher (broker adds overhead) |
| **Timing** | Immediate | Eventual (through queue) |
| **Location** | Must be in same process | Can be on different machines |

### Visual Comparison

```
OBSERVER PATTERN:
┌─────────────┐
│   Subject   │ ────push notif──→ ┌──────────────┐
│             │                   │ Observer 1   │
└─────────────┘                   └──────────────┘
                                  ┌──────────────┐
                              ──→ │ Observer 2   │
                                  └──────────────┘

PUBLISHER-SUBSCRIBER PATTERN:
┌───────────────┐                ┌────────────────┐                ┌──────────────┐
│  Publisher 1  │                │  Message       │                │ Subscriber 1 │
│               │──publish──→     │  Broker        │  ──deliver─→  │              │
└───────────────┘   (topic)       │                │   (topic)     └──────────────┘
                                  │  (Decoupled)   │
┌───────────────┐                 │  (Asynchronous)│              ┌──────────────┐
│  Publisher 2  │──publish──→      │  (Queuing)     │──deliver──→  │ Subscriber 2 │
│               │    (topic)       │                │   (topic)     │              │
└───────────────┘                  └────────────────┘               └──────────────┘
```

---

## When to Use Each Pattern

### Use Observer Pattern When:

✓ Subject and observers are in the same process/application
✓ Real-time, synchronous notifications required
✓ Simple architecture with few observers
✓ Low latency is important
✓ Tight coupling is acceptable
✓ Memory efficiency critical (embedded systems)
✓ Number of observers known at design time

### Use Publisher-Subscriber When:

✓ Publishers and subscribers may not know each other
✓ Systems are distributed across multiple machines/processes
✓ Asynchronous processing acceptable/desired
✓ High scalability needed
✓ Need to add/remove subscribers at runtime dynamically
✓ Handling bursty workloads with queuing
✓ Enterprise-level systems with multiple teams

---

## Message Broker Concept

### What is a Message Broker?

A **message broker** is an intermediary that:
1. Accepts messages from publishers
2. Routes messages to subscribers
3. Manages message delivery guarantees
4. Decouples publishers from subscribers
5. Enables asynchronous communication

### Broker Responsibilities

```cpp
// Simplified message broker concept
class MessageBroker {
private:
    map<string, queue<Message>> topics;  // Topic → message queue
    map<string, vector<Subscriber>> subscriptions;  // Topic → subscribers
    
public:
    // Publisher publishes to topic
    void publish(const string& topic, const Message& message) {
        topics[topic].push(message);
        deliverMessages(topic);
    }
    
    // Subscriber subscribes to topic
    void subscribe(const string& topic, Subscriber handler) {
        subscriptions[topic].push_back(handler);
    }
    
    // Deliver queued messages to subscribers
    void deliverMessages(const string& topic) {
        while (!topics[topic].empty()) {
            Message msg = topics[topic].front();
            topics[topic].pop();
            
            for (auto& subscriber : subscriptions[topic]) {
                subscriber.handle(msg);  // Async delivery
            }
        }
    }
};
```

---

## Broker-Based Implementation Example

### Message Broker Pattern in Embedded Linux

```cpp
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <memory>
#include <string>

using namespace std;

struct Message {
    string topic;
    string data;
    int timestamp;
};

class Subscriber {
public:
    virtual ~Subscriber() = default;
    virtual void handle(const Message& msg) = 0;
    virtual string getName() const = 0;
};

class MessageBroker {
private:
    map<string, queue<Message>> topicQueues;
    map<string, vector<shared_ptr<Subscriber>>> subscriptions;
    int messageCount = 0;
    
public:
    // Publisher publishes message
    void publish(const string& topic, const string& data) {
        Message msg{topic, data, messageCount++};
        cout << "[BROKER] Published: " << topic << " - " << data << "\n";
        
        topicQueues[topic].push(msg);
        deliverMessages(topic);
    }
    
    // Subscriber subscribes to topic
    void subscribe(const string& topic, shared_ptr<Subscriber> subscriber) {
        subscriptions[topic].push_back(subscriber);
        cout << "[BROKER] " << subscriber->getName() << " subscribed to " 
             << topic << "\n";
    }
    
    // Deliver all queued messages
    void deliverMessages(const string& topic) {
        while (!topicQueues[topic].empty()) {
            Message msg = topicQueues[topic].front();
            topicQueues[topic].pop();
            
            cout << "[BROKER] Delivering to " << subscriptions[topic].size() 
                 << " subscribers\n";
            
            for (auto& subscriber : subscriptions[topic]) {
                subscriber->handle(msg);
            }
        }
    }
};

// Example subscribers
class SystemMonitor : public Subscriber {
public:
    void handle(const Message& msg) override {
        cout << "  [SYS_MONITOR] Received: " << msg.data << "\n";
    }
    
    string getName() const override { return "SystemMonitor"; }
};

class EventLogger : public Subscriber {
public:
    void handle(const Message& msg) override {
        cout << "  [EVENT_LOGGER] Logged: " << msg.data << "\n";
    }
    
    string getName() const override { return "EventLogger"; }
};

class AlertGenerator : public Subscriber {
public:
    void handle(const Message& msg) override {
        cout << "  [ALERT_GEN] Alert triggered: " << msg.data << "\n";
    }
    
    string getName() const override { return "AlertGenerator"; }
};

// Usage
int main() {
    auto broker = make_shared<MessageBroker>();
    
    auto monitor = make_shared<SystemMonitor>();
    auto logger = make_shared<EventLogger>();
    auto alerts = make_shared<AlertGenerator>();
    
    cout << "=== Subscriptions ===\n";
    broker->subscribe("system.event", monitor);
    broker->subscribe("system.event", logger);
    broker->subscribe("system.event", alerts);
    
    cout << "\n=== Publishing Events ===\n";
    broker->publish("system.event", "CPU usage > 80%");
    
    cout << "\n";
    broker->publish("system.event", "Memory pressure detected");
    
    return 0;
}

// Output:
// === Subscriptions ===
// [BROKER] SystemMonitor subscribed to system.event
// [BROKER] EventLogger subscribed to system.event
// [BROKER] AlertGenerator subscribed to system.event
//
// === Publishing Events ===
// [BROKER] Published: system.event - CPU usage > 80%
// [BROKER] Delivering to 3 subscribers
//   [SYS_MONITOR] Received: CPU usage > 80%
//   [EVENT_LOGGER] Logged: CPU usage > 80%
//   [ALERT_GEN] Alert triggered: CPU usage > 80%
//
// [BROKER] Published: system.event - Memory pressure detected
// [BROKER] Delivering to 3 subscribers
//   [SYS_MONITOR] Received: Memory pressure detected
//   [EVENT_LOGGER] Logged: Memory pressure detected
//   [ALERT_GEN] Alert triggered: Memory pressure detected
```

---

## Real-World Broker Technologies

### For Embedded Systems

1. **In-Process Brokers** (Single Machine)
   - Custom C++ implementation
   - POSIX message queues
   - Qt Signals/Slots (event bus)

2. **Lightweight Message Brokers** (Embedded Linux)
   - **Mosquitto**: MQTT broker for IoT
   - **RabbitMQ Lite**: Simplified version
   - **Redis**: Pub/Sub capability
   - **ZeroMQ (ZMQ)**: Lightweight, no broker needed

### For Distributed Systems

1. **Enterprise Brokers**
   - Apache Kafka: High-throughput, distributed streaming
   - RabbitMQ: Full-featured, reliable
   - ActiveMQ: Java-based, comprehensive

2. **Cloud-Native**
   - AWS SNS/SQS: Amazon managed service
   - Azure Service Bus: Microsoft managed
   - Google Pub/Sub: Google cloud service

3. **Lightweight Protocols**
   - MQTT: IoT and embedded systems
   - AMQP: Advanced Message Queuing Protocol
   - XMPP: For chat/presence systems

---

## Implementation Comparison

### Observer Pattern Pros/Cons

**Pros**:
- ✓ Simple and straightforward
- ✓ Low latency (direct calls)
- ✓ No external dependencies
- ✓ Memory efficient
- ✓ Fast in embedded systems

**Cons**:
- ✗ Tight coupling
- ✗ All components must be in same address space
- ✗ Synchronous (blocking)
- ✗ Hard to debug (complex call chains)
- ✗ Not suitable for distribution

### Publisher-Subscriber Pattern Pros/Cons

**Pros**:
- ✓ Loose coupling
- ✓ Highly scalable
- ✓ Asynchronous processing
- ✓ Distributed system support
- ✓ Message persistence

**Cons**:
- ✗ More complex
- ✗ Higher latency
- ✗ Requires broker/infrastructure
- ✗ Message ordering challenges
- ✗ Debugging complexity

---

## Design Decision Tree

```
Event Notification Needed?
│
├─ Single Process/Machine?
│  │
│  ├─ YES
│  │  ├─ Real-time critical?
│  │  │  ├─ YES → Observer Pattern
│  │  │  └─ NO  → Either pattern
│  │  └─ Memory constrained?
│  │     ├─ YES → Observer Pattern
│  │     └─ NO  → Observer or Broker
│  │
│  └─ NO
│     ├─ Distributed System?
│     │  ├─ YES → Publisher-Subscriber
│     │  └─ NO  → Observer (if local only)
│     │
│     └─ Need Persistence?
│        ├─ YES → Publisher-Subscriber with Broker
│        └─ NO  → Consider lightweight broker
│
└─ Many independent consumers?
   ├─ YES (scalability needed) → Publishing-Subscriber
   └─ NO → Observer sufficient
```

---

## Best Practices

### For Observer Pattern

1. **Use weak pointers** to prevent circular references
2. **Avoid observer modifications** during notification
3. **Keep observers independent** from each other
4. **Document event ordering** if multiple observers
5. **Use thread-safe collections** in multi-threaded systems
6. **Provide memory guarantees** (RAII for observer lifetime)

### For Publisher-Subscriber Pattern

1. **Choose appropriate broker** for your use case
2. **Define clear topic hierarchies**
3. **Handle message losses** gracefully
4. **Implement idempotency** in subscribers
5. **Monitor broker performance** and queue depths
6. **Implement rate limiting** to prevent overload
7. **Use message expiration** to prevent stale data

### General Guidelines

1. **Start simple** (Observer) and move to Broker if needed
2. **Document coupling** between components
3. **Test error paths** (observer/broker failures)
4. **Monitor system health** (queue depths, latencies)
5. **Consider fallback mechanisms** for critical events
6. **Measure actual latency** requirements
7. **Plan for scalability** from day one

---

## Summary

| Scenario | Pattern | Reason |
|----------|---------|--------|
| **Single embedded system with sensors** | Observer | Direct, simple, performant |
| **IoT network with multiple devices** | Pub/Sub with MQTT Broker | Distributed, asynchronous, protocol standardized |
| **Linux daemon with internal events** | Observer | In-process, tight coupling acceptable |
| **Microservices architecture** | Pub/Sub with Enterprise Broker | Scalability, decoupling, persistence |
| **Real-time control system** | Observer | Low latency critical |
| **Event streaming (logs, metrics)** | Pub/Sub with Kafka | High throughput, persistence, scalability |
| **Simple UI event handling** | Observer | Single app, tight coupling OK |
| **Multi-tenant SaaS platform** | Pub/Sub with Cloud Broker | Isolation, scale per tenant |

---


