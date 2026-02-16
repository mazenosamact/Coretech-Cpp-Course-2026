# Pointers - Practical Exercises

## Exercise 1: GPIO Register Access (Embedded Systems)
**Context:** In embedded systems, GPIO registers are accessed through memory addresses. You need to control an LED on a microcontroller.

**Problem:**
```cpp
// Simulating ARM Cortex-M4 GPIO registers
#define GPIOA_BASE 0x40020000
#define GPIO_ODR_OFFSET 0x14
#define GPIO_IDR_OFFSET 0x10

// Your task: 
// 1. Create pointers to the GPIO output and input data registers
// 2. Set bit 5 (LED pin) in the output register to turn ON LED
// 3. Read bit 3 (button pin) from the input register
// 4. Verify the LED is ON only when button is pressed
```

**Solution:**
```cpp
#include <iostream>
#include <cstdint>
using namespace std;

int main() {
    // Simulated memory for GPIO registers
    uint32_t gpio_memory[1024] = {0};
    
    // Create pointers to GPIO registers (normally would be hardware addresses)
    uint32_t *GPIOA_ODR = gpio_memory + (0x14 / 4);  // Output Data Register
    uint32_t *GPIOA_IDR = gpio_memory + (0x10 / 4);  // Input Data Register
    
    // Simulate button press by setting bit 3 in input register
    *GPIOA_IDR |= (1 << 3);  // Button pressed
    
    // LED control: turn ON if button is pressed
    if (*GPIOA_IDR & (1 << 3)) {
        *GPIOA_ODR |= (1 << 5);  // Set LED (bit 5)
        cout << "LED ON (Button pressed)" << endl;
    }
    
    // Verify LED is ON
    if (*GPIOA_ODR & (1 << 5)) {
        cout << "✓ LED successfully turned ON" << endl;
    }
    
    return 0;
}
```

---

## Exercise 2: Array Processing with Pointer Arithmetic (Backend Development)
**Context:** Processing sensor data array in a data acquisition system. Data comes in as raw buffer that needs filtering.

**Problem:**
```cpp
// You have a circular buffer of sensor readings
// Task:
// 1. Create a pointer to traverse the buffer
// 2. Find the maximum value using pointer arithmetic (no array indexing)
// 3. Calculate average of last 5 readings using pointers
// 4. Output results with pointer positions

int sensor_data[] = {23, 45, 12, 67, 34, 89, 56, 78, 23, 45};
int buffer_size = 10;
```

**Solution:**
```cpp
#include <iostream>
using namespace std;

int main() {
    int sensor_data[] = {23, 45, 12, 67, 34, 89, 56, 78, 23, 45};
    int buffer_size = 10;
    
    // Task 1: Find maximum value using pointer arithmetic
    int *ptr = sensor_data;
    int max_value = *ptr;
    int *max_ptr = ptr;
    
    while (ptr < sensor_data + buffer_size) {
        if (*ptr > max_value) {
            max_value = *ptr;
            max_ptr = ptr;
        }
        ptr++;
    }
    
    cout << "Max value: " << max_value 
         << " at position: " << (max_ptr - sensor_data) << endl;
    
    // Task 2: Calculate average of last 5 readings
    ptr = sensor_data + buffer_size - 5;  // Point to 5th from end
    int sum = 0;
    
    cout << "Last 5 readings: ";
    while (ptr < sensor_data + buffer_size) {
        cout << *ptr << " ";
        sum += *ptr;
        ptr++;
    }
    
    double average = (double)sum / 5;
    cout << "\nAverage of last 5: " << average << endl;
    
    return 0;
}
```

---

## Exercise 3: Dynamic String Buffer Management (Linux System Programming)
**Context:** Writing to a log file that grows dynamically. You need to manage a buffer for log entries.

**Problem:**
```cpp
// Scenario: A daemon process logs system events
// Task:
// 1. Create a dynamic string buffer
// 2. Append multiple log entries using pointer operations
// 3. Find specific log entry by substring using pointer traversal
// 4. Deallocate memory properly

// Hint: Use strcpy, strcat, and pointer arithmetic
```

**Solution:**
```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    // Task 1: Create dynamic buffer for logs
    int buffer_size = 256;
    char *log_buffer = new char[buffer_size];
    strcpy(log_buffer, "[INFO] System started\n");
    
    // Task 2: Append log entries using pointer operations
    char *log_ptr = log_buffer + strlen(log_buffer);
    
    strcat(log_buffer, "[WARN] Low memory detected\n");
    log_ptr = log_buffer + strlen(log_buffer);
    
    strcat(log_buffer, "[ERROR] Failed to open config\n");
    
    // Task 3: Find specific log entry
    char *error_ptr = strstr(log_buffer, "[ERROR]");
    if (error_ptr != nullptr) {
        cout << "Found error at position: " 
             << (error_ptr - log_buffer) << endl;
        cout << "Error message: " << error_ptr << endl;
    }
    
    // Task 4: Display all logs
    cout << "\nFull log buffer:\n" << log_buffer << endl;
    
    // Deallocate properly
    delete[] log_buffer;
    cout << "✓ Memory deallocated" << endl;
    
    return 0;
}
```
