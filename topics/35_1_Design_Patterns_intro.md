# Design Patterns Introduction

## What are Design Patterns?

Design patterns are **reusable solutions to common problems** that occur during software design and development. They represent best practices and can be used to solve recurring design problems.

### Key Characteristics:
- **Proven Solutions**: Tested and verified by experienced developers
- **Reusable**: Can be applied to different contexts and projects
- **Well-Documented**: Established naming conventions and documentation
- **Language-Independent**: Core concepts apply across all programming languages
- **Problem-Context Solutions**: Each pattern addresses specific design challenges

### Benefits of Using Design Patterns:
1. **Faster Development**: Use tested solutions instead of reinventing the wheel
2. **Code Reusability**: Apply patterns across multiple projects
3. **Better Communication**: Team members understand pattern-based code immediately
4. **Scalability**: Patterns support growing and complex systems
5. **Maintainability**: Well-organized code following established patterns
6. **Flexibility**: Patterns enable easy changes and extensions

---

## Categories of Design Patterns

Design patterns are typically organized into four main categories:

### 1. **Behavioral Patterns**
Focus on **communication between objects** and responsibility distribution.

**Purpose**: 
- Define how objects interact and distribute responsibility
- Increase flexibility in object collaboration
- Encapsulate behavior variations

**Common Behavioral Patterns**:

| Pattern | Purpose |
|---------|---------|
| **Observer** | Notify multiple objects about state changes without tight coupling |
| **State Machine** | Allow object behavior to change based on internal state |
| **Strategy** | Encapsulate algorithms as interchangeable objects |
| **Command** | Encapsulate requests as objects for delayed/queued execution |
| **Iterator** | Access elements of a container sequentially without exposing structure |
| **Visitor** | Add operations to objects without modifying their classes |
| **Template Method** | Define algorithm skeleton, let subclasses override steps |
| **Chain of Responsibility** | Pass request along chain of handlers |
| **Mediator** | Centralize communication between objects |
| **Memento** | Capture and restore object state |
| **Interpreter** | Define grammar for a language |

**When to Use Behavioral Patterns**:
- Objects need to communicate without tight coupling
- Behavior varies based on internal state
- You need to encapsulate algorithms
- Processing order is flexible or data-dependent

---

### 2. **Creational Patterns**
Focus on **object creation mechanisms** to make systems more flexible and independent.

**Purpose**:
- Abstract object creation process
- Make systems independent of how objects are created
- Hide creation details from clients

**Common Creational Patterns**:

| Pattern | Purpose |
|---------|---------|
| **Singleton** | Ensure only one instance exists globally |
| **Factory** | Create objects without specifying exact classes |
| **Abstract Factory** | Create families of related objects |
| **Builder** | Construct complex objects step by step |
| **Prototype** | Create new objects by cloning existing ones |
| **Pool** | Reuse expensive objects instead of creating new ones |

**When to Use Creational Patterns**:
- Object creation is complex or expensive
- Want flexibility in which classes to instantiate
- Need to control object creation process
- System should be independent of how objects are composed

**Example Use Case**:
```cpp
// Without Factory (tight coupling)
Database* db;
if (useMySQL) {
    db = new MySQLDatabase();
} else {
    db = new PostgresDatabase();
}

// With Factory (loose coupling)
Database* db = DatabaseFactory::create(databaseType);
```

---

### 3. **Structural Patterns**
Focus on **composition of objects and classes** to form larger structures.

**Purpose**:
- Compose objects into larger structures
- Keep structures flexible and efficient
- Simplify relationships between entities

**Common Structural Patterns**:

| Pattern | Purpose |
|---------|---------|
| **Adapter** | Make incompatible interfaces compatible |
| **Bridge** | Decouple abstraction from implementation |
| **Composite** | Treat individual and composite objects uniformly |
| **Decorator** | Add responsibilities to objects dynamically |
| **Facade** | Provide simplified interface to complex subsystem |
| **Flyweight** | Share objects efficiently to reduce memory |
| **Proxy** | Control access to another object |
| **Wrapper** | Wrap object to add new functionality |

