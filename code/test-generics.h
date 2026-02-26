#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <sstream>
#include <any>
#include <algorithm>
#include <variant>
#include <utility>
#include <memory>

// uart class
// device manager --> smart pointer to uart class

using namespace std;

struct Point2D
{
    int x,y;
};

struct Point3D
{
    int x,y,z ;
    Point3D(int xx, int yy, int zz):x(xx),y(yy),z(zz){}
    string display() 
    {
        stringstream ss;
        ss << "(" 
        << x << "," 
        << y << ","
        << z << ","
        << ")" ;

        return ss.str();
    };
};


struct PointVisitor
{
    void operator()(Point2D p2d ) const {
        std::cout << "(" << p2d.x << "," << p2d.y  << ")" << std::endl;
    }
    
    void operator()(Point3D p3d ) const {
        std::cout << "(" << p3d.x << "," << p3d.y << "," << p3d.z  << ")" << std::endl;
    }
};


template<typename T>
T any_get(std::any x)
{
    T d;
    if(x.type() == typeid(T))
    {
        // std::cout << "any data:" << std::any_cast<T>(x) << std::endl;
        d = std::any_cast<T>(x);
        return d;
    }

    return d;
}


int test_generics_main(int argc = 0, char* argv[] = nullptr)
{

#if 0
    std::any x = 10;

    std::cout << "any int:" << std::any_cast<int>(x) << std::endl;
    
    x = 3.14 ;
    
    std::cout << "any currently has type:" <<  std::string(x.type().name()) << ",double typeid:"
    << typeid(double).name() << std::endl;
    
    // if(x.type() == typeid(double))
    // {
    //     std::cout << "any double:" << std::any_cast<double>(x) << std::endl;
    // }

    double dd = any_get<double>(x);

    x = std::string("Hello");

    std::string s = any_get<std::string>(x);

    std::any vec = std::vector<int>({1,2,3,4,5,6});

    std::vector<int> vec2 = any_get< std::vector<int> >(vec);


    std::for_each(vec2.begin(), vec2.end(), [](int& a){ std::cout<< a << " " ; });
    std::cout << std::endl;

    std::vector< std::any > any_vec ;
#endif

#if 0
    std::variant<int, float, std::string> var;

    var = 10 ;

    std::cout << "has int ? " << (std::holds_alternative<float>(var) ? "true":"false") << std::endl;
    
    var = "hello";
    
    std::cout << "has string ? " << (std::holds_alternative<std::string>(var) ? "true":"false") << std::endl;

    if(std::holds_alternative<std::string>(var))
    {
        std::cout << "The string in variant is: " << std::get<std::string>(var) << std::endl;
    }
    

    // visitor pattern
    std::variant<Point2D, Point3D> var_point;

    Point2D p1 = {10,20};
    Point3D p2 = {40,50,60};
    var_point = p1;
    std::visit(PointVisitor(), var_point);

    var_point = p2;
    std::visit(PointVisitor(), var_point);
#endif

#if 0
    typedef std::variant<int , float, std::string> Variant;
    vector< Variant > var_vec;
    std::string v;
    int i; float f; std::string s;
    while(std::cin >> v)
    {
        std::stringstream ss(v);
        ss >> i >> f >> s ;
    }

    var_vec.push_back(i);
    var_vec.push_back(f);
    var_vec.push_back(s);

    auto visitor = [](auto& v){
        cout << "I am " << typeid(v).name()  << " datatype" <<endl;
    };

    for_each(var_vec.begin(), var_vec.end(), [&](Variant& v){
        visit(visitor, v);
    });
#endif

#if 0
    unique_ptr<int> un_int = make_unique<int>(15); // good practice

    cout << *un_int << endl;

    cout << un_int.get() << endl;

    unique_ptr<int> un_int2;

    // un_int2 = un_int; compile error: operator= deleted

    unique_ptr<Point3D> un_p3d(new Point3D(1,2,3)) ; // fair but dont use.

    cout << "point is: " << un_p3d->display() << endl;
    
    unique_ptr<Point3D> un_p3d2 = move(un_p3d);
    
    cout << "point (after move )is: " << un_p3d2->display() << endl;

    if(!un_p3d) cout << "old point is now null" << endl;
#endif

    shared_ptr<int> sh_int = make_shared<int>(20);

    shared_ptr<int> sh_int2 = sh_int;

    cout << "ref count for sh_int: " << sh_int.use_count() << endl;
    cout << "ref count for sh_int2: " << sh_int2.use_count() << endl;

    shared_ptr<int> sh_int3(new int(50));

    cout << *sh_int3 << " , ref count: " << sh_int3.use_count() << endl ;

    sh_int2.reset();

    if(!sh_int2) cout << "sh_int2 is now null and ref_count: " << sh_int.use_count() << endl;


    return 0;
}