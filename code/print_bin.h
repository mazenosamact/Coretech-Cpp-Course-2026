#include <stdio.h>
#include <stdbool.h>
#define GET_BIT(n,b) (((n)>>(b))&1)

void print_bin(int num, int left_zero_padding)
{
    printf("0b");
    // 0b0001 1010 1110
    int start_pos = (sizeof(int)*8)+left_zero_padding;
    for(int b=(sizeof(int)*8)-1 ; b >= 0 ; b--)
    {
        start_pos--;
        if(GET_BIT(num,b))
        {
            break;
        }
    }
    for(int b=start_pos ; b >= 0 ; b--)
    {        
        putc((GET_BIT(num,b))+'0', stdout);
    }
}

typedef struct
{
    int num;
    int padding;
}NumWithPadding_t;

int test_print_bin(void)
{
    NumWithPadding_t test_nums[] = {
        {3, 11}, 
        {5, 10} , 
        {9, 9} , 
        {20, 8} , 
        {125, 6} , 
        {253, 5} , 
        {400, 4}
    };
    int sz_test_nums = (sizeof(test_nums)/sizeof(test_nums[0]));
    for(int i=0; i < sz_test_nums; i++)
    {
        print_bin(test_nums[i].num, test_nums[i].padding);
        printf("\n");
    }
    return 0;
}