**When to Use Structural Patterns**:
- Need to work with incompatible interfaces
- Want to add functionality to objects dynamically
- Need simplified interface to complex subsystems
- Want to defer object access or control it

**Example Use Case**:
```cpp
// Without Adapter (incompatible interfaces)
// LegacyInterface and NewInterface don't match - compilation error

// With Adapter
class Adapter : public NewInterface {
    LegacyInterface* legacy;
public:
    void newOperation() override {
        legacy->oldOperation();  // Translate interface
    }
};
```

---

### 4. **Concurrent Patterns**
Focus on **multi-threading and concurrent execution** challenges.

**Purpose**:
- Manage concurrent access to shared resources
- Coordinate parallel activities
- Avoid race conditions and deadlocks

**Common Concurrent Patterns**:

| Pattern | Purpose |
|---------|---------|
| **Active Object** | Encapsulate concurrent execution in object |
| **Actor** | Independent entities communicating via messages |
| **Monitor Object** | Synchronize method execution in multi-threaded environment |
| **Reactor** | Demultiplex events and dispatch to handlers |
| **Thread Pool** | Reuse threads for multiple tasks |
| **Producer-Consumer** | Decouple data production from consumption |
| **Read-Write Lock** | Allow concurrent reads, exclusive writes |
| **Double-Checked Locking** | Efficiently check conditions in multithreaded code |

**When to Use Concurrent Patterns**:
- Working with multiple threads
- Need thread synchronization
- Want to avoid race conditions
- Handling asynchronous operations

**Example Use Case**:
```cpp
// Without Thread Pool (creates new thread for each task)
for (auto& task : tasks) {
    thread t(executeTask, task);  // Expensive!
    t.detach();
}

// With Thread Pool
ThreadPool pool(4);  // 4 reusable threads
for (auto& task : tasks) {
    pool.submit(executeTask, task);  // Efficient!
}
```

---

### 5. **Architectural Patterns**
Focus on **overall system structure** and high-level organization.

**Purpose**:
- Define overall system structure
- Show system interactions at highest level
- Address fundamental structural organization

**Common Architectural Patterns**:

| Pattern | Purpose |
|---------|---------|
| **Model-View-Controller (MVC)** | Separate data, presentation, and logic |
| **Model-View-ViewModel (MVVM)** | Separate UI logic from presentation |
| **Layered Architecture** | Organize system into horizontal layers |
| **Microservices** | Decompose system into small, independent services |
| **Event-Driven** | System behavior triggered by events |
| **Pipeline** | Process data through sequence of transformations |
| **Plug-in** | Allow extending system with plug-in modules |

**When to Use Architectural Patterns**:
- Designing overall system structure
- Multiple teams working on same system
- Need clear separation of concerns
- System needs to be maintainable and scalable

---

## Pattern Selection Guide

### Choose Pattern Based On Problem Type:

```
Problem: Need to restrict object creation
   └─> Use: Singleton, Factory, Builder

Problem: Objects need to communicate
   └─> Use: Observer, Mediator, Command

Problem: Need different algorithm implementations
   └─> Use: Strategy, Bridge, Template Method

Problem: Need to add functionality dynamically
   └─> Use: Decorator, Proxy, Adapter

Problem: Working with groups of objects uniformly
   └─> Use: Composite, Visitor, Iterator

Problem: Multi-threaded access to shared resource
   └─> Use: Monitor Object, Thread Pool, Producer-Consumer

Problem: Incompatible interfaces need to work together
   └─> Use: Adapter, Bridge, Facade
```

---

## Anti-Patterns: Patterns to AVOID

Just as important as knowing good patterns is knowing bad ones:

