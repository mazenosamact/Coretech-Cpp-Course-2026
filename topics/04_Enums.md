# Enums (C Concepts)

## Summary
An enum (enumeration) is a data type that defines a set of named integer constants. Enums provide a way to create a collection of related constants with meaningful names, improving code readability and maintainability.

## Key Concepts
- **Named Constants**: Each enum value has a meaningful name
- **Underlying Type**: By default, enum values are integers
- **Scope**: Enums can be global or local
- **Default Values**: Start from 0 and increment by 1 (customizable)

## Code Examples

### Basic Enum Declaration
```cpp
#include <iostream>
using namespace std;

enum Color { RED, GREEN, BLUE };

int main() {
    Color myColor = RED;
    
    cout << "Red value: " << RED << endl;       // 0
    cout << "Green value: " << GREEN << endl;   // 1
    cout << "Blue value: " << BLUE << endl;     // 2
    
    return 0;
}
```

### Enum with Custom Values
```cpp
#include <iostream>
using namespace std;

enum Status {
    OFFLINE = 0,
    ONLINE = 1,
    INACTIVE = 2,
    SUSPENDED = 3
};

enum Direction {
    NORTH = 1,
    SOUTH = 2,
    EAST = 4,
    WEST = 8
};

int main() {
    Status currentStatus = ONLINE;
    Direction heading = NORTH;
    
    cout << "Status value: " << currentStatus << endl;      // 1
    cout << "Direction value: " << heading << endl;         // 1
    
    return 0;
}
```

### Enum in Switch Statement
```cpp
#include <iostream>
using namespace std;

enum TrafficLight { GREEN, YELLOW, RED };

void action(TrafficLight light) {
    switch (light) {
        case GREEN:
            cout << "Go!" << endl;
            break;
        case YELLOW:
            cout << "Prepare to stop!" << endl;
            break;
        case RED:
            cout << "Stop!" << endl;
            break;
    }
}

int main() {
    action(GREEN);
    action(YELLOW);
    action(RED);
    
    return 0;
}
```

### Enum with Strings
```cpp
#include <iostream>
#include <string>
using namespace std;

enum Season { SPRING, SUMMER, FALL, WINTER };

string seasonName(Season s) {
    switch (s) {
        case SPRING: return "Spring";
        case SUMMER: return "Summer";
        case FALL: return "Fall";
        case WINTER: return "Winter";
        default: return "Unknown";
    }
}

int main() {
    Season currentSeason = SUMMER;
    cout << "Current season: " << seasonName(currentSeason) << endl;
    
    return 0;
}
```

### Enum in Structures
```cpp
#include <iostream>
using namespace std;

enum UserRole { ADMIN, USER, GUEST };

struct Account {
    char username[50];
    UserRole role;
    int loginCount;
};

int main() {
    Account acc1 = {"john", ADMIN, 150};
    Account acc2 = {"guest", GUEST, 5};
    
    cout << "User: " << acc1.username << endl;
    cout << "Role: " << acc1.role << endl;  // 0
    cout << "Guest role value: " << acc2.role << endl;  // 2
    
    return 0;
}
```

### Enum Arithmetic
```cpp
#include <iostream>
using namespace std;

enum Month {
    JANUARY = 1, FEBRUARY = 2, MARCH = 3, APRIL = 4,
    MAY = 5, JUNE = 6, JULY = 7, AUGUST = 8,
    SEPTEMBER = 9, OCTOBER = 10, NOVEMBER = 11, DECEMBER = 12
};

int main() {
    Month m = MARCH;
    
    cout << "March is month: " << m << endl;
    
    // Advance to next month
    m = (Month)(m + 1);
    cout << "Next month is: " << m << endl;
    
    if (m > JULY) {
        cout << "It's in the second half of the year!" << endl;
    }
    
    return 0;
}
```

### Enum as Flags/Bitmask
```cpp
#include <iostream>
using namespace std;

enum Permissions {
    NONE = 0,
    READ = 1,
    WRITE = 2,
    EXECUTE = 4
};

int main() {
    int userPerms = READ | WRITE;  // Combine permissions
    
    cout << "User permissions value: " << userPerms << endl;
    
    if (userPerms & READ) {
        cout << "User can read" << endl;
    }
    if (userPerms & WRITE) {
        cout << "User can write" << endl;
    }
    if (!(userPerms & EXECUTE)) {
        cout << "User cannot execute" << endl;
    }
    
    return 0;
}
```

### Typedef with Enum
```cpp
#include <iostream>
using namespace std;

typedef enum {
    SUNDAY = 0,
    MONDAY = 1,
    TUESDAY = 2,
    WEDNESDAY = 3,
    THURSDAY = 4,
    FRIDAY = 5,
    SATURDAY = 6
} DayOfWeek;

int main() {
    DayOfWeek today = FRIDAY;
    
    cout << "Today is day " << today << endl;
    
    if (today == FRIDAY) {
        cout << "The weekend is coming!" << endl;
    }
    
    return 0;
}
```

## Advantages
- **Readability**: Named constants are self-documenting
- **Type Safety**: Compiler can check enum values
- **Maintainability**: Easy to modify enum values in one place
- **Memory Efficient**: Takes space of an integer
