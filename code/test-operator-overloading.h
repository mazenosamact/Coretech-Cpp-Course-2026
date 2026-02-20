



/**
 * @brief count, step
 * overload ctor
 * overload ++
 * 
 */
class Counter
{
    int m_count, m_step;
public:
    Counter(int c = 0 , int s = 1):m_count(c), m_step(s){}

    /** Pre-increment operator */
    void operator++()
    {
        m_count += m_step;
    }

    int operator++(int c)
    {
        (void)c ; // un-used
        m_count += m_step;
        return m_count;
    }

};


class CCartesianPoint
{

public:
    CCartesianPoint(int x, int y):m_x(x), m_y(y){}

    CCartesianPoint add(CCartesianPoint other)
    {
        return CCartesianPoint(
                        this->m_x + other.m_x , 
                        this->m_y + other.m_y 
        );
    }

    CCartesianPoint operator+(CCartesianPoint other)
    {
        return CCartesianPoint(
                        this->m_x + other.m_x , 
                        this->m_y + other.m_y 
        );
    }

    int operator*(CCartesianPoint other)
    {
        return (this->m_x*other.m_x + this->m_y+other.m_y) ;
    }


private:
    int m_x, m_y;

};

CCartesianPoint add(CCartesianPoint p1, CCartesianPoint p2)
{

}

void test_operator_overloading_main()
{
    CCartesianPoint p1(2,2) , p2(3,3);

    // CCartesianPoint p3 = p1.add(p2) ;
    CCartesianPoint p3 = p1 + p2 ;

    Counter c1; // default ctor

    ++c1 ;
    c1++ ;

    Counter c2(5), c3(10,2);
}