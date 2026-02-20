#include <iostream>
using namespace std;


struct Counter
{

int m_count = 0;

    Counter& increment()
    {
        m_count++;
        return (*this);
    }
};



int test_method_chaining_main()
{
    Counter c1;

    c1.increment().increment().increment();

    cout << "current count: " << c1.m_count << endl ;
}