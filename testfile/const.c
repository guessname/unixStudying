#include <stdio.h>
int main(void)
{
	int i1=30;
	int i2=40;
	const int * pi=&i1;
	pi=&i2;    //4.注意这里，pi可以在任意时候重新赋值一个新内存地址
	i2=80;    //5.想想看：这里能用*pi=80;来代替吗？当然不能
	printf("%d", *pi );  //6.输出是80
	return 0;
}