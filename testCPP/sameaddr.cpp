#include <iostream>
using namespace std;
int main(void)
{
	  // force to convert   
    const int x = 50;  
    int* y = (int *)(&x);       // ͬ���ĵ�ַ�����������ǲ�һ����  
    *y = 200;  
    cout << "x: "<<x<<" address: "<<&x<<endl;  
    cout << "*y: "<<*y<<" address: "<<y<<endl;  
    cout<<endl;
}