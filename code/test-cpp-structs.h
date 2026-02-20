#include <iostream>
#include <string>
using namespace std;

// Struct - default public
struct Person_Struct {
    string name;
    int age;
    
    void display() {
        // cout << "address of person:" << this << endl;
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

// Class - default private
class CPerson {

    string name;
    int age;
    
public:
    CPerson(string n, int a) : name(n), age(a) {}
    CPerson(string n) : name(n), age(0) {}
    CPerson(){}
    
    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
};

class CSensorReading {

public:
    CSensorReading(int value, int unit, int timestamp): 
    m_value(value), 
    m_unit(unit),
    m_timestamp(timestamp)
    {

    }
    
private:
    int m_value; int m_unit; int m_timestamp ;
};

for(int i=0; i<size; i++)

int stat = func_call();
if(stat == ERROR)
{
    print_err_msg();
    exit 1;
}


/** idiom RAII
 * Resource Aquisition Is Initialization
 * memory, files, mutex, semaphore, ...
 */
class CSensorNode
{
public:
    CSensorNode(int loc):
    m_id(new int),
    m_hash(genrateHash(m_id)),
    m_location(loc)
    {
        generateHash(m_id);
        m_reading = CSensorReading(0,0,0);

    }

    ~CSensorNode()
    {
        delete m_id;
    }

    /** lazy initialization */
    void init(...){}

    

private:
    int* m_id;
    int m_location;
    CSensorReading m_reading;
    CSensorReading m_reading2;
};

{
    CSensorNode n;
    
    n.init();
}
    

int test_cpp_struct_main() {
    // Struct: members are directly accessible
    Person_Struct s = {"John", 25};
    s.name = "Jane";  // Valid
    s.display();
    // cout << "address of s:" << &s << endl ;
    
    // Class: members are private, need getters/setters
    CPerson c("Bob", 30);

    // c.name = "Alice";  // ERROR: private member
    c.setName("Alice");  // OK: using setter
    c.display();

    CPerson b ;
    
    return 0;
}