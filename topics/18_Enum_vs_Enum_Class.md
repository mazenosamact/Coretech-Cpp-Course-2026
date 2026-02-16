# enum vs enum class

## Summary
`enum` and `enum class` (scoped enums) both define named constants, but they differ in scope, type safety, and C++ standard compliance. `enum class` is the modern, safer choice with explicit scoping and can specify underlying type.

## Key Concepts
- **Scope**: enum is unscoped, enum class is scoped
- **Implicit Conversion**: enum converts to int, enum class doesn't
- **Naming**: enum pollutes namespace, enum class doesn't
- **Underlying Type**: enum class can specify (C++11)
- **Type Safety**: enum class is type-safer

## Code Examples

### Basic Comparison
```cpp
#include <iostream>
using namespace std;

// Old style - unscoped
enum Color {
    RED, GREEN, BLUE
};

// Modern style - scoped
enum class Status {
    IDLE, RUNNING, STOPPED
};

int main() {
    Color c = RED;          // No prefix needed
    Status s = Status::IDLE; // Must use prefix
    
    cout << "Color: " << c << endl;        // 0
    cout << "Status: " << (int)s << endl;  // 0 (requires cast)
    
    return 0;
}
```

### Scope Issues with Unscoped enum
```cpp
#include <iostream>
using namespace std;

// Unscoped enum pollutes global namespace
enum FileMode {
    OPEN,
    CLOSE,
    READ
};

enum DatabaseMode {
    // OPEN,  // ERROR: duplicate, conflicts with FileMode::OPEN
    // CLOSE, // ERROR: duplicate
    EXECUTE
};

int main() {
    auto mode1 = OPEN;  // Which OPEN? Ambiguous!
    
    return 0;
}
```

### enum class or scoped enum Prevents Pollution
```cpp
#include <iostream>
using namespace std;

enum class FileMode {
    OPEN,
    CLOSE,
    READ
};

enum class DatabaseMode {
    OPEN,    // OK: scoped to DatabaseMode
    CLOSE,   // OK: scoped to DatabaseMode
    EXECUTE
};

int main() {
    auto mode1 = FileMode::OPEN;
    auto mode2 = DatabaseMode::OPEN;
    
    // No ambiguity!
    cout << "File mode: " << (int)mode1 << endl;
    cout << "DB mode: " << (int)mode2 << endl;
    
    return 0;
}
```

### Implicit Conversion: enum vs enum class
```cpp
#include <iostream>
using namespace std;

enum OldEnum {
    VALUE = 10
};

enum class NewEnum {
    VALUE = 20
};

int main() {
    // Old enum implicitly converts to int
    OldEnum old = VALUE;
    int x = old;  // OK: implicit conversion
    
    cout << "Old enum: " << x << endl;
    
    // enum class requires explicit cast
    NewEnum neu = NewEnum::VALUE;
    // int y = neu;  // ERROR: no implicit conversion
    int y = (int)neu;  // OK: explicit cast
    
    cout << "New enum: " << y << endl;
    
    return 0;
}
```

### Specifying Underlying Type
```cpp
#include <iostream>
using namespace std;

// Specify underlying type (C++11)
enum class ColorByte : unsigned char {
    RED = 0,
    GREEN = 1,
    BLUE = 2
};

enum class PriorityInt : int {
    LOW = -1,
    NORMAL = 0,
    HIGH = 1
};

int main() {
    cout << "Size of ColorByte: " << sizeof(ColorByte) << " bytes" << endl;
    cout << "Size of PriorityInt: " << sizeof(PriorityInt) << " bytes" << endl;
    
    ColorByte c = ColorByte::RED;
    PriorityInt p = PriorityInt::HIGH;
    
    cout << "ColorByte RED: " << (int)c << endl;
    cout << "PriorityInt HIGH: " << (int)p << endl;
    
    return 0;
}
```

### enum class with Iteration
```cpp
#include <iostream>
using namespace std;

enum class Direction {
    NORTH = 0,
    SOUTH = 1,
    EAST = 2,
    WEST = 3
};

int main() {
    // For enum class, need explicit cast for iteration
    for (int i = 0; i <= 3; i++) {
        Direction dir = (Direction)i;
        cout << "Direction: " << i << endl;
    }
    
    return 0;
}
```

