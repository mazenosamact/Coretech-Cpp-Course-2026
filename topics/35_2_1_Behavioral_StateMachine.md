# Behavioral Patterns: State Machine Implementation in C++

## Introduction to State Machine Pattern

A **state machine** is a design pattern where an object's behavior changes based on its internal state. The same input can produce different outputs depending on the current state.

### Real-World Examples:
- **Traffic Light**: Red → Green → Yellow → Red
- **Door Lock**: Locked → Unlocked → Locked
- **Media Player**: Stopped → Playing → Paused → Stopped
- **Network Connection**: Connecting → Connected → Disconnecting → Disconnected
- **ATM**: Idle → CardInserted → PinEntered → SelectingOperation → Transaction

### State Machine Terminology:
- **State**: A condition or situation where the system exists
- **Event/Trigger**: External stimulus that causes transition
- **Transition**: Movement from one state to another
- **Action**: Behavior executed during or after transition
- **Guard Condition**: A boolean condition that must be satisfied for a transition to occur
- **Entry Action**: Behavior executed when entering a state (entry action)
- **Exit Action**: Behavior executed when leaving a state (exit action)
- **Initial State**: The starting state when the state machine is created
- **Final/Terminal State**: A state with no outgoing transitions (end state)
- **Context**: The object that manages the current state and processes events

---

## Mealy vs Moore Machines

State machines are classified based on **when actions are executed**:

