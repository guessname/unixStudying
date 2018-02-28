#include <stdio.h>  
#include <string.h>  
  
int main(int argc, char **argv)  
{  
    int test1 = 1;  
    int test2 = 2;  
    const int *p;  
      
    p = &test1;  
    p = &test2;  
    //test2 = 3;  
    //*p = 4;     //error: assignment of read-only location ¡®*p¡¯  
    printf("%d\n", *p);  
      
    return 0;  
} 