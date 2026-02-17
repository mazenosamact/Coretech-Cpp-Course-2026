# Micsillaneous excersies

## Print Binary
This is useful to see the binary representation of a number if needed.

```cpp
#include <stdio.h>
#include <stdbool.h>
#define GET_BIT(n,b) (((n)>>(b))&1)

void print_bin(int num)
{
    printf("0b");
    // 0b0001 1010 1110
    bool skip = true;
    for(int b=sizeof(int)-1 ; b != 0 ; b--)
    {        
        printf("%d", (GET_BIT(num,b)));
    }
}

int main(void)
{
    int num = 0x0A0B0C0D;

    print_bin(num);
    return 0;
}
```
