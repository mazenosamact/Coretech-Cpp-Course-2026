#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <sstream>
using namespace std;

#if 0
// Callable objects
std::function<void(void)> func;


void handle_create(vector<string>&)
{
    // priv_create()
}

map<string, std::function<void(vector<string>&)>> m_commands = {
    {"create", handle_create  } , 
};

void say_hello(void)
{
    cout << "hello world" << endl;
}
#endif

// map ordered container --> keys are sorted 
struct Person
{
    Person(string n, int a):name(n),age(a){}
    string name;
    int age;
    string toString()
    {
        string out("Person:");
        stringstream ss(out);

        ss << name << "," << age << endl;
        return ss.str();
    }
};

struct Address
{
    string street;
    string country;
    int building_no;
    Address(string st, string ct, int bn)
    :street(st),country(ct),building_no(bn){}
    bool operator<(const Address& other) const
    {
        cout << "comparing" << endl;
        return (
            this->street < other.street  && this->building_no < other.building_no 
        );
    }

    string toString()
    {
        string out("Address:");
        stringstream ss(out);

        ss << country << "," << street << "," << building_no << endl ;

        return ss.str();
    }
};

map<Address, Person> google_maps = {
    {Address("Abbas","Egypt",5),Person("Mazen", 30)   },
    {Address("Tayaran","Egypt2",50), Person("Ahmed", 45)   },
    {Address("EL-7aram","SaudiArabia",15),Person("Nabil", 78 )   },
};

int test_map_main(int argc, char* argv[])
{
    map<string, int> m = {
        {"mazen", 30},
        {"nabil", 26},
        {"ali", 27},
        {"Mohamed", 25},
    };

    m["mazen"] = 32;

    if(m.count("mazen"))
    {
        cout << "mazen exists in map" << endl;
    }
    m.insert({"Ahmed", 35});

    for(auto it = google_maps.begin(); it != google_maps.end(); it++)
    {
        auto addr = it->first;
        cout << "key:" << addr.toString() << ' ' 
        << ",value: " << it->second.toString() << endl;
    }

    // func = say_hello ;

    // func();
}
