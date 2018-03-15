#include <stdio.h>
struct a{
	char m;
	char n;
	char p;
};
struct b{
	struct a e;
	int v;
};
int main(void){
	struct b n;
	printf("%d", sizeof(n));	//8
}