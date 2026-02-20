


int add(int a, int b){
    return a+b;
}


float add(float a, float b)
{
    return a+b;
}

void test_func_overloading_main()
{
    int x=5 , y=6 ;

    int z = add(x,y);

    float x2=5.25, y2 = 6.5;

    int z2 = add(x2,y2);

    float z3 = add(x2,6);




}