### Using enum class in Functions
```cpp
#include <iostream>
using namespace std;

enum class TrafficLight {
    GREEN, YELLOW, RED
};

void handleLight(TrafficLight light) {
    switch (light) {
        case TrafficLight::GREEN:
            cout << "Go!" << endl;
            break;
        case TrafficLight::YELLOW:
            cout << "Caution!" << endl;
            break;
        case TrafficLight::RED:
            cout << "Stop!" << endl;
            break;
    }
}

int main() {
    handleLight(TrafficLight::GREEN);
    
    return 0;
}
```

### Forward Declaration
```cpp
#include <iostream>
using namespace std;

// Forward declaration of enum class (C++11)
enum class Result : int;

// Function prototype
void processResult(Result r);

// Definition
enum class Result : int {
    SUCCESS = 0,
    FAILURE = 1
};

void processResult(Result r) {
    if (r == Result::SUCCESS) {
        cout << "Operation successful" << endl;
    }
}

int main() {
    processResult(Result::SUCCESS);
    return 0;
}
```

### Legacy enum with Explicit Underlying Type
```cpp
#include <iostream>
using namespace std;

// C++11 allows specifying type for unscoped enum too
enum class Color : unsigned short {
    RED = 0,
    GREEN = 65535
};

// But use enum class for clarity
enum class Size : unsigned char {
    SMALL = 0,
    MEDIUM = 1,
    LARGE = 2
};

int main() {
    cout << "Color size: " << sizeof(Color) << endl;
    cout << "Size size: " << sizeof(Size) << endl;
    
    return 0;
}
```

### Pattern: Multiple Enums in Namespace
```cpp
#include <iostream>
using namespace std;

namespace Graphics {
    enum class ColorModel { RGB, CMYK, HSV };
    enum class BlendMode { NORMAL, MULTIPLY, SCREEN };
}

namespace Audio {
    enum class SampleRate { S44_1K, S48K, S96K };
    enum class BitDepth { B16, B24, B32 };
}

int main() {
    Graphics::ColorModel cm = Graphics::ColorModel::RGB;
    Audio::SampleRate sr = Audio::SampleRate::S48K;
    
    cout << "Color model: " << (int)cm << endl;
    cout << "Sample rate: " << (int)sr << endl;
    
    return 0;
}
```

### Helper Functions for enum class
```cpp
#include <iostream>
#include <string>
using namespace std;

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

string logLevelName(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

int main() {
    LogLevel level = LogLevel::INFO;
    cout << "Log level: " << logLevelName(level) << endl;
    
    return 0;
}
```

### Comparison: Old vs Modern Style
```cpp
#include <iostream>
using namespace std;

// OLD STYLE - NOT RECOMMENDED
enum OldGame {
    PAUSED,
    RUNNING,
    ENDED
};

// MODERN STYLE - RECOMMENDED
enum class GameState {
    PAUSED,
    RUNNING,
    ENDED
};

int main() {
    // Old: pollutes namespace, implicit conversion
    OldGame game1 = RUNNING;
    int x = game1;
    
    // New: scoped, no implicit conversion, needs cast
    GameState game2 = GameState::RUNNING;
    // int y = game2;  // ERROR
    int y = (int)game2;
    
    cout << "Old style: " << x << endl;
    cout << "New style: " << y << endl;
    
    return 0;
}
```

## Quick Comparison Table
| Feature | enum | enum class |
|---------|------|-----------|
| Scope | Global namespace | Scoped |
| Prefix required | No | Yes |
| Implicit conversion | Yes | No |
| Specify type | C++11 with `:` | C++11 |
| Forward declare | Only with C++11 | Yes |
| Type safety | Low | High |
| Modern recommendation | No | Yes |

## Best Practices
1. Always use `enum class` in modern C++
2. Always specify underlying type for clarity
3. Use descriptive names within the enum
4. Consider using namespaces with enums
5. Write helper functions for enum-to-string conversion
6. Use enum class for type safety and namespace cleanliness

## Migration from enum to enum class
```cpp
// OLD
enum Status { ACTIVE, INACTIVE };
Status s = ACTIVE;

// NEW
enum class Status { ACTIVE, INACTIVE };
Status s = Status::ACTIVE;
```

The main work is updating all references to use `Status::` prefix.
