#include <stdio.h>

int main()
{
    int y = (1 + 2 * 3);
    int x = (1 + 2 * 3) - (5 + y * x) % 12;
    printf("Value is %d\n", x);
    return 0;
}