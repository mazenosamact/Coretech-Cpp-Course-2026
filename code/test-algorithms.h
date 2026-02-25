#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <iterator>

using namespace std;


class NumChecker
{
    bool isEven(int n){return (n%2 == 0); }
    bool isOdd(int n){return !isEven(n); }
    bool isPrime(int n){ return false; }
public:
    enum { CHECK_EVEN, CHECK_ODD, CHECK_PRIME };
    bool operator()(int check, int num)
    {
        switch(check)
        {
            case CHECK_EVEN: return isEven(num);
            case CHECK_ODD: return isOdd(num);
            case CHECK_PRIME: return isPrime(num);
            default: return false;
        }
    }
#if 0
    bool operator()(int check, int num)
    {
        switch(check)
        {
            case CHECK_EVEN: return isEven(num);
            case CHECK_ODD: return isOdd(num);
            case CHECK_PRIME: return isPrime(num);
            default: return false;
        }
    }
#endif
};

// map<string, NumChecker>



string join(string acc, string next)
{
    return (acc + ',' + next) ;
}

bool isEven(int a)
{
    return (a%2 == 0) ;
}

void print_int(int a){ cout << a << ' ' ; }

int test_algorithm(int argc=0, char* argv[] = nullptr)
{
#if 0
    vector<string> csv_line = { "Name" , "age" , "length" };

    string joined = accumulate(csv_line.begin()+1, csv_line.end() ,
                                csv_line[0], join);

    // joined = joined.erase(0,1);
    cout << joined << endl;
    
    vector<string> copied;
    // copied.reserve(csv_line.size());
    // cout << "size after reserve:" << copied.size() << endl;
    // copied.resize(csv_line.size());
    // cout << "size after resize:" << copied.size() << endl;

    // copied.push_back(string());
    // copied.push_back(string());
    // copied.push_back(string());

    cout << "sizeof(csv_line): " << csv_line.size() << endl;
    cout << "sizeof(copied): " << copied.size() << endl;
    copy(csv_line.begin(), csv_line.end(), back_inserter(copied));
    
    joined = accumulate(copied.begin()+1, copied.end() ,
                        copied[0], join);
    cout << "copied: " << joined << endl;
#endif

    vector<int> nums = {1,2,3,4,5,6,7,8,9,10};

    vector<int> evens;

    copy_if(nums.begin(), nums.end(), back_inserter(evens), [](int a) -> bool { return (a%2 == 0); } );

    // for_each(evens.begin(), evens.end(),print_int );
    for_each(evens.begin(), evens.end(), 
        [](int& a){ cout << a << ' ' ; } 
    ); // lamda expression/function --> anonymous function
    cout << endl;
    NumChecker checker;

    cout << (checker(NumChecker::CHECK_EVEN, 42) ? "true":"false") << endl; 

    vector<int> scaled_by_10 ;

    transform(nums.begin(), nums.end(), back_inserter(scaled_by_10), 
        [](int n){ return (n*10); });
    
    for_each(scaled_by_10.begin(), scaled_by_10.end(), [](int n){ cout << n << ' '; });
    cout <<endl;
}