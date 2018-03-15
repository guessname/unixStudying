#include <stdio.h>
#define mul(a) (a)*(a)
int main(void)
{
    int a = 5, b, c;
    b = mul(a++);
    c = mul(++a);
    printf("%d %d %d\n", a, b, c);		//9  25  81
    if(!a && c++)
        b++;
    else
        c++;
    printf("%d %d\n", b, c);			//25  82
}