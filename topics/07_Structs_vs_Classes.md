# Structs vs Classes and Class Syntax

## Summary
In C++, both structs and classes are used to group data and functions, but they differ primarily in encapsulation: structs default to public members, while classes default to private. Classes introduce object-oriented programming concepts with proper encapsulation and access control.

## Key Concepts
- **Access Control**: Public, private, protected
- **Constructors**: Initialize objects
- **Destructors**: Cleanup resources
- **Member Functions**: Methods within the class
- **Encapsulation**: Hide internal implementation

## Code Examples

### Struct vs Class Comparison
```cpp
#include <iostream>
using namespace std;

// Struct - default public
struct Person_Struct {
    string name;
    int age;
    
    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

// Class - default private
class Person_Class {
private:
    string name;
    int age;
    
public:
    Person_Class(string n, int a) : name(n), age(a) {}
    
    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
};

int main() {
    // Struct: members are directly accessible
    Person_Struct s = {"John", 25};
    s.name = "Jane";  // Valid
    s.display();
    
    // Class: members are private, need getters/setters
    Person_Class c("Bob", 30);
    // c.name = "Alice";  // ERROR: private member
    c.setName("Alice");  // OK: using setter
    c.display();
    
    return 0;
}
```

### Basic Class Definition
```cpp
#include <iostream>
using namespace std;

class Rectangle {
private:
    double length;
    double width;
    
public:
    Rectangle() : length(0), width(0) {}
    
    Rectangle(double l, double w) : length(l), width(w) {}
    
    double getArea() {
        return length * width;
    }
    
    double getPerimeter() {
        return 2 * (length + width);
    }
    
    void setDimensions(double l, double w) {
        length = l;
        width = w;
    }
};

int main() {
    Rectangle rect(5.0, 3.0);
    
    cout << "Area: " << rect.getArea() << endl;
    cout << "Perimeter: " << rect.getPerimeter() << endl;
    
    return 0;
}
```

### Access Specifiers
```cpp
#include <iostream>
using namespace std;

class BankAccount {
private:                    // Accessible only within the class
    double balance;
    
protected:                  // Accessible in derived classes
    string accountNumber;
    
public:                     // Accessible from outside
    BankAccount(double initial = 0) : balance(initial) {}
    
    void deposit(double amount) {
        balance += amount;
    }
    
    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        }
    }
    
    double getBalance() {
        return balance;
    }
};

int main() {
    BankAccount acc(1000.0);
    
    acc.deposit(500);
    cout << "Balance: " << acc.getBalance() << endl;
    
    acc.withdraw(200);
    cout << "New balance: " << acc.getBalance() << endl;
    
    // acc.balance = 100;  // ERROR: private
    
    return 0;
}
```

### Member Variables and Functions
```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int rollNumber;
    double gpa;
    
public:
    // Constructor
    Student(string n, int roll, double g) 
        : name(n), rollNumber(roll), gpa(g) {}
    
    // Member functions
    void display() {
        cout << "Name: " << name << endl;
        cout << "Roll: " << rollNumber << endl;
        cout << "GPA: " << gpa << endl;
    }
    
    bool isTopStudent() {
        return gpa >= 3.8;
    }
    
    // Getters
    string getName() { return name; }
    int getRoll() { return rollNumber; }
    double getGPA() { return gpa; }
    
    // Setters
    void setGPA(double g) {
        if (g >= 0 && g <= 4.0) {
            gpa = g;
        }
    }
};

int main() {
    Student s1("Alice", 101, 3.9);
    s1.display();
    
    if (s1.isTopStudent()) {
        cout << s1.getName() << " is a top student!" << endl;
    }
    
    return 0;
}
```

### Const Member Functions
```cpp
#include <iostream>
using namespace std;

class CircleAPI {
private:
    double radius;
    
public:
    CircleAPI(double r) : radius(r) {}
    
    // Const member functions - cannot modify member data
    double getRadius() const {
        return radius;
    }
    
    double getArea() const {
        return 3.14159 * radius * radius;
    }
    
    // Non-const function
    void setRadius(double r) {
        radius = r;
    }
};

int main() {
    const CircleAPI c1(5.0);
    double area = c1.getArea();  // OK: calls const function
    // c1.setRadius(10);  // ERROR: cannot call non-const function on const object
    
    CircleAPI c2(3.0);
    c2.setRadius(7.0);  // OK: non-const function
    
    return 0;
}
```

### Static Members
```cpp
#include <iostream>
using namespace std;

class Counter {
private:
    static int count;  // Shared across all instances
    
public:
    Counter() { count++; }
    
    static int getCount() {
        return count;
    }
};

// Initialize static member
int Counter::count = 0;

int main() {
    cout << "Count: " << Counter::getCount() << endl;  // 0
    
    Counter c1, c2, c3;
    
    cout << "Count: " << Counter::getCount() << endl;  // 3
    cout << "Count: " << c1.getCount() << endl;        // 3
    
    return 0;
}
```

### Class with Arrays and Strings
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Course {
private:
    string courseName;
    vector<int> grades;
    
public:
    Course(string name) : courseName(name) {}
    
    void addGrade(int grade) {
        grades.push_back(grade);
    }
    
    double getAverage() {
        if (grades.empty()) return 0;
        
        double sum = 0;
        for (int g : grades) {
            sum += g;
        }
        return sum / grades.size();
    }
    
    void display() {
        cout << "Course: " << courseName << endl;
        cout << "Average: " << getAverage() << endl;
    }
};

int main() {
    Course math("Calculus");
    
    math.addGrade(95);
    math.addGrade(87);
    math.addGrade(92);
    
    math.display();
    
    return 0;
}
```

## Key Differences Summary
| Feature | Struct | Class |
|---------|--------|-------|
| Default Access | Public | Private |
| Inheritance | Public | Private |
| Use Case | Simple data | Complex objects |
| Encapsulation | Limited | Full |

## Best Practices
- Use classes for complex objects with behavior
- Use structs for simple data containers
- Keep data private, provide public interfaces
- Use const for read-only member functions
