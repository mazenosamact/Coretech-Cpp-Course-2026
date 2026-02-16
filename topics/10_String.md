# std::string

## Summary
`std::string` is a C++ Standard Library class that provides dynamic string management, automatically handling memory allocation and deallocation. It's more convenient and safer than C-style character arrays.

## Key Concepts
- **Dynamic Allocation**: Grows as needed
- **Memory Management**: Automatic (RAII)
- **Rich API**: Many built-in functions
- **String Operations**: Concatenation, substring, searching
- **Safe Access**: Bounds checking available

## Code Examples

### Basic String Creation and Usage
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Different ways to create strings
    string s1;              // Empty string
    string s2("Hello");     // From C-string
    string s3 = "World";    // Assignment
    string s4(5, 'A');      // 5 'A' characters: "AAAAA"
    string s5(s2);          // Copy of s2
    
    cout << "s1: '" << s1 << "'" << endl;
    cout << "s2: " << s2 << endl;
    cout << "s3: " << s3 << endl;
    cout << "s4: " << s4 << endl;
    cout << "s5: " << s5 << endl;
    
    return 0;
}
```

### String Length and Size
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "Hello, World!";
    
    cout << "String: " << str << endl;
    cout << "Length: " << str.length() << endl;
    cout << "Size: " << str.size() << endl;
    cout << "Is empty: " << str.empty() << endl;
    
    string empty;
    cout << "Empty string length: " << empty.length() << endl;
    cout << "Empty string is empty: " << empty.empty() << endl;
    
    return 0;
}
```

### String Concatenation
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string first = "Hello";
    string second = "World";
    
    // Method 1: + operator
    string result1 = first + " " + second;
    cout << "Method 1: " << result1 << endl;
    
    // Method 2: += operator
    first += " ";
    first += second;
    cout << "Method 2: " << first << endl;
    
    // Method 3: append function
    string s1 = "Hello";
    s1.append(" Beautiful");
    s1.append(" World");
    cout << "Method 3: " << s1 << endl;
    
    return 0;
}
```

### Accessing Characters
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "Hello";
    
    // Using [] operator (no bounds checking)
    cout << "First char: " << str[0] << endl;      // 'H'
    cout << "Last char: " << str[4] << endl;       // 'o'
    
    // Using at() function (with bounds checking)
    cout << "at(0): " << str.at(0) << endl;        // 'H'
    
    // Modify characters
    str[0] = 'h';
    cout << "Modified: " << str << endl;           // "hello"
    
    // Iterate through string
    cout << "Characters: ";
    for (char c : str) {
        cout << c << " ";
    }
    cout << endl;
    
    return 0;
}
```

### String Comparison
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s1 = "Apple";
    string s2 = "Apple";
    string s3 = "Banana";
    
    // Equality
    cout << "s1 == s2: " << (s1 == s2) << endl;      // 1 (true)
    cout << "s1 == s3: " << (s1 == s3) << endl;      // 0 (false)
    
    // Comparison
    cout << "s1 < s3: " << (s1 < s3) << endl;        // 1 (true)
    cout << "s3 > s1: " << (s3 > s1) << endl;        // 1 (true)
    
    // Using compare() function
    cout << "s1.compare(s2): " << s1.compare(s2) << endl; // 0 (equal)
    cout << "s1.compare(s3): " << s1.compare(s3) << endl; // -1 (less)
    
    return 0;
}
```

### Substring and Finding
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "Hello, World! Hello!";
    
    // Substring
    string sub = str.substr(0, 5);
    cout << "Substring(0, 5): " << sub << endl;     // "Hello"
    
    // Finding substring
    size_t pos = str.find("World");
    if (pos != string::npos) {
        cout << "Found 'World' at position: " << pos << endl;
    }
    
    // Finding character
    size_t pos2 = str.find('!');
    cout << "First '!' at position: " << pos2 << endl;
    
    // Finding last occurrence
    size_t last = str.rfind("Hello");
    cout << "Last 'Hello' at position: " << last << endl;
    
    return 0;
}
```

### String Insertion and Erasure
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "Hello World";
    
    // Insert
    str.insert(6, "Beautiful ");
    cout << "After insert: " << str << endl;
    
    // Erase
    string str2 = "Hello World";
    str2.erase(5, 6);  // Erase 6 characters starting at position 5
    cout << "After erase: " << str2 << endl;
    
    // Replace
    string str3 = "Hello World";
    str3.replace(6, 5, "C++");
    cout << "After replace: " << str3 << endl;
    
    // Clear
    str3.clear();
    cout << "After clear: '" << str3 << "'" << endl;
    
    return 0;
}
```

### Reversed String
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string str = "Hello";
    
    // Using reverse algorithm
    reverse(str.begin(), str.end());
    cout << "Reversed: " << str << endl;  // "olleH"
    
    return 0;
}
```

### String Conversion
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // String to number
    string num_str = "42";
    int num = stoi(num_str);
    double d = stod("3.14");
    
    cout << "String '42' as int: " << num << endl;
    cout << "String '3.14' as double: " << d << endl;
    
    // Number to string
    int value = 100;
    string str = to_string(value);
    cout << "100 as string: " << str << endl;
    
    double pi = 3.14159;
    string pi_str = to_string(pi);
    cout << "3.14159 as string: " << pi_str << endl;
    
    return 0;
}
```

### String Input and Output
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    
    // Read single word
    cout << "Enter a word: ";
    cin >> name;
    cout << "You entered: " << name << endl;
    
    // Read entire line
    cout << "Enter a sentence: ";
    cin.ignore();  // Clear newline from buffer
    getline(cin, name);
    cout << "You entered: " << name << endl;
    
    return 0;
}
```

### String Manipulation Functions
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string str = "Hello World";
    
    // Count occurrences
    int count = 0;
    for (char c : str) {
        if (c == 'l') count++;
    }
    cout << "Count of 'l': " << count << endl;
    
    // Check if starts with
    if (str.substr(0, 5) == "Hello") {
        cout << "Starts with 'Hello'" << endl;
    }
    
    // Check if ends with
    if (str.substr(str.length() - 5) == "World") {
        cout << "Ends with 'World'" << endl;
    }
    
    // Convert to uppercase
    string upper = str;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    cout << "Uppercase: " << upper << endl;
    
    return 0;
}
```

## Common String Methods
| Method | Purpose |
|--------|---------|
| `length()`, `size()` | Get string length |
| `empty()` | Check if empty |
| `find()` | Find substring position |
| `substr()` | Extract substring |
| `insert()` | Insert at position |
| `erase()` | Delete characters |
| `replace()` | Replace characters |
| `append()` | Add to end |
| `clear()` | Remove all |
| `compare()` | Compare strings |

## Advantages over C-style Strings
- Automatic memory management
- Can grow dynamically
- Safe bounds checking with `at()`
- Rich set of member functions
- Can be used with STL algorithms
- Easier to compare and concatenate
