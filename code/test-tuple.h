#include <iostream>
#include <tuple>
#include <string>
using namespace std;

enum {
    NAME,AGE,LENGTH
};

struct Phase
{
    int current,voltage, power;
};

// 3 phase - current, voltage, power
struct PhaseVector
{
    Phase phase1;
    Phase phase2;
    Phase phase3;
    int size(){ return 3; } ;

    Phase& operator[](int i)
    {
        switch(i)
        {
            case 0: return phase1;
            case 1: return phase2;
            case 2: return phase3;
            default: throw std::out_of_range ; return Phase();
        }
    }
};

PhaseVector pv;

pv.phase1.current = 20 ;

for(int i=0; i<pv.size(); i++)
{
    pv[i].current = 0;
    pv[i].voltage = 1;
    pv[i].power = 2 ;
}


int test_tuple_main(int argc, char* argv[])
{
    tuple<string, int, int, float> t = std::make_tuple<string,int,int, float>("Mazen", 30,42, 151.25);
    // tuple<string, int, float> t = {"Mazen", 30, 151.25};

    auto &[name, age, age2, length] = t ;

    // name = get<0>(t);

    // for(auto [i,j,k] :  matrix )
    // {

    // }


    cout << name << " " << age << " " << age2 << " " << length << endl;

    // for(int i=0; i<4; i++)
    // {
    //     auto elem = get<i>(t);
    //     cout << elem <<endl;
    // }


}
