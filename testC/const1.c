#include <stdio.h>  
#include <string.h>  
  
int main(int argc, char **argv)  
{  
    int test1 = 1;  
    int test2 = 2;  
    int const *p = &test1;  //ֻ����������ʱ��͸�������ֵ�������ǻᱨ���  
  
    p = &test2;           //error: assignment of read-only location ��*p��  
    //test1 = 3;  
    printf("%d\n", *p);  
      
    return 0;  
} 