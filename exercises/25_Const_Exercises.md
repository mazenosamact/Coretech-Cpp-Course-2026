# Const Keyword - Practical Exercises

## Exercise 1: Const Correctness (Data Protection)
**Context:** Prevent accidental modification of read-only data.

**Problem:**
```cpp
// Implement const correctness:
// 1. Const variables
// 2. Const pointers and references
// 3. Const member functions
// 4. Const method overloading
// 5. Compile-time safety
```

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string account_holder;
    double balance;
    int pin;
    
public:
    BankAccount(const string &holder, double initial_balance, int p)
        : account_holder(holder), balance(initial_balance), pin(p) {}
    
    // Const member function - cannot modify state
    double getBalance() const {
        return balance;
    }
    
    const string &getHolder() const {
        return account_holder;
    }
    
    // Non-const - can modify state
    void deposit(double amount) {
        balance += amount;
        cout << "✓ Deposited: $" << amount << endl;
    }
    
    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "✓ Withdrew: $" << amount << endl;
        } else {
            cout << "✗ Insufficient funds" << endl;
        }
    }
    
    void displayStatement() const {
        cout << "Account: " << account_holder << endl;
        cout << "Balance: $" << balance << endl;
    }
};

int main() {
    cout << "=== Const Keyword: Const Correctness ===" << endl;
    
    cout << "\n--- Creating account ---" << endl;
    BankAccount account("John Doe", 1000.0, 1234);
    
    cout << "\n--- Const operations (read-only functions) ---" << endl;
    // These work because they're const member functions
    cout << "Balance: $" << account.getBalance() << endl;
    cout << "Holder: " << account.getHolder() << endl;
    account.displayStatement();
    
    cout << "\n--- Modifying account ---" << endl;
    account.deposit(500);
    account.withdraw(200);
    
    cout << "\n--- Reading after modification ---" << endl;
    cout << "New balance: $" << account.getBalance() << endl;
    
    cout << "\n--- Const reference (prevents modification) ---" << endl;
    const BankAccount &const_ref = account;
    // const_ref.deposit(100);  // Compiler error!
    cout << "Via const ref - Balance: $" << const_ref.getBalance() << endl;
    
    cout << "\n--- Const data ---" << endl;
    const double PI = 3.14159;
    // PI = 3.0;  // Compiler error!
    cout << "PI value: " << PI << endl;
    
    cout << "\n✓ Const correctness enforced" << endl;
    
    return 0;
}
```

---

## Exercise 2: Const Pointers (Pointer Types)
**Context:** Understand different const pointer variations.

**Problem:**
```cpp
// Master const pointer variants:
// 1. const value pointer to value
// 2. pointer to const value
// 3. const pointer to const value
// 4. Compilation errors for violations
// 5. Real-world usage
```

**Solution:**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== Const: Pointer Variants ===" << endl;
    
    int value = 10;
    
    cout << "\n--- Type 1: Const value (pointer to non-const) ---" << endl;
    // Can change what pointer points to, cannot change value through pointer
    const int *ptr1 = &value;
    cout << "Value: " << *ptr1 << endl;
    // *ptr1 = 20;  // Error: cannot modify const value
    int other = 20;
    ptr1 = &other;  // OK: can reassign pointer
    cout << "After reassignment: " << *ptr1 << endl;
    
    cout << "\n--- Type 2: Const pointer (non-const value) ---" << endl;
    // Cannot change what pointer points to, can change value
    int *const ptr2 = &value;
    *ptr2 = 30;  // OK: can modify value
    cout << "Modified value: " << *ptr2 << endl;
    // ptr2 = &other;  // Error: const pointer cannot change address
    
    cout << "\n--- Type 3: Const pointer to const value ---" << endl;
    // Cannot change either pointer or value
    const int *const ptr3 = &value;
    cout << "Value: " << *ptr3 << endl;
    // *ptr3 = 40;  // Error: cannot modify
    // ptr3 = &other;  // Error: cannot reassign
    
    cout << "\n--- Practical use case: Array iteration ---" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    
    // Pointer to const - reading array values
    const int *read_ptr = arr;
    for (int i = 0; i < 5; i++) {
        cout << *read_ptr << " ";
        read_ptr++;
    }
    cout << endl;
    
    cout << "\n--- Practical use case: Configuration pointer ---" << endl;
    struct Config {
        int timeout;
        string host;
    };
    
    Config config1 = {30, "localhost"};
    // Configuration pointer shouldn't change
    const Config *const config_ptr = &config1;
    
    cout << "Timeout: " << config_ptr->timeout << endl;
    // config_ptr->timeout = 60;  // Error in real code
    // config_ptr = new Config();  // Error: cannot reassign
    
    cout << "\n✓ Const pointer variations understood" << endl;
    
    return 0;
}
```

---

## Exercise 3: Logical Const (Mutable Members)
**Context:** Methods that are const but need to modify internal state (caching, logging).

**Problem:**
```cpp
// Use mutable with const:
// 1. Const method with internal state modification
// 2. Caching in const function
// 3. Lazy evaluation
// 4. Logging in const functions
// 5. Distinguish physical vs logical const
```

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Rectangle {
private:
    double width, height;
    mutable double cached_area;
    mutable bool area_valid;
    mutable int access_count;
    
public:
    Rectangle(double w, double h) 
        : width(w), height(h), cached_area(0), area_valid(false), access_count(0) {}
    
    // Const method that caches result
    double getArea() const {
        access_count++;  // mutable - can modify in const function
        
        if (!area_valid) {
            cout << "  (calculating area...)" << endl;
            cached_area = width * height;
            area_valid = true;
        } else {
            cout << "  (using cached value)" << endl;
        }
        
        return cached_area;
    }
    
    // Const method with side effects (logging)
    void printDimensions() const {
        access_count++;  // Modification allowed via mutable
        cout << "Dimensions: " << width << " x " << height << endl;
    }
    
    // Return access statistics (const method modifying mutable)
    int getAccessCount() const {
        return access_count;
    }
    
    // Non-const version that invalidates cache
    void resize(double new_width, double new_height) {
        width = new_width;
        height = new_height;
        area_valid = false;  // Invalidate cache
        cout << "✓ Resized to " << width << " x " << height << endl;
    }
};

int main() {
    cout << "=== Const: Logical Const with Mutable ===" << endl;
    
    Rectangle rect(5.0, 4.0);
    
    cout << "\n--- First area calculation ---" << endl;
    double area1 = rect.getArea();
    cout << "Area: " << area1 << endl;
    
    cout << "\n--- Second area calculation (uses cache) ---" << endl;
    double area2 = rect.getArea();
    cout << "Area: " << area2 << endl;
    
    cout << "\n--- Printing dimensions ---" << endl;
    rect.printDimensions();
    
    cout << "\n--- Access count ---" << endl;
    cout << "Total accesses: " << rect.getAccessCount() << endl;
    
    cout << "\n--- Resizing (invalidates cache) ---" << endl;
    rect.resize(3.0, 4.0);
    
    cout << "\n--- Area calculation after resize ---" << endl;
    double area3 = rect.getArea();
    cout << "New area: " << area3 << endl;
    
    cout << "\n--- Final stats ---" << endl;
    cout << "Total accesses: " << rect.getAccessCount() << endl;
    
    cout << "\n✓ Logical const implementation complete" << endl;
    
    return 0;
}
```
