#include <stdio.h>  
#include <string.h>  
  
int main(int argc, char **argv)  
{  
    int *m = 1;  
    int *n = 2;  
    int const *p;
	p = m;
 
    p = n;           //error: assignment of read-only location ¡®*p¡¯  
    //test1 = 3;  
    printf("%d\n", *p);  
      
    return 0;  
} 