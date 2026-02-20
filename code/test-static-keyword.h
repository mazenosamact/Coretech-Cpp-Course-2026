#include <iostream>
using namespace std;

class Counter
{
    int m_count, m_step;
    static int instances ;
public:
    Counter(int c= 0, int s=1):m_count(c), m_step(s)
    {
        instances ++ ;
    }

    static int getReferenceCount();

    Counter& inc(){ m_count+=m_step; return (*this); }
};

/** definition of static member */
int Counter::instances = 0;

int Counter::getReferenceCount()
{
    return instances ;
}

void test_static_keyword()
{
    // Counter counters[5] ;

    cout << "number of counters created is " << Counter::getReferenceCount()  << endl;
}