### Moore Machine
- **Output depends on**: Current state only
- **Actions triggered**: On state **entry** (when entering a state)
- **Output Timing**: Synchronous (changes when state changes)
- **Use When**: Output should reflect the current state
- **Benefits**: Simpler logic, more predictable timing
- **Example**: Traffic light (output is determined solely by which state you're in)

```
Event comes in → Transition to new state → Execute entry action → Output produced
```

### Mealy Machine
- **Output depends on**: Current state AND event received
- **Actions triggered**: On **transition** (when moving between states)
- **Output Timing**: Asynchronous (can change mid-state)
- **Use When**: Output needs to react to specific events
- **Benefits**: Potentially fewer states, more responsive
- **Example**: Elevator controller (action depends on which floor button is pressed and current floor)

```
Event comes in → Transition + Execute transition action → Output produced
```

### Comparison Table

| Aspect | Moore | Mealy |
|--------|-------|-------|
| **Output depends on** | State only | State + Event |
| **When actions execute** | On entry to state | On transition |
| **State diagram** | Labels on circles | Labels on arrows |
| **Complexity** | May need more states | Potentially fewer states |
| **Predictability** | More predictable | Less predictable (depends on events) |
| **Response time** | One cycle | Same cycle as event |
| **Implementation** | State Pattern naturally | Requires transition actions |

### Example Comparison

**Moore Approach (Traffic Light)**:
```cpp
state RED:
    on_entry: turn_on_red_light()  // Output: Red
    on Timer → GREEN

state GREEN:
    on_entry: turn_on_green_light()  // Output: Green
    on Timer → YELLOW
```

**Mealy Approach (Elevator)**:
```cpp
state at_floor_3:
    on Floor_1_Button → goto_floor_1 { 
        descend()  // Output: Start descending
    } = at_floor_1
    
    on Floor_5_Button → goto_floor_5 { 
        ascend()   // Output: Start ascending
    } = at_floor_5
```

### Which to Use?

- **Moore**: Most practical state machines (traffic lights, UI states, game states)
- **Mealy**: Systems where output must react immediately to events (control systems, protocol handlers)
- **Hybrid**: Many real systems combine both approaches

---

## Running Example: Traffic Light State Machine

We'll implement a traffic light system that transitions through states:
```
RED → GREEN → YELLOW → RED
```

With these transitions:
- `onTimer()` triggers RED → GREEN
- `onTimer()` triggers GREEN → YELLOW
- `onTimer()` triggers YELLOW → RED

---

## Approach 1: if-else Anti-Pattern (AVOID THIS)

### Implementation:

```cpp
#include <iostream>
using namespace std;

class TrafficLightBad {
public:
    enum State { RED, GREEN, YELLOW };
    
private:
    State currentState = RED;
    
public:
    void onTimer() {
        if (currentState == RED) {
            cout << "RED → GREEN" << endl;
            currentState = GREEN;
        }
        else if (currentState == GREEN) {
            cout << "GREEN → YELLOW" << endl;
            currentState = YELLOW;
        }
        else if (currentState == YELLOW) {
            cout << "YELLOW → RED" << endl;
            currentState = RED;
        }
        onButton1(){
            if(currentState == RED || currentState == GREEN || currentState == YELLOW)
            {
                currentState = BLUE; 
            }
        }
        onButton2()
        {

        }
    }
    
    void display() {
        if (currentState == RED) {
            cout << "Light is RED - Stop!" << endl;
        }
        else if (currentState == GREEN) {
            cout << "Light is GREEN - Go!" << endl;
        }
        else if (currentState == YELLOW) {
            cout << "Light is YELLOW - Caution!" << endl;
        }
    }
};
```

### Problems:

❌ **Spaghetti Code**: Multiple `if-else` chains scattered throughout class
❌ **Fragile**: Adding new state requires modifying multiple places
❌ **Hard to Test**: State logic is implicit
❌ **Poor Encapsulation**: State information isn't encapsulated
❌ **State Explosion**: With N states and M events, you get N×M conditions
❌ **Debugging Nightmare**: Hard to trace state transitions
❌ **Not Scalable**: Works for 3 states, becomes unmanageable at 20+ states

### When This Happens:
- Quick prototypes
- Learning code
- Very simple state machines (2-3 states, 1 event)
- Code that evolves without refactoring

---

## Approach 2: switch Case Based

### Implementation:

```cpp
#include <iostream>
using namespace std;

class TrafficLightSwitch {
public:
    enum State { RED = 0, GREEN = 1, YELLOW = 2 };
    
private:
    State currentState = RED;
    
public:
    void onTimer() {
        switch (currentState) {
            case RED:
                cout << "RED → GREEN" << endl;
                currentState = GREEN;
                break;
            case GREEN:
                cout << "GREEN → YELLOW" << endl;
                currentState = YELLOW;
                break;
            case YELLOW:
                cout << "YELLOW → RED" << endl;
                currentState = RED;
                break;
        }
    }
    
    void display() {
        switch (currentState) {
            case RED:
                cout << "Light is RED - Stop!" << endl;
                break;
            case GREEN:
                cout << "Light is GREEN - Go!" << endl;
                break;
            case YELLOW:
                cout << "Light is YELLOW - Caution!" << endl;
                break;
        }
    }
};
```

### Advantages:

✓ Better than `if-else`: More readable structure
✓ Slightly better performance: Switch is more efficient
✓ Easier to understand intent: Explicit state handling

### Problems:

❌ **Still Scattered Logic**: State logic still mixed in one class
❌ **Difficult to Extend**: Adding states requires modifying switches
❌ **Duplicate Code**: Same state might appear in multiple switches
❌ **State Actions Lost**: No clear separation of state-specific behavior
❌ **Not Object-Oriented**: Doesn't leverage OOP principles
❌ **Hard to Test**: Can't test state behavior independently

### When to Use:
- Small state machines (< 5 states)
- Very simple transitions
- Performance-critical embedded systems
- One-off implementation

---

## Approach 3: State Pattern (OOP Solution)

### Principle:

Create separate **State classes** that encapsulate behavior for each state. The context delegates to the current state object.

### Implementation:

```cpp
#include <iostream>
#include <memory>
using namespace std;

// Forward declaration
class TrafficLightContext;

// Abstract state
class TrafficLightState {
public:
    virtual ~TrafficLightState() = default;
    
    virtual void onTimer(TrafficLightContext& context) = 0;
    virtual void display() = 0;
    virtual const char* getName() = 0;
    virtual void onButton(TrafficLightContext& context) = 0;
};

// Context class
class TrafficLightContext {
private:
    unique_ptr<TrafficLightState> currentState;
    
public:
    TrafficLightContext();
    
    void setState(unique_ptr<TrafficLightState> newState) {
        currentState = move(newState);
    }
    
    void onTimer() {
        currentState->onTimer(*this);
    }
    
    void display() {
        currentState->display();
    }
};

// Concrete states
class RedState : public TrafficLightState {
public:
    void onTimer(TrafficLightContext& context) override;
    void display() override {
        cout << "Light is RED - Stop!" << endl;
    }
    const char* getName() override { return "RED"; }

    void onButton(TrafficLightContext& context) override
    {
        context.setState(make_unique<BlueState>());
    }
};

class GreenState : public TrafficLightState {
public:
    void onTimer(TrafficLightContext& context) override;
    void display() override {
        cout << "Light is GREEN - Go!" << endl;
    }
    const char* getName() override { return "GREEN"; }
    void onButton(TrafficLightContext& context) override
    {
        context.setState(make_unique<BlueState>());
    }
};

class YellowState : public TrafficLightState {
public:
    void onTimer(TrafficLightContext& context) override;
    void display() override {
        cout << "Light is YELLOW - Caution!" << endl;
    }
    const char* getName() override { return "YELLOW"; }
    void onButton(TrafficLightContext& context) override
    {
        if(/** guard condition if exists*/)
        {
            context.setState(make_unique<GreenState>());
        }
        this->onExit();
        context.setState(make_unique<BlueState>());
        context.currentState.onEntry();
    }
};

class BlueState : public TrafficLightState {
public:
    void onTimer(TrafficLightContext& context) override;
    void display() override {
        cout << "Light is YELLOW - Caution!" << endl;
    }
    const char* getName() override { return "YELLOW"; }
};


// Transitions
void RedState::onTimer(TrafficLightContext& context) {
    cout << "RED → GREEN" << endl;
    context.setState(make_unique<GreenState>());
}

void GreenState::onTimer(TrafficLightContext& context) {
    cout << "GREEN → YELLOW" << endl;
    context.setState(make_unique<YellowState>());
}

void YellowState::onTimer(TrafficLightContext& context) {
    cout << "YELLOW → RED" << endl;
    context.setState(make_unique<RedState>());
}

// Context constructor
TrafficLightContext::TrafficLightContext() : currentState(make_unique<RedState>()) {}

// Usage
int main() {
    TrafficLightContext light;
    
    light.display();  // RED - Stop!
    light.onTimer();  // RED → GREEN
    light.display();  // GREEN - Go!
    light.onTimer();  // GREEN → YELLOW
    
    light.display();  // YELLOW - Caution!
    light.onTimer();  // YELLOW → RED
    
    return 0;
}
```

### Advantages:

✓ **Clean Separation**: Each state is a separate class
✓ **Open/Closed Principle**: Open for extension, closed for modification
✓ **Easy to Test**: Each state can be tested independently
✓ **Self-Contained**: State logic is encapsulated
✓ **Flexible**: Easy to add new states without modifying existing code
✓ **OOP Best Practices**: Leverages polymorphism

### Problems:

❌ **Class Explosion**: Many classes for complex state machines
❌ **Memory Overhead**: Dynamic allocation for each state object
❌ **Definition Scattered**: Different files for different states
❌ **Verbose**: More boilerplate code than other approaches
❌ **Transition Logic Hidden**: Transitions are in state classes, not grouped together
❌ **Hard to Visualize**: State diagram not obvious from code

### When to Use:
- Medium complexity state machines (5-20 states)
- Need to unit test state behavior
- Team familiar with OOP patterns
- Long-term maintenance important
- Reusable state classes across projects

---

## Approach 4: State Transition Table (STL Containers)

### Principle:

Define states and transitions in **declarative data structures** instead of procedural code. The engine processes the table.

### Implementation:

```cpp
#include <iostream>
#include <map>
#include <functional>
#include <string>
using namespace std;

class TrafficLightTable {
public:
    enum State { RED, GREEN, YELLOW };
    enum Event { TIMER };
    
private:
    State currentState = RED;
    
    // State names for debugging
    map<State, string> stateNames = {
        {RED, "RED"},
        {GREEN, "GREEN"},
        {YELLOW, "YELLOW"}
    };
    
    // Transition table: (CurrentState, Event) → NextState
    map<pair<State, Event>, State> transitionTable = {
        {{RED, TIMER}, GREEN},        // RED + TIMER → GREEN
        {{GREEN, TIMER}, YELLOW},     // GREEN + TIMER → YELLOW
        {{YELLOW, TIMER}, RED}        // YELLOW + TIMER → RED
    };
    
    // Action table: (CurrentState, Event) → Action
    map<pair<State, Event>, function<void()>> actionTable = {
        {{RED, TIMER}, [this]() { cout << "RED → GREEN" << endl; }},
        {{GREEN, TIMER}, [this]() { cout << "GREEN → YELLOW" << endl; }},
        {{YELLOW, TIMER}, [this]() { cout << "YELLOW → RED" << endl; }}
    };
    
    // Entry actions: triggered when entering a state
    map<State, function<void()>> entryActions = {
        {RED, [this]() { cout << "Entering RED - Stop!" << endl; }},
        {GREEN, [this]() { cout << "Entering GREEN - Go!" << endl; }},
        {YELLOW, [this]() { cout << "Entering YELLOW - Caution!" << endl; }}
    };
    
public:
    void onTimer() {
        auto transitionKey = make_pair(currentState, TIMER);
        
        // Check if transition exists
        if (transitionTable.find(transitionKey) != transitionTable.end()) {
            // Execute action
            if (actionTable.find(transitionKey) != actionTable.end()) {
                actionTable[transitionKey]();  // Transition action
            }
            
            // Perform transition
            State nextState = transitionTable[transitionKey];
            currentState = nextState;
            
            // Execute entry action for new state
            if (entryActions.find(currentState) != entryActions.end()) {
                entryActions[currentState]();
            }
        } else {
            cout << "Invalid transition from " << stateNames[currentState] << endl;
        }
    }
    
    void display() {
        cout << "Current state: " << stateNames[currentState] << endl;
    }
};

// Usage
int main() {
    TrafficLightTable light;
    
    light.display();   // RED
    light.onTimer();   // RED → GREEN, Entering GREEN - Go!
    
    light.display();   // GREEN
    light.onTimer();   // GREEN → YELLOW, Entering YELLOW - Caution!
    
    light.display();   // YELLOW
    light.onTimer();   // YELLOW → RED, Entering RED - Stop!
    
    return 0;
}
```

### Advantages:

✓ **Data-Driven**: Transitions are data, not code
✓ **Declarative**: Clear specification of state machine behavior
✓ **Easy to Visualize**: Complete state diagram in one place
✓ **Simple to Extend**: Add rows to tables for new transitions
✓ **Entry/Exit Actions**: Built-in entry and exit behaviors
✓ **Error Handling**: Invalid transitions are handled centrally
✓ **Testable**: State machine logic can be verified against table
✓ **No Class Explosion**: Single class implementation

### Problems:

❌ **Complex for Large State Machines**: Thousands of transitions hard to manage
❌ **Guard Conditions Hard**: Hard to express conditional transitions
❌ **Hierarchical States Difficult**: Hard to implement substates
❌ **Debugging**: Large maps can be hard to debug
❌ **Performance**: Map lookups slower than direct method calls
❌ **Not Object-Oriented**: Procedural approach

### When to Use:
- Clear, finite transition tables
- Need to modify transitions at runtime
- Desire a declarative state machine specification
- Different teams: one defines states, another implements actions
- Medium complexity (20-100 states)
- Transitions are simple (no complex guards)

---

### Using `boost::SML` (State Machine Library)

#### Overview:

**Boost.SML** is a modern C++ library providing:
- Type-safe state machine declaration
- Header-only library (easy integration)
- No runtime overhead (compiles to state machine)
- Expressive C++ syntax (lambda-based)
- Automatic diagram generation (Graphviz)
- Support for hierarchical states
- C++14 compatible

#### Traffic Light Example with boost::SML:

```cpp
#include <boost/sml.hpp>
#include <iostream>

namespace sml = boost::sml;
using namespace std;

// State definitions
struct Red {};
struct Green {};
struct Yellow {};

// Events
struct Timer {};

// State machine definition
struct TrafficLightSML {
    auto operator()() const {
        return sml::make_transition_table(
            // From state RED
            *sml::state<Red> + sml::event<Timer> / [this] { 
                cout << "RED → GREEN" << endl;
                cout << "Entering GREEN - Go!" << endl;
            } = sml::state<Green>,
            
            // From state GREEN
            sml::state<Green> + sml::event<Timer> / [this] { 
                cout << "GREEN → YELLOW" << endl;
                cout << "Entering YELLOW - Caution!" << endl;
            } = sml::state<Yellow>,
            
            // From state YELLOW
            sml::state<Yellow> + sml::event<Timer> / [this] { 
                cout << "YELLOW → RED" << endl;
                cout << "Entering RED - Stop!" << endl;
            } = sml::state<Red>
        );
    }
};

// Usage
int main() {
    sml::sm<TrafficLightSML> light;  // Create state machine
    
    cout << "Initial state: " << light.current() << endl;  // Shows state index
    
    light.process_event(Timer());  // RED → GREEN
    light.process_event(Timer());  // GREEN → YELLOW
    light.process_event(Timer());  // YELLOW → RED
    
    return 0;
}

// Output:
// Initial state: 0 (Red)
// RED → GREEN
// Entering GREEN - Go!
// GREEN → YELLOW
// Entering YELLOW - Caution!
// YELLOW → RED
// Entering RED - Stop!
```

#### More Advanced Example with Entry/Exit Actions:

```cpp
#include <boost/sml.hpp>
#include <iostream>

namespace sml = boost::sml;
using namespace std;

struct Red {
    template<typename Event, typename SM>
    void on_entry(Event const&, SM&) const {
        cout << "[RED::on_entry] LED is OFF, traffic stops" << endl;
    }
    
    template<typename Event, typename SM>
    void on_exit(Event const&, SM&) const {
        cout << "[RED::on_exit] Preparing for next phase" << endl;
    }
};

struct Green {
    template<typename Event, typename SM>
    void on_entry(Event const&, SM&) const {
        cout << "[GREEN::on_entry] LED is ON, traffic goes" << endl;
    }
    
    template<typename Event, typename SM>
    void on_exit(Event const&, SM&) const {
        cout << "[GREEN::on_exit] Countdown to yellow" << endl;
    }
};

struct Yellow {
    template<typename Event, typename SM>
    void on_entry(Event const&, SM&) const {
        cout << "[YELLOW::on_entry] LED is ON, prepare to stop" << endl;
    }
    
    template<typename Event, typename SM>
    void on_exit(Event const&, SM&) const {
        cout << "[YELLOW::on_exit] Clearing intersection" << endl;
    }
};

struct Timer {};

struct TrafficLightAdvanced {
    auto operator()() const {
        return sml::make_transition_table(
            *sml::state<Red> + sml::event<Timer> 
                = sml::state<Green>,
            
            sml::state<Green> + sml::event<Timer> 
                = sml::state<Yellow>,
            
            sml::state<Yellow> + sml::event<Timer> 
                = sml::state<Red>
        );
    }
};

int main() {
    sml::sm<TrafficLightAdvanced> light;
    
    cout << "\n=== Transition 1: Timer ===\n";
    light.process_event(Timer());
    
    cout << "\n=== Transition 2: Timer ===\n";
    light.process_event(Timer());
    
    cout << "\n=== Transition 3: Timer ===\n";
    light.process_event(Timer());
    
    return 0;
}

// Output:
// === Transition 1: Timer ===
// [RED::on_exit] Preparing for next phase
// [GREEN::on_entry] LED is ON, traffic goes
// 
// === Transition 2: Timer ===
// [GREEN::on_exit] Countdown to yellow
// [YELLOW::on_entry] LED is ON, prepare to stop
// 
// === Transition 3: Timer ===
// [YELLOW::on_exit] Clearing intersection
// [RED::on_entry] LED is OFF, traffic stops
```

#### Example with Guard Conditions:

```cpp
#include <boost/sml.hpp>
#include <iostream>

namespace sml = boost::sml;
using namespace std;

struct Red {};
struct Green {};
struct Yellow {};

struct Timer {
    int duration;
};

struct TrafficLightGuard {
    auto operator()() const {
        return sml::make_transition_table(
            *sml::state<Red> + sml::event<Timer> 
                [ [](Timer const& t) { return t.duration > 30; } ] 
                = sml::state<Green>,
            
            sml::state<Red> + sml::event<Timer> 
                [ [](Timer const& t) { return t.duration <= 30; } ] 
                = sml::state<Red>,  // Stay in Red
            
            sml::state<Green> + sml::event<Timer> 
                [ [](Timer const& t) { return t.duration > 25; } ] 
                = sml::state<Yellow>,
            
            sml::state<Yellow> + sml::event<Timer> 
                = sml::state<Red>
        );
    }
};

int main() {
    sml::sm<TrafficLightGuard> light;
    
    cout << "Timer 20s (no transition): ";
    light.process_event(Timer{20});  // Stays in Red
    
    cout << "Timer 35s (Red → Green): ";
    light.process_event(Timer{35});  // Transitions to Green
    
    return 0;
}
```

#### Advantages:

✓ **Modern C++**: Uses C++14 features (lambdas, type deduction)
✓ **Type-Safe**: Compile-time state/event checking
✓ **Header-Only**: No compilation needed, easy integration
✓ **Zero Runtime Overhead**: Compiles to optimized state machine
✓ **Expressive Syntax**: Clear declaration of transitions
✓ **Entry/Exit Actions**: Built-in state callbacks
✓ **Guard Conditions**: Lambda-based conditional transitions
✓ **Automatic Visualization**: Can generate Graphviz diagrams
✓ **Hierarchical States**: Supports composite states (substates)
✓ **Small Code Size**: More compact than hand-written state patterns

#### Disadvantages:

❌ **Learning Curve**: Unfamiliar syntax for many developers
❌ **Compiler Support**: Requires C++14 or later
❌ **Error Messages**: Template errors can be verbose
❌ **Boost Dependency**: Requires Boost library installation
❌ **Documentation**: Less documentation than SMC or Sinelabore
❌ **Visual Editing**: No graphical editor (must code manually)

#### When to Use:

✓ Modern C++ projects (C++14+)
✓ Header-only library preferred
✓ Type safety important
✓ Need automatic code generation from declaration
✓ Want to integrate state machine directly in C++ code
✓ Header-only Boost library available
✓ Medium to complex state machines (5-50 states)

#### Generating State Diagram with boost::SML:

```cpp
#include <boost/sml.hpp>
#include <iostream>
#include <fstream>

namespace sml = boost::sml;

struct Red {};
struct Green {};
struct Yellow {};
struct Timer {};

struct TrafficLight {
    auto operator()() const {
        return sml::make_transition_table(
            *sml::state<Red> + sml::event<Timer> = sml::state<Green>,
            sml::state<Green> + sml::event<Timer> = sml::state<Yellow>,
            sml::state<Yellow> + sml::event<Timer> = sml::state<Red>
        );
    }
};

int main() {
    // Generate diagram
    std::ofstream diagram("traffic_light.dot");
    diagram << sml::visit(boost::sml::sm<TrafficLight>{});
    
    // Generates Graphviz DOT format - visualize with:
    // dot -Tpng traffic_light.dot -o traffic_light.png
    
    return 0;
}
```

---

## Approach 5: Tool-Based State Machine Generators

### Introduction

Using **dedicated tools** to generate state machine code from visual diagrams.

### Option A: SMC (State Machine Compiler)

#### Overview:
- Reads `.sm` (state machine) files
- Generates C++ code automatically
- Supports entry/exit actions, guards, transitions

#### SMC Syntax:

```
// traffic_light.sm
FSMClass TrafficLight
{
    Red
    {
        Timer => Green { onRedToGreen(); }
    }
    
    Green
    {
        Timer => Yellow { onGreenToYellow(); }
    }
    
    Yellow
    {
        Timer => Red { onYellowToRed(); }
    }
}
```

#### Generating C++ Code:
```bash
smc.pl -c++ traffic_light.sm
# Generates: traffic_light.h, traffic_light.cpp
# Also generates: traffic_lightContext.h, traffic_lightContext.cpp
```

#### Using Generated Code:

```cpp
#include "TrafficLightContext.h"

class TrafficLightImpl : public TrafficLightContext {
private:
    void onRedToGreen() { cout << "RED → GREEN" << endl; }
    void onGreenToYellow() { cout << "GREEN → YELLOW" << endl; }
    void onYellowToRed() { cout << "YELLOW → RED" << endl; }
    
public:
    void onTimer() {
        Timer(*this);  // Call SMC-generated method
    }
};

int main() {
    TrafficLightImpl light;
    light.enterStartState();  // Enter initial state
    
    light.onTimer();  // RED → GREEN (SMC handles transition)
    light.onTimer();  // GREEN → YELLOW
    light.onTimer();  // YELLOW → RED
    
    return 0;
}
```

### Option B: Sinelabore

#### Overview:
- Visual graphical editor
- Generates C, C++, C#, Java code
- Supports hierarchical states
- Better suited for complex state machines

#### Features:
- Drag-and-drop state creation
- Visual transitions
- Entry/exit actions with code snippets
- Guard conditions
- History states (substates)
- Generates complete, compilable code

#### Workflow:
1. Open Sinelabore
2. Create states visually
3. Draw transitions
4. Add entry/exit code
5. Generate C++ code
6. Integrate into your project

#### Example Generated Code Structure:
```cpp
// From Sinelabore FSM editor
class TrafficLightFSM {
private:
    enum State { s_red, s_green, s_yellow };
    State currentState;
    
public:
    void processEvent(Event e) {
        switch(currentState) {
            case s_red:
                if (e == Timer) {
                    exit_red();
                    currentState = s_green;
                    entry_green();
                }
                break;
            case s_green:
                if (e == Timer) {
                    exit_green();
                    currentState = s_yellow;
                    entry_yellow();
                }
                break;
            case s_yellow:
                if (e == Timer) {
                    exit_yellow();
                    currentState = s_red;
                    entry_red();
                }
                break;
        }
    }

private:
    void entry_red() { /* user code */ }
    void exit_red() { /* user code */ }
    void entry_green() { /* user code */ }
    void exit_green() { /* user code */ }
    void entry_yellow() { /* user code */ }
    void exit_yellow() { /* user code */ }
};
```

### Tool-Based Advantages:

✓ **Visual Specification**: State machine as diagram
✓ **Auto-Generated Code**: Less manual coding
✓ **Hierarchical States**: Support for nested/composite states
✓ **Guard Conditions**: Easy to express conditional transitions
✓ **Documentation**: Diagram serves as documentation
✓ **Validation**: Tools check for unreachable states, missing transitions
✓ **Multiple Languages**: Generate C++, C, Python, Java from same diagram
✓ **Team Communication**: Non-developers can understand diagrams

### Tool-Based Problems:

❌ **License Costs**: Professional tools can be expensive (Sinelabore ~$200-1000)
❌ **Learning Curve**: Need to learn tool-specific syntax
❌ **Generated Code Quality**: May not match coding standards
❌ **Modifications Overwritten**: Manual edits lost when regenerating
❌ **Version Control**: Hard to diff generated code
❌ **Integration**: Need build system integration
❌ **Debugging**: Harder to debug generated code
❌ **Overkill for Simple Cases**: Too much overhead for trivial state machines

### Open Source Alternatives:

**Free Options**:
- **SMC (State Machine Compiler)**: Open source, lightweight
- **YAKINDU Statechart Tools**: Free Eclipse plugin with code generation
- **Graphviz**: Visualize state diagrams (not generation, but documentation)
- **Plc_open**: IEC 61131-3 standard tools

---

## Approach 6: SCXML (State Chart XML)

### Introduction to SCXML

**SCXML (State Chart XML)** is a standardized XML format for describing state machines and statecharts based on W3C standards. It provides a platform-independent, human-readable way to define complex state machines that can be executed, visualized, or used to generate code.

### What is SCXML?

- **Standard Format**: W3C recommendation for state machine definition
- **XML-Based**: Human-readable, text-based format
- **Platform-Independent**: Not tied to any programming language
- **Executable**: Many SCXML engines can directly execute state machines
- **Tool-Neutral**: Can be used across different tools and platforms

### Basic SCXML Syntax:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<scxml xmlns="http://www.w3.org/2005/07/scxml" version="1.0" initial="red">
    <state id="red">
        <transition event="timer" target="green" />
    </state>
    
    <state id="green">
        <transition event="timer" target="yellow" />
    </state>
    
    <state id="yellow">
        <transition event="timer" target="red" />
    </state>
</scxml>
```

### Traffic Light Example in SCXML:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<scxml xmlns="http://www.w3.org/2005/07/scxml" 
       xmlns:cc="http://commonsensemedia.org/scxml"
       version="1.0" 
       initial="red">
    
    <!-- RED state -->
    <state id="red">
        <onentry>
            <log expr="'Entering RED - Stop!'" />
        </onentry>
        
        <onexit>
            <log expr="'Leaving RED state'" />
        </onexit>
        
        <transition event="timer" target="green">
            <log expr="'RED → GREEN'" />
        </transition>
    </state>
    
    <!-- GREEN state -->
    <state id="green">
        <onentry>
            <log expr="'Entering GREEN - Go!'" />
        </onentry>
        
        <onexit>
            <log expr="'Leaving GREEN state'" />
        </onexit>
        
        <transition event="timer" target="yellow">
            <log expr="'GREEN → YELLOW'" />
        </transition>
    </state>
    
    <!-- YELLOW state -->
    <state id="yellow">
        <onentry>
            <log expr="'Entering YELLOW - Caution!'" />
        </onentry>
        
        <onexit>
            <log expr="'Leaving YELLOW state'" />
        </onexit>
        
        <transition event="timer" target="red">
            <log expr="'YELLOW → RED'" />
        </transition>
    </state>
</scxml>
```

### SCXML Features:

**Core Elements**:
- `<scxml>`: Root element defining the state machine
- `<state>`: Defines a state
- `<transition>`: Defines state transitions
- `<onentry>`: Actions executed when entering a state
- `<onexit>`: Actions executed when leaving a state
- `<history>`: Saves state history (for substates)

**Advanced Features**:
- **Hierarchical States**: Nested state definitions for complex machines
- **Guards**: Conditional transitions with `<cond>`
- **Parallel States**: Multiple active states simultaneously
- **Final States**: Terminal states using `<final>`
- **Variables**: Local state machine variables with `<datamodel>`
- **Custom Actions**: Extensible action language (ECMAScript, etc.)

### SCXML with Guard Conditions:

```xml
<scxml xmlns="http://www.w3.org/2005/07/scxml" version="1.0" initial="red">
    <datamodel>
        <data id="counter" expr="0" />
    </datamodel>
    
    <state id="red">
        <transition event="timer" cond="counter > 30" target="green">
            <assign location="counter" expr="counter + 1" />
        </transition>
        
        <transition event="timer" cond="counter &lt;= 30" target="red">
            <assign location="counter" expr="counter + 1" />
        </transition>
    </state>
    
    <state id="green">
        <transition event="timer" target="yellow" />
    </state>
    
    <state id="yellow">
        <transition event="timer" target="red" />
    </state>
</scxml>
```

### Advantages of SCXML:

✓ **Standardized Format**: W3C standard, universally recognized
✓ **Platform-Independent**: Works across languages and platforms
✓ **Readable**: XML is human-readable and version-control friendly
✓ **Tool Support**: Many tools support SCXML input/output
✓ **Executable**: Engines can run SCXML directly without translation
✓ **Hierarchical**: Natural support for complex nested states
✓ **Rich Features**: Guards, parallel states, history mechanisms
✓ **Documentation**: Format itself documents the state machine
✓ **Code Generation**: Multiple generators available (C++, Java, Python)

### Disadvantages of SCXML:

❌ **Verbose**: More verbose than programmatic definitions
❌ **Learning Curve**: XML syntax and SCXML semantics to learn
❌ **Parsing Overhead**: Runtime XML parsing may have performance cost
❌ **Limited Tooling**: Fewer integrated development tools than commercial solutions
❌ **Debugging**: Harder to debug at development time
❌ **Manual Editing**: Prone to XML syntax errors

### Tools Supporting SCXML:

#### SCXML Engines and Generators:

1. **Apache Commons SCXML** (Java)
   - Open-source SCXML engine
   - Executes SCXML directly
   - Can generate Java code

2. **libscxml** (C/C++)
   - Open-source SCXML interpreter
   - For embedded and real-time systems
   - Direct SCXML execution in C/C++

3. **YAKINDU Statechart Tools**
   - Visual editor with SCXML export
   - Code generation for C++, Java, Python
   - Free Eclipse plugin

4. **PlantUML**
   - Generates diagrams from SCXML
   - Can also generate SCXML from visual descriptions
   - Open-source

5. **Qt State Machine Framework**
   - Qt's built-in state machine support
   - Can load and execute SCXML files
   - C++ framework with Qt integration

6. **Mоткровения SCXML Editor**
   - Web-based SCXML editor
   - Visual state machine design
   - Real-time preview

#### Code Generation from SCXML:

```bash
# Using YAKINDU to generate C++ from SCXML
yakindu-statechart-compiler -model traffic_light.scxml -outlet cpp

# Using libscxml (direct execution)
scxml_interpreter traffic_light.scxml

# Using custom code generators
scxml-to-cpp traffic_light.scxml --output traffic_light.hpp
```

### Using SCXML with C++:

```cpp
#include <scxml/scxml.hpp>  // Hypothetical SCXML C++ library

int main() {
    // Load SCXML file
    scxml::StateMachine machine("traffic_light.scxml");
    
    // Initialize
    machine.init();
    
    // Process events
    machine.send(scxml::Event("timer"));  // RED → GREEN
    machine.send(scxml::Event("timer"));  // GREEN → YELLOW
    machine.send(scxml::Event("timer"));  // YELLOW → RED
    
    // Check current state
    if (machine.isInState("green")) {
        std::cout << "Light is green!" << std::endl;
    }
    
    return 0;
}
```

### When to Use SCXML:

✓ **Standard Format Required**: When standardization is important
✓ **Multi-Language Projects**: Same SCXML used for C++, Java, Python
✓ **Complex Hierarchical States**: Excellent for nested state machines
✓ **Tool Chain Independence**: Want flexibility in tool choices
✓ **Long-Term Maintenance**: Format is standardized and documented
✓ **Team Collaboration**: Non-programmers can review SCXML
✓ **Regulatory Compliance**: Documentation requirements for safety-critical systems

### SCXML vs Other Approaches:

| Aspect | SCXML | SMC | Sinelabore | boost::SML |
|--------|-------|-----|-----------|-----------|
| **Standard** | Yes (W3C) | No | No | No |
| **Format** | XML | Text | Binary/Visual | C++ code |
| **Tool Support** | Multiple | Limited | Proprietary | Boost ecosystem |
| **Verbosity** | High | Medium | Low | Low |
| **Code Generation** | Yes | Yes | Yes | N/A (C++ native) |
| **Multi-Language** | Yes | No | Yes | C++ only |
| **Learning Curve** | Moderate | Easy | Medium | Moderate |
| **Direct Execution** | Yes | No | No | Yes |

---

## Comparison Table

```
Approach           | Complexity | Performance | Maintainability | Scalability | Learning
================================================================================
1. if-else         | Trivial    | Slow        | Poor            | 1-3 states  | Instant
2. switch          | Simple     | Moderate    | Fair            | 3-5 states  | Easy
3. State Pattern   | Moderate   | Good        | Excellent       | 5-20 states | Moderate
4. STL Table       | Moderate   | Good        | Excellent       | 20-100 states | Moderate
5. SMC/Sinelabore  | High       | Excellent   | Excellent       | 100+ states | Hard
```

---

## Detailed Comparison: Feature Matrix

| Feature | if-else | switch | State Pattern | STL Table | SMC | Sinelabore |
|---------|---------|--------|---------------|-----------|-----|-----------|
| **Readability** | Poor | Fair | Good | Good | Good | Excellent |
| **Extensibility** | Hard | Hard | Easy | Easy | Easy | Easy |
| **Entry/Exit Actions** | Manual | Manual | Built-in | Built-in | Auto | Auto |
| **Guard Conditions** | Hard | Hard | Easy | Medium | Built-in | Built-in |
| **Hierarchical States** | No | No | No | No | Yes | Yes |
| **Visual Diagram** | None | None | None | Table | Auto | Interactive |
| **Code Generation** | No | No | No | No | Yes | Yes |
| **Unit Testable** | Hard | Medium | Easy | Easy | Fair | Fair |
| **Runtime Modification** | Hard | Hard | Hard | Yes | No | No |
| **Memory Efficient** | Best | Best | Good | Good | Excellent | Excellent |
| **Suitable for Embedded** | Yes | Yes | Yes | Yes | Yes | Medium |
| **IDE Integration** | Any | Any | Any | Any | Limited | Good |

---

## Decision Tree: Which Approach to Use?

```
START: Need a state machine?
│
├─ How complex? (number of states)
│  │
│  ├─ 2-3 states
│  │  └─→ Is it a one-time throwaway?
│  │     ├─ Yes → Use if-else or switch
│  │     └─ No  → Use State Pattern
│  │
│  ├─ 4-15 states
│  │  └─→ Need runtime modification?
│  │     ├─ Yes → Use STL Table
│  │     └─ No  → Use State Pattern
│  │
│  ├─ 16-50 states
│  │  └─→ Need hierarchical states?
│  │     ├─ Yes → Use SMC or Sinelabore
│  │     └─ No  → Use STL Table
│  │
│  └─ 50+ states with complex guards
│     └─→ Use SMC or Sinelabore (with visual editor)
```

---

## Real-World Examples: What Powers Use

### State Pattern
- Game engines (character states: idle, walking, running, jumping)
- UI frameworks (widget states: normal, hover, pressed, disabled)
- Telecom (call states: idle, dialing, ringing, connected)

### STL Table
- Network protocols (connection states)
- Industrial controllers (machine states)
- Robotics (robot arm states)

### SMC/Sinelabore
- Automotive (vehicle state machines: 50+ states)
- Aerospace (aircraft control systems)
- Medical devices (operation state machines)
- Complex embedded systems

---

## Best Practices

### 1. **Start Simple**
   - Begin with switch case or State Pattern
   - Graduate to tables/tools as complexity grows

### 2. **Document Transitions**
   - Always include a state diagram
   - Document expected behavior for each state

### 3. **Handle Invalid Transitions**
   - Explicitly define what happens for invalid events
   - Log warnings or assert on unexpected transitions

### 4. **Use Entry/Exit Actions**
   - Trigger initialization on state entry
   - Clean up on state exit
   - Reduces bugs from forgotten initialization

### 5. **Test State Transitions**
   - Test each transition independently
   - Test invalid transitions
   - Test entry/exit actions

### 6. **Guard Conditions**
   - Keep guards simple and testable
   - Document why a transition is guarded

### 7. **Avoid State Explosion**
   - Use hierarchical states for complex systems
   - Consider combining related states

### 8. **Performance Considerations**
   - For real-time systems: prefer switch or generated code
   - For event-driven: STL table is acceptable
   - Avoid virtual function calls in time-critical paths

---

## Hybrid Approach: Combining Strategies

### For Complex Embedded Systems:

```cpp
// Top-level: SMC/Sinelabore for overall system
// Level 2: STL table for subsystem states
// Level 3: State Pattern for complex state behaviors

// Example: Network interface
// - SMC: Connection lifecycle (Disconnected → Connecting → Connected → Reconnecting)
// - STL Table: Packet processing states (Idle → Receiving → Processing → Sending)
// - State Pattern: Each packet processing state can have complex logic
```

---

## Summary: When to Use Each Approach

| Approach | Best For | Avoid If |
|----------|----------|----------|
| **if-else** | Quick prototypes only | Complexity grows |
| **switch** | Small, simple state machines | More than 5 states |
| **State Pattern** | Reusable, testable, medium complexity | Class explosion becomes issue |
| **STL Table** | Data-driven, configurable state machines | Hierarchical states needed |
| **SMC** | Free, lightweight, good balance | Budget for commercial tool |
| **Sinelabore** | Complex visual systems, professional | Simple state machines, cost concerns |

---

## Next Steps

Choose an approach based on:
1. Current complexity
2. Expected growth
3. Team expertise
4. Performance requirements
5. Maintenance burden

For professional C++ projects: **Start with State Pattern → Migrate to STL Table → Use Tools for 50+ states**

For embedded systems: **Start with switch case → Move to State Pattern → Tools only if essential**
