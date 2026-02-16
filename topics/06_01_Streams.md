# Streams - StringStream and FileStream

## Summary

Streams are abstractions for data flow in C++. While `iostream` handles console I/O, **`stringstream`** handles in-memory string data, and **`fstream`** handles file I/O. All streams follow the same buffer-based paradigm, allowing seamless data reading/writing with consistent operators.

## Key Concepts

### stringstream
- In-memory stream for string data
- Used for parsing and formatting strings
- Supports both input and output operations
- Useful for data conversion and manipulation

### File Streams (ifstream, ofstream, fstream)
- `ifstream`: Input File Stream (reading files)
- `ofstream`: Output File Stream (writing files)
- `fstream`: Both input and output (reading and writing)
- Handle file operations with consistent stream syntax

### Common Operations
- `<<` operator: Write/insert data into stream
- `>>` operator: Read/extract data from stream
- `.str()`: Get string content from stringstream
- `.open()`: Open file to stream
- `.close()`: Close file stream
- `.is_open()`: Check if file is open
- `.eof()`: Check end of file
- `.getline()`: Read line from stream
- `.seekg()` / `.seekp()`: Position in stream

## stringstream

### Basic Usage
```cpp
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    // Creating a stringstream
    stringstream ss;
    
    // Writing to stringstream
    cout << "=== Writing to stringstream ===" << endl;
    ss << "Hello" << " " << "World" << " " << 123;
    
    // Getting the string content
    cout << "Content: " << ss.str() << endl;
    
    // Reading from stringstream
    cout << "\n=== Reading from stringstream ===" << endl;
    string word1, word2;
    int number;
    
    ss >> word1 >> word2 >> number;
    cout << "Extracted: " << word1 << ", " << word2 << ", " << number << endl;
    
    return 0;
}
```

### String to Integer Conversion
```cpp
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string str_number = "12345";
    int number;
    
    stringstream ss(str_number);
    ss >> number;
    
    cout << "String '" << str_number << "' as int: " << number << endl;
    cout << "Doubled: " << (number * 2) << endl;
    
    return 0;
}
```

### Parsing CSV Line
```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string line = "John,25,Engineer,75000";
    vector<string> fields;
    string field;
    
    stringstream ss(line);
    
    // Extract fields separated by comma
    while (getline(ss, field, ',')) {
        fields.push_back(field);
    }
    
    cout << "Name: " << fields[0] << endl;
    cout << "Age: " << fields[1] << endl;
    cout << "Title: " << fields[2] << endl;
    cout << "Salary: " << fields[3] << endl;
    
    return 0;
}
```

### Number to String Conversion
```cpp
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    int count = 42;
    double pi = 3.14159;
    
    stringstream ss;
    ss << "Count: " << count << ", Pi: " << pi;
    
    string result = ss.str();
    cout << result << endl;
    
    // Another approach
    ss.str("");  // Clear stringstream
    ss.clear();  // Reset flags
    
    ss << "New value: " << 100;
    cout << ss.str() << endl;
    
    return 0;
}
```

## File Streams

### Writing to File (ofstream)
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Create and open output file
    ofstream outfile("data.txt");
    
    // Check if file opened successfully
    if (!outfile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    // Write to file
    outfile << "Line 1: Hello, File!" << endl;
    outfile << "Line 2: This is a test" << endl;
    outfile << "Line 3: Goodbye!" << endl;
    
    // Always close the file
    outfile.close();
    
    cout << "File written successfully" << endl;
    
    return 0;
}
```

### Reading from File (ifstream)
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream infile("data.txt");
    
    if (!infile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    string line;
    
    // Read line by line until end of file
    while (getline(infile, line)) {
        cout << line << endl;
    }
    
    infile.close();
    
    return 0;
}
```

### Counting Lines in File
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream infile("data.txt");
    
    if (!infile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    int line_count = 0;
    string line;
    
    while (getline(infile, line)) {
        line_count++;
    }
    
    cout << "Total lines: " << line_count << endl;
    
    infile.close();
    
    return 0;
}
```

### Reading and Writing (fstream)
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Write mode
    fstream file("data.txt", ios::out);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    file << "First entry" << endl;
    file << "Second entry" << endl;
    file.close();
    
    // Read mode
    file.open("data.txt", ios::in);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    string content;
    while (getline(file, content)) {
        cout << content << endl;
    }
    
    file.close();
    
    return 0;
}
```

### Append Mode
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Open file in append mode
    ofstream file("log.txt", ios::app);
    
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    file << "New log entry" << endl;
    file << "Another entry" << endl;
    
    file.close();
    
    cout << "Entries appended successfully" << endl;
    
    return 0;
}
```

## Stream Flags and Modes

### File Open Modes
```cpp
ios::in        // Read (default for ifstream)
ios::out       // Write (default for ofstream)
ios::app       // Append to end of file
ios::ate       // Open and seek to end
ios::binary    // Binary mode (default is text)
ios::trunc     // Truncate file if it exists
```

### Stream State Flags
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream file("test.txt");
    
    // Check if file is open
    if (file.is_open()) {
        file << "Test data";
        
        cout << "good(): " << file.good() << endl;     // No errors
        cout << "eof(): " << file.eof() << endl;       // End of file reached
        cout << "fail(): " << file.fail() << endl;     // Operation failed
        cout << "bad(): " << file.bad() << endl;       // Fatal error
    }
    
    file.close();
    
    return 0;
}
```

## Best Practices

1. **Always check if stream is open**
   ```cpp
   if (!file.is_open()) {
       cerr << "Error opening file" << endl;
       return 1;
   }
   ```

2. **Always close files**
   ```cpp
   file.close();
   ```

3. **Use RAII principle (file closes automatically)**
   ```cpp
   {
       ofstream file("data.txt");
       file << "data";
   }  // File automatically closed here
   ```

4. **Clear stringstream before reusing**
   ```cpp
   ss.str("");    // Clear
   ss.clear();    // Reset flags
   ```

5. **Handle errors gracefully**
   ```cpp
   if (!infile) {
       cerr << "Failed to open file" << endl;
       // Handle error
   }
   ```

## Common Stream Operations

| Operation | Syntax | Purpose |
|-----------|--------|---------|
| Write | `stream << value` | Output data |
| Read | `stream >> variable` | Input data |
| Read line | `getline(stream, str)` | Read until newline |
| Check open | `stream.is_open()` | File opened? |
| Check EOF | `stream.eof()` | End of file? |
| Get string | `stringstream.str()` | Extract content |
| Seek position | `stream.seekg(pos)` | Set read position |
| Clear stream | `stream.clear()` | Reset flags |
| Close | `stream.close()` | Close stream |

## Summary

- **stringstream**: In-memory string processing and conversion
- **ifstream**: Read files efficiently
- **ofstream**: Write files efficiently
- **fstream**: Both read and write operations
- Streams provide consistent interface across console, strings, and files
- Always check if stream is open before use
- Remember to close files when done
