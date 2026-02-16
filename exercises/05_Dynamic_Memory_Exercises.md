# Dynamic Memory Allocation - Practical Exercises

## Exercise 1: Circular Buffer for Real-Time Data (Embedded Systems)
**Context:** Real-time systems need a circular buffer to store sensor readings with fixed memory allocation.

**Problem:**
```cpp
// Create a circular buffer that:
// 1. Allocates memory dynamically with specified size
// 2. Stores sensor readings in FIFO order
// 3. Wraps around when reaching the end
// 4. Calculates running average
// 5. Properly deallocates memory
//
// Requirements:
// - Buffer size: 100 readings
// - Data type: float (temperature readings)
// - Implement: enqueue, dequeue, getAverage
```

**Solution:**
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class CircularBuffer {
private:
    float *buffer;
    int size;
    int head;
    int tail;
    int count;
    
public:
    CircularBuffer(int buffer_size) : size(buffer_size), head(0), 
                                      tail(0), count(0) {
        buffer = new float[size];
        cout << "✓ Circular buffer allocated: " << size << " elements" << endl;
    }
    
    ~CircularBuffer() {
        delete[] buffer;
        cout << "✓ Circular buffer deallocated" << endl;
    }
    
    void enqueue(float value) {
        buffer[tail] = value;
        tail = (tail + 1) % size;
        
        if (count < size) {
            count++;
        } else {
            head = (head + 1) % size;  // Overwrite oldest
        }
    }
    
    float dequeue() {
        if (count == 0) {
            cout << "Buffer empty!" << endl;
            return 0;
        }
        
        float value = buffer[head];
        head = (head + 1) % size;
        count--;
        return value;
    }
    
    float getAverage() {
        if (count == 0) return 0;
        
        float sum = 0;
        int idx = head;
        
        for (int i = 0; i < count; i++) {
            sum += buffer[idx];
            idx = (idx + 1) % size;
        }
        
        return sum / count;
    }
    
    int getCount() const {
        return count;
    }
    
    void printBuffer() {
        cout << "Buffer contents (" << count << " elements): ";
        int idx = head;
        for (int i = 0; i < count; i++) {
            cout << buffer[idx] << " ";
            idx = (idx + 1) % size;
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Circular Buffer for Sensor Data ===" << endl;
    
    CircularBuffer sensor_readings(5);  // Small buffer for demo
    
    cout << "\n--- Adding sensor readings ---" << endl;
    float temps[] = {22.5, 23.1, 22.8, 23.5, 22.9, 23.2, 22.7};
    
    for (float temp : temps) {
        sensor_readings.enqueue(temp);
        cout << "Added: " << temp << "°C | ";
        cout << "Average: " << sensor_readings.getAverage() << "°C | ";
        cout << "Count: " << sensor_readings.getCount() << endl;
    }
    
    cout << "\n--- Wrapping around buffer ---" << endl;
    sensor_readings.printBuffer();
    
    cout << "\n--- Dequeueing values ---" << endl;
    cout << "Dequeued: " << sensor_readings.dequeue() << endl;
    cout << "Dequeued: " << sensor_readings.dequeue() << endl;
    sensor_readings.printBuffer();
    
    return 0;
}
```

---

## Exercise 2: 2D Matrix for Image Processing (Backend/Signal Processing)
**Context:** Image processing requires dynamic 2D arrays to handle images of different sizes.

**Problem:**
```cpp
// Create a 2D matrix class:
// 1. Dynamically allocate a 2D array (rows × columns)
// 2. Implement row-major layout in single malloc
// 3. Provide element access: matrix[i][j]
// 4. Implement matrix operations (transpose, sum)
// 5. Proper cleanup with destructor
//
// Use case: Image pixel operations (RGB values)
```

**Solution:**
```cpp
#include <iostream>
using namespace std;

class Matrix {
private:
    int **data;
    int rows;
    int cols;
    
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        // Allocate 2D array
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
        }
        cout << "✓ Matrix allocated: " << rows << "x" << cols << endl;
    }
    
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        cout << "✓ Matrix deallocated" << endl;
    }
    
    void setValue(int i, int j, int value) {
        if (i < rows && j < cols) {
            data[i][j] = value;
        }
    }
    
    int getValue(int i, int j) const {
        if (i < rows && j < cols) {
            return data[i][j];
        }
        return -1;
    }
    
    void print() {
        cout << "\nMatrix (" << rows << "x" << cols << "):" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    int sumAll() {
        int sum = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                sum += data[i][j];
            }
        }
        return sum;
    }
    
    Matrix *transpose() {
        Matrix *result = new Matrix(cols, rows);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result->setValue(j, i, data[i][j]);
            }
        }
        
        return result;
    }
};

