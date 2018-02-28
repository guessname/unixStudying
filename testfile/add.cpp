#include <stdio.h>  
#include <iostream>  
using namespace std;  
  
int main() {  
    int value, value2;  
      
        //A  
    int a = 3;  
    printf("printf a: %d  %d\n", a++, a++);  
    cout << "after a: " << a << endl << endl;  
  
        //B  
        int d = 3;  
    cout << "cout d: " << d++ << " " << d++ << endl;  
    cout << "after d: "  << d << endl << endl;  
  
        //C  
    int c = 3;  
    printf("printf c: %d  %d\n", c++, ++c);  
    cout << "after c: " << c << endl << endl;  
  
        //D          
        int b = 3;  
    cout << "cout b: " << b++ << " " << ++b << endl;  
    cout << "after b: " << b << endl << endl;  
  
        //E 该部分代码是<span style="color:#3366FF;">《程序员面试宝典第四版32页》的题</span>  
    int arr[] = {6,7,8,9,10};  
    int *ptr = arr;  
    *(ptr++) += 123;  
//    printf("%d, %d\n", *(ptr++), *(++ptr));  
        cout << *(ptr++) << " " << *(++ptr) << endl;  
 }  