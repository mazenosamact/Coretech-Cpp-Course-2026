// #include <iostream>
// #include <cstring>
// using namespace std;
#include <stdio.h>

union IntToBytes {
    int intValue;
    unsigned char bytes[4];
};

typedef enum 
{
    NO_TYPE,
    STRING,
    FLOAT,
    CHAR,
    INTEGER,
}DATATYPE;


typedef struct {
    union {
        char name[15];
        int i;
        float f;
        char c;
    }data;
    DATATYPE tag;
}Listelement;

int test_union_main() {
    
#if 0
    IntToBytes data;
    data.intValue = 0x12345678;
    
    cout << "Integer: " << hex << data.intValue << endl;
    cout << "As bytes: ";
    for (int i = 0; i < 4; i++) {
        cout << hex << (int)data.bytes[i] << " ";
    }
    cout << endl;
#endif


#if 1
Listelement list[] = {
    { .data = {.name="Mazen"}, .tag=STRING },
    { .data = {.i = 52}, .tag = INTEGER},
    { .data.c = 'S', .tag = CHAR},
    { .data.f = 15.25, .tag = FLOAT}
};
int list_sz = (sizeof(list)/sizeof(list[0]));

for(int i=0; i<list_sz; i++)
{
    DATATYPE type = list[i].tag;
    switch(type)
    {
        case STRING:
            printf("%s",list[i].data.name );
        break;
        case FLOAT:
            printf("%lf", list[i].data.f);
        break;
        case CHAR:
            printf("%c", list[i].data.c);
        break;
        case INTEGER:
            printf("%d", list[i].data.i);
        break;
        case NO_TYPE:
        default:
            printf("Not a valid type");
        break;
    };

    printf("\n");
}
#endif

    return 0;
}

