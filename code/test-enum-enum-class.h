

// #include <stdio.h>
#include <iostream>
using namespace std;

/** github: magic enum */
/** youtube, google: X-macros */


typedef enum  {
    NORTH = 0x10000000 ,SOUTH,WEST,EAST
}direction_t;

enum class eDirection : int8_t {
    South,West,East, North
};



void take_direction(direction_t direction)
{
    printf("direction is: %d\n", direction);
}

ostream& operator<<(eDirection)
{

}

auto directions[] = {
    "South","West","East", "North"
};

int size_arr = sizeof(directions)/sizeof(directions[0]) ;


void take_direction_cpp(eDirection dir)
{
    cout << "my direction is: " << static_cast<int>(dir) << endl;
}

int test_enum_enumclass_main()
{
    direction_t dir = (direction_t)15 ;
    take_direction(static_cast<direction_t>(15));
    take_direction(NORTH);
    take_direction_cpp(eDirection::North);
}

