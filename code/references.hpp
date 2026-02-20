#include <iostream>
using namespace std;

int& returnRef()
{
    int x = 100;

    int& ref_x = x;

    return ref_x;
}


int add(int a, int b)
{
    int sum = a + b;
    return sum;
}

void add_with_ref(int a, int b, int& sum)
{
    sum = a + b ;
}

void swap(int& a, int& b)
{
    int temp ;

    temp = a;
    a = b ;
    b = temp;

}



int test_references_main() {


    int x = 10;
    // int& ref_x = x;

    // cout << "x=" << x << endl;
    // cout << "ref_x=" << ref_x << endl;

    int y = 15 ;
    // int main_sum = 0;

    // add_with_ref(x,y, main_sum);

    // cout << "main_sum=" << main_sum ;

    // int z = returnRef();

    cout << "before swap: " << "x=" << x << " y=" << y << endl;
    swap(x,y);
    cout << "after swap: " << "x=" << x << " y=" << y << endl;
    
    // reference to a pointer

    int* ptr_x = &x ;

    int*& ref_to_ptr = ptr_x ;

    cout << "ptr_x:" <<  ref_to_ptr << endl;

    // pointer to reference

    int& ref_x = x ;

    int* ptr_ref_x = &ref_x ; 

    return 0;
}
