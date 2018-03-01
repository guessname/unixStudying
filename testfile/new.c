#include <stdio.h>
int main(void)
{
	  // force to convert   
    const int x = 30;  
    int *y = (int *)(&x);       // 同样的地址，但是内容是不一样的  
    *y = 100; 
    printf("%d\t%p\n", x, &x);
    printf("%d\t%p\n", *y, y);
}