int main() {
    cout << "=== 2D Matrix Operations ===" << endl;
    
    Matrix img(3, 4);
    
    cout << "\n--- Populating matrix (image pixels) ---" << endl;
    int pixel_data[] = {
        255, 128, 64, 32,
        100, 150, 200, 250,
        50, 75, 100, 125
    };
    
    int idx = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            img.setValue(i, j, pixel_data[idx++]);
        }
    }
    
    img.print();
    
    cout << "\nSum of all pixels: " << img.sumAll() << endl;
    
    cout << "\n--- Transposed matrix ---" << endl;
    Matrix *transposed = img.transpose();
    transposed->print();
    
    delete transposed;
    cout << "\n✓ Operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Dynamic String Array with Reallocation (System Utilities)
**Context:** Command-line application needs to store a growing list of commands/arguments.

**Problem:**
```cpp
// Create a dynamic string array that:
// 1. Starts with small capacity (e.g., 5)
// 2. Doubles capacity when full
// 3. Stores command arguments
// 4. Searches for specific argument
// 5. Maintains proper memory management
//
// Use case: Shell command parser or configuration loader
```

**Solution:**
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class DynamicStringArray {
private:
    char **strings;
    int capacity;
    int count;
    
public:
    DynamicStringArray(int initial_capacity = 5) 
        : capacity(initial_capacity), count(0) {
        strings = new char*[capacity];
        cout << "✓ Array created with capacity: " << capacity << endl;
    }
    
    ~DynamicStringArray() {
        for (int i = 0; i < count; i++) {
            delete[] strings[i];
        }
        delete[] strings;
        cout << "✓ Array deallocated" << endl;
    }
    
    void add(const char *str) {
        if (count >= capacity) {
            capacity *= 2;
            cout << "  → Reallocating to capacity: " << capacity << endl;
            
            char **new_strings = new char*[capacity];
            
            for (int i = 0; i < count; i++) {
                new_strings[i] = strings[i];
            }
            
            delete[] strings;
            strings = new_strings;
        }
        
        strings[count] = new char[strlen(str) + 1];
        strcpy(strings[count], str);
        cout << "  Added: " << str << endl;
        count++;
    }
    
    const char *get(int index) const {
        if (index < count) {
            return strings[index];
        }
        return nullptr;
    }
    
    int find(const char *str) const {
        for (int i = 0; i < count; i++) {
            if (strcmp(strings[i], str) == 0) {
                return i;
            }
        }
        return -1;  // Not found
    }
    
    void print() {
        cout << "\nArray contents (" << count << "/" << capacity << "):" << endl;
        for (int i = 0; i < count; i++) {
            cout << "  [" << i << "] " << strings[i] << endl;
        }
    }
    
    int getCount() const {
        return count;
    }
};

int main() {
    cout << "=== Dynamic String Array ===" << endl;
    
    DynamicStringArray args;
    
    cout << "\n--- Adding command arguments ---" << endl;
    const char *commands[] = {
        "--verbose", "--debug", "--output", "/path/to/file", "--config"
    };
    
    for (const char *cmd : commands) {
        args.add(cmd);
    }
    
    args.print();
    
    cout << "\n--- Searching for arguments ---" << endl;
    int pos = args.find("--debug");
    if (pos != -1) {
        cout << "Found '--debug' at position: " << pos << endl;
    }
    
    pos = args.find("--help");
    if (pos == -1) {
        cout << "Argument '--help' not found" << endl;
    }
    
    cout << "\n--- Adding more arguments (triggering reallocation) ---" << endl;
    args.add("--version");
    args.add("--license");
    
    args.print();
    
    cout << "\n✓ Dynamic array operations complete" << endl;
    
    return 0;
}
```
