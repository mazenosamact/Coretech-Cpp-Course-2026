# Unions

## Summary
A union is a data type that allows multiple members to share the same memory location. Unlike structs where each member has its own memory, all members in a union occupy the same space. The size of a union equals the size of its largest member.

## Key Concepts
- **Shared Memory**: All members share the same memory location
- **Size**: Union size = size of largest member
- **Mutual Exclusivity**: Only one member can hold a value at a time
- **Use Cases**: Type punning, space-efficient data storage

## Code Examples

### Basic Union Declaration
```cpp
#include <iostream>
using namespace std;

union Data {
    int intValue;
    float floatValue;
    char charValue;
};

int main() {
    Data data;
    
    cout << "Size of union: " << sizeof(Data) << " bytes" << endl;
    
    data.intValue = 10;
    cout << "data.intValue: " << data.intValue << endl;
    
    // Assigning to floatValue overwrites intValue
    data.floatValue = 3.14f;
    cout << "data.floatValue: " << data.floatValue << endl;
    cout << "data.intValue (now): " << data.intValue << endl;  // Changed!
    
    return 0;
}
```

### Memory Comparison: Struct vs Union
```cpp
#include <iostream>
using namespace std;

struct StructData {
    int a;
    float b;
    char c;
};

union UnionData {
    int a;
    float b;
    char c;
};

int main() {
    cout << "Size of struct: " << sizeof(StructData) << " bytes" << endl;
    cout << "Size of union: " << sizeof(UnionData) << " bytes" << endl;
    
    // Struct stores all values separately
    StructData s;
    s.a = 10;
    s.b = 3.14f;
    s.c = 'A';
    
    // Union overwrites when assigning
    UnionData u;
    u.a = 10;
    cout << "Union with int: " << u.a << endl;
    
    u.b = 3.14f;
    cout << "Union with float: " << u.b << endl;
    cout << "int value after float assignment: " << u.a << endl;  // Corrupted
    
    return 0;
}
```

### Union for Type Punning
```cpp
#include <iostream>
#include <cstring>
using namespace std;

union IntToBytes {
    int intValue;
    unsigned char bytes[4];
};

int main() {
    IntToBytes data;
    data.intValue = 0x12345678;
    
    cout << "Integer: " << hex << data.intValue << endl;
    cout << "As bytes: ";
    for (int i = 0; i < 4; i++) {
        cout << hex << (int)data.bytes[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Practical Union Example: Device Data
```cpp
#include <iostream>
using namespace std;

struct SensorValue {
    int sensorType;  // 1=temperature, 2=pressure, 3=humidity
};

union Value {
    float temperature;
    float pressure;
    float humidity;
};

struct Sensor {
    int type;
    Value reading;
};

int main() {
    Sensor s1;
    s1.type = 1;
    s1.reading.temperature = 25.5f;
    
    Sensor s2;
    s2.type = 2;
    s2.reading.pressure = 1013.25f;
    
    cout << "Sensor 1 - Temperature: " << s1.reading.temperature << "°C" << endl;
    cout << "Sensor 2 - Pressure: " << s2.reading.pressure << " hPa" << endl;
    
    return 0;
}
```

### Union with Arrays
```cpp
#include <iostream>
using namespace std;

union Data {
    int intArray[4];
    float floatArray[4];
    double doubleValue;
};

int main() {
    Data data;
    
    cout << "Size of union: " << sizeof(Data) << " bytes" << endl;
    
    // Fill with integers
    for (int i = 0; i < 4; i++) {
        data.intArray[i] = i * 10;
    }
    
    cout << "Int array: ";
    for (int i = 0; i < 4; i++) {
        cout << data.intArray[i] << " ";
    }
    cout << endl;
    
    // Now interpret as floats
    data.floatArray[0] = 3.14f;
    cout << "After float assignment - first int: " << data.intArray[0] << endl;
    
    return 0;
}
```

## Key Differences from Structs
| Aspect | Struct | Union |
|--------|--------|-------|
| Memory | Each member has own space | Members share space |
| Size | Sum of all members | Size of largest member |
| Access | All members independently | Only one at a time |
| Data Loss | No data loss | Overwriting occurs |

## Magic things you can do with union
- bit manipulation on floating point numbers (for complex mathematical operations optimizations with floats)
- Loop on struct members as if they are an array
- Create a "seemingly" non homogenoues array or list of elements.

## Use Cases
- Embedded systems with limited memory
- Hardware register mapping
- Type punning and bit manipulation
- Network packet handling
