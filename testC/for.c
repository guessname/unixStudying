#include <stdio.h>
int main(void)
{
	int i;
	for(i = 0; i < 10; i++){
		int m = i;
		printf("%p\n", &m);	//sameaddr
	}
}