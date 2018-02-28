#include <stdio.h>
int f(int x)
{
	return (x * x);
}
int main(void)
{
	int m = f(3 + 5);
	printf("%d", m);
}