| Anti-Pattern | Problem | Solution |
|----------------|---------|----------|
| **God Object** | Single class does too much | Break into smaller classes |
| **Spaghetti Code** | No clear structure or flow | Apply architectural patterns |
| **Copy-Paste Programming** | Duplicated code everywhere | Extract common code, use patterns |
| **Ping-Pong Pattern** | Excessive back-and-forth calls | Redesign interaction model |
| **Boat Anchor** | Obsolete code kept "just in case" | Remove unused code |
| **Golden Hammer** | Using one pattern for everything | Choose appropriate patterns |
| **Circular Dependency** | Modules depend on each other | Reorganize dependencies |
| **Double Checked Locking** | Looks efficient but is problematic | Use proper synchronization |

---

## Pattern Classification Matrix

```
          | Behavioral | Creational | Structural | Concurrent
----------|------------|-----------|-----------|----------
Scope     |            |           |           |
Class     | Template   | Factory   | Adapter   | -
          | Method     |           |           |
          |            |           |           |
Object    | Observer   | Singleton | Proxy     | Active
          | Command    | Builder   | Decorator | Object
          | Strategy   | Prototype | Composite | Actor
          | Iterator   | -         | Facade    | Thread Pool
          | State      | -         | Bridge    | Reactor
          | Visitor    | -         | -         | -
```

---

## Pattern Learning Path

**Beginner Patterns** (Start Here):
1. Singleton - Simplest creational pattern
2. Factory - Foundation for flexible object creation
3. Observer - Most useful behavioral pattern
4. Decorator - Introduces dynamic behavior

**Intermediate Patterns**:
1. Strategy - Encapsulate algorithms
2. Adapter - Make things work together
3. Template Method - Define algorithm skeleton
4. Builder - Complex object construction

**Advanced Patterns**:
1. CRTP (Curiously Recurring Template Pattern) - Static polymorphism
2. Command - Encapsulate requests as objects
3. Visitor - Operations on complex structures
4. Composite - Recursive object composition

**Concurrent Patterns**:
1. Thread Pool - Start with thread management
2. Producer-Consumer - Async communication
3. Reactor - Event-driven systems
4. Actor - Message-passing concurrency

---

## Key Principles Behind Patterns

### SOLID Principles

Design patterns implement these core principles:

- **S**ingle Responsibility: Each class has one reason to change
- **O**pen/Closed: Open for extension, closed for modification
- **L**iskov Substitution: Derived classes can replace base classes
- **I**nterface Segregation: Many specific interfaces vs. one general
- **D**ependency Inversion: Depend on abstractions, not concretions

### DRY (Don't Repeat Yourself)
- Patterns eliminate code duplication
- Encapsulate common solutions

### Composition Over Inheritance
- Patterns prefer composition to inheritance
- More flexible and maintainable

### Favor Abstraction
- Patterns use abstractions to decouple components
- Changes in implementation don't affect clients

---

## When NOT to Use Design Patterns

⚠️ **Avoid Over-Engineering**:

1. **Simple Problems**: Don't add patterns to trivial code
2. **Premature Complexity**: Use patterns only when needed
3. **Team Unfamiliarity**: Pattern implementation requires understanding
4. **Performance Critical Code**: Some patterns add overhead
5. **Learning Projects**: Start simple, add patterns as you learn

**Rule of Three**:
- Use a pattern only when you've seen the problem 3 times
- Don't apply patterns speculative

---

## Summary

| Category | Focus | Usage |
|----------|-------|-------|
| **Behavioral** | Object interaction | When objects need to communicate |
| **Creational** | Object creation | When construction is complex |
| **Structural** | Object composition | When composing larger structures |
| **Concurrent** | Parallel execution | When using multiple threads |
| **Architectural** | System structure | When designing overall architecture |

---

## Coupling and Cohesion in Software Development

### What is Coupling?

**Coupling** measures how dependent modules are on each other. It describes the degree to which one module relies on another.

**Types of Coupling** (from worst to best):
1. **Content Coupling**: Module A directly modifies data in module B
2. **Common Coupling**: Both modules access/modify global data
3. **Control Coupling**: One module controls flow of another (passing control flags)
4. **Stamp Coupling**: Modules share a data structure but use different parts
5. **Data Coupling**: Modules communicate through function parameters only

**Goal**: Achieve **loose coupling** (high independence)

### What is Cohesion?

**Cohesion** measures how closely the responsibilities within a module are related. It describes the strength of relationships between elements within a module.

**Types of Cohesion** (from worst to best):
1. **Coincidental**: Elements randomly grouped (worst)
2. **Logical**: Elements perform similar operations but are unrelated
3. **Temporal**: Elements activated at same time
4. **Procedural**: Elements follow specific procedure
5. **Communicational**: Elements operate on same data
6. **Sequential**: Output of one is input to another
7. **Functional**: All elements contribute to single task (best)

**Goal**: Achieve **high cohesion** (elements strongly related)

### Why Do They Matter?

| Issue | Cause | Effect |
|-------|-------|--------|
| **High Coupling** | Tight dependencies between modules | Changes ripple; hard to test; code reuse difficult |
| **Low Cohesion** | Unrelated responsibilities mixed | Hard to understand; difficult to maintain |
| **Good Design** | Low coupling + High cohesion | Flexible; testable; reusable; maintainable |

### How Design Patterns Help

**Patterns Reduce Coupling**:
- **Observer**: Subjects don't need to know observer details
- **Factory**: Client doesn't know concrete class types
- **Adapter**: Incompatible modules can work together
- **Strategy**: Client chooses algorithm without knowing details
- **Dependency Inversion**: Depend on abstractions, not concretions

**Patterns Increase Cohesion**:
- **Single Responsibility Principle**: Each class has one reason to change
- **Builder**: Groups complex object creation logic
- **Command**: Groups request-related information
- **Mediator**: Groups communication logic in one place

### Visual Example

```
LOW COHESION + HIGH COUPLING (BAD):
┌──────────────────┐
│ UserManager      │
├──────────────────┤
│ - createUser()   │─────────┐
│ - readFile()     │─────┐   │
│ - parseXML()     │─┐   │   │
│ - encryptData()  │ │   │   │
│ - sendEmail()    │ │   │   │
└──────────────────┘ │   │   │
        ↓            ↓   ↓   ↓
   (Mix of unrelated (Tightly coupled to
    responsibilities) multiple modules)

HIGH COHESION + LOW COUPLING (GOOD):
┌──────────────┐  ┌──────────────┐  ┌──────────────┐
│ UserManager  │  │ FileReader   │  │ Encryptor    │
├──────────────┤  ├──────────────┤  ├──────────────┤
│ -create()    │  │ -read()      │  │ -encrypt()   │
│ -delete()    │  │ -validate()  │  │ -decrypt()   │
│ -update()    │  └──────────────┘  └──────────────┘
└──────────────┘
    (Each has   (Collaborate only
     single     when needed via
     purpose)   clear interfaces)
```

### Practical Metrics

**Good Coupling/Cohesion Indicators**:
- ✓ Classes have single, clear responsibility
- ✓ Methods in a class work on same data
- ✓ Dependencies are explicit and minimal
- ✓ Easy to write unit tests
- ✓ Can reuse classes in other projects
- ✓ Changes in one class don't affect others

**Bad Coupling/Cohesion Indicators**:
- ✗ Classes have multiple unrelated responsibilities
- ✗ Methods don't use shared state
- ✗ Hidden dependencies (tight coupling)
- ✗ Hard to test in isolation
- ✗ Can't reuse classes
- ✗ Change in one class breaks multiple other classes

---

## Next Steps

Each of the following topics covers specific patterns in detail:
- **35_2_Behavioral_Patterns.md** - Observer, State Machine, Strategy, Command, etc.
- **35_3_Creational_Patterns.md** - Singleton, Factory, Builder, Prototype, etc.
- **35_4_Structural_Patterns.md** - Adapter, Bridge, Composite, Decorator, Facade, etc.
- **35_5_Concurrent_Patterns.md** - Thread Pool, Actor, Reactor, Producer-Consumer, etc.

Each topic includes:
- Detailed explanation
- Problem it solves
- Implementation in C++
- Real-world examples
- When to use
- Trade-offs and alternatives
