# iostream - Input/Output Streams

## Summary
`iostream` (Input/Output stream) is the C++ standard library header that provides classes for reading from and writing to input/output streams. It includes `cin` for input and `cout` for output, enabling interactive console programming and formatted data handling.

## Key Concepts
- **Streams**: Abstraction for data flow (input/output)
- **`cout`**: Standard output stream (console)
- **`cin`**: Standard input stream (keyboard)
- **`cerr`**: Standard error stream
- **Operators**: `<<` (output), `>>` (input)
- **Formatting**: Manipulators like `endl`, `setw()`, `fixed`, etc.

## Code Examples

### Basic Output with cout
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    
    int age = 25;
    float height = 5.8f;
    
    cout << "Age: " << age << endl;
    cout << "Height: " << height << endl;
    
    // Chaining output
    cout << "Name: " << "John" << ", Age: " << 25 << endl;
    
    return 0;
}
```

### Basic Input with cin
```cpp
#include <iostream>
using namespace std;

int main() {
    int number;
    string name;
    
    cout << "Enter a number: ";
    cin >> number;
    
    cout << "Enter your name: ";
    cin >> name;  // Reads until whitespace
    
    cout << "You are " << name << " and entered: " << number << endl;
    
    return 0;
}
```

### Reading Multiple Values
```cpp
#include <iostream>
using namespace std;

int main() {
    int x, y;
    float f;
    
    cout << "Enter two integers and a float: ";
    cin >> x >> y >> f;
    
    cout << "Values: " << x << ", " << y << ", " << f << endl;
    
    return 0;
}
```

### Reading Strings
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    
    cout << "Enter your full name: ";
    getline(cin, name);  // Reads entire line including spaces
    
    cout << "Hello, " << name << "!" << endl;
    
    return 0;
}
```

### Formatted Output with Manipulators
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    float pi = 3.14159265f;
    int value = 42;
    
    cout << "Default precision: " << pi << endl;
    
    // Set decimal precision
    cout << fixed << setprecision(2) << pi << endl;
    
    // Set field width
    cout << setw(10) << value << endl;
    
    // Right align (default)
    cout << setw(10) << right << value << endl;
    
    // Left align
    cout << setw(10) << left << value << endl;
    
    // Hexadecimal and octal
    cout << hex << value << endl;  // 2a
    cout << oct << value << endl;  // 52
    cout << dec << value << endl;  // 42
    
    return 0;
}
```

### Table Formatting
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << setw(15) << "Name" << setw(10) << "Age" << setw(15) << "Salary" << endl;
    cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;
    
    cout << setw(15) << left << "John Doe" 
         << setw(10) << right << 25 
         << setw(15) << right << "$50,000" << endl;
    
    cout << setw(15) << left << "Jane Smith" 
         << setw(10) << right << 28 
         << setw(15) << right << "$55,000" << endl;
    
    return 0;
}
```

### Error Stream (cerr)
```cpp
#include <iostream>
using namespace std;

int main() {
    int value;
    
    cout << "Enter a positive number: ";
    cin >> value;
    
    if (value <= 0) {
        cerr << "Error: Please enter a positive number!" << endl;
        return 1;
    }
    
    cout << "Thank you for entering: " << value << endl;
    return 0;
}
```

### Input Validation
```cpp
#include <iostream>
using namespace std;

int main() {
    int num;
    
    cout << "Enter an integer: ";
    
    if (cin >> num) {
        cout << "Successfully read: " << num << endl;
    } else {
        cerr << "Error: Invalid input!" << endl;
        cin.clear();        // Clear error flags
        cin.ignore(100, '\n');  // Clear input buffer
    }
    
    return 0;
}
```

### Reading Character by Character
```cpp
#include <iostream>
using namespace std;

int main() {
    char ch;
    
    cout << "Enter characters (Ctrl+D to end):" << endl;
    
    while (cin.get(ch)) {
        cout << "You entered: " << ch << " (ASCII: " << (int)ch << ")" << endl;
        
        if (ch == '\n') break;
    }
    
    return 0;
}
```

### Scientific Notation
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double large = 123456789.0;
    double small = 0.000000123;
    
    cout << "Default: " << large << ", " << small << endl;
    
    cout << scientific;
    cout << "Scientific: " << large << ", " << small << endl;
    
    cout << fixed;
    cout << "Fixed: " << large << ", " << small << endl;
    
    return 0;
}
```

## Common Stream Manipulators
| Manipulator | Purpose |
|-------------|---------|
| `endl` | Output newline and flush |
| `setw(n)` | Set field width |
| `setprecision(n)` | Set decimal precision |
| `fixed` | Use fixed-point notation |
| `scientific` | Use scientific notation |
| `left`, `right` | Alignment |
| `hex`, `oct`, `dec` | Number base |
| `showpoint` | Show decimal point |

## Best Practices
- Use `getline()` for reading entire lines
- Check input validity before using values
- Use `endl` or `'\n'` appropriately
- Prefer `string` over character arrays
