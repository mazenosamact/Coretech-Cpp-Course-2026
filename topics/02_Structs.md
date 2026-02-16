# Structs (C Concepts)

## Summary
A struct (structure) is a composite data type that groups multiple variables (members) together. It allows you to organize related data under a single name, improving code organization and readability.

## Key Concepts
- **Members**: Variables within a struct
- **Default access**: Public in C structs
- **Declaration**: Define structure type and create instances
- **Accessing members**: Using dot (`.`) or arrow (`->`) operators

## Code Examples

### Basic Struct Definition and Usage
```cpp
#include <iostream>
using namespace std;

struct Person {
    char name[50];
    int age;
    float height;
};

int main() {
    Person p1;
    p1.age = 25;
    p1.height = 5.9f;
    
    cout << "Age: " << p1.age << endl;
    cout << "Height: " << p1.height << endl;
    
    return 0;
}
```

### Struct Initialization
```cpp
#include <iostream>
using namespace std;

struct Point {
    int x;
    int y;
};

int main() {
    // Declaration and initialization
    Point p1 = {10, 20};
    
    Point p2;
    p2.x = 5;
    p2.y = 15;
    
    cout << "Point 1: (" << p1.x << ", " << p1.y << ")" << endl;
    cout << "Point 2: (" << p2.x << ", " << p2.y << ")" << endl;
    
    return 0;
}
```

### Structs with Arrays
```cpp
#include <iostream>
using namespace std;

struct Student {
    char name[50];
    int id;
    float gpa;
    int scores[5];
};

int main() {
    Student s1 = {"John", 101, 3.8, {95, 87, 92, 88, 90}};
    
    cout << "Name: " << s1.name << endl;
    cout << "ID: " << s1.id << endl;
    cout << "GPA: " << s1.gpa << endl;
    cout << "First score: " << s1.scores[0] << endl;
    
    return 0;
}
```

### Nested Structs
```cpp
#include <iostream>
using namespace std;

struct Address {
    char street[100];
    char city[50];
    int zipCode;
};

struct Employee {
    char name[50];
    int id;
    Address home;
};

int main() {
    Employee emp = {"Alice", 1001, {"123 Main St", "New York", 10001}};
    
    cout << "Employee: " << emp.name << endl;
    cout << "Address: " << emp.home.street << ", " << emp.home.city << endl;
    
    return 0;
}
```

### Struct with Pointers
```cpp
#include <iostream>
#include <cstring>
using namespace std;

struct Book {
    char title[100];
    char author[50];
    float price;
};

void displayBook(Book *book) {
    cout << "Title: " << book->title << endl;
    cout << "Author: " << book->author << endl;
    cout << "Price: $" << book->price << endl;
}

int main() {
    Book b1 = {"The C++ Primer", "Stanley Lippman", 59.99f};
    
    displayBook(&b1);
    
    return 0;
}
```

### Array of Structs
```cpp
#include <iostream>
using namespace std;

struct Car {
    char brand[30];
    int year;
    float price;
};

int main() {
    Car cars[3] = {
        {"Honda", 2020, 25000},
        {"Toyota", 2021, 28000},
        {"Ford", 2019, 22000}
    };
    
    for (int i = 0; i < 3; i++) {
        cout << cars[i].brand << " (" << cars[i].year << ")" << endl;
    }
    
    return 0;
}
```

## Differences from Classes
- Structs default to public access
- Classes default to private access
- Structs are used for simple data grouping
