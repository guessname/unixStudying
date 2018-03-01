#include <stdio.h>
#include <stdlib.h>

typedef struct _test Test;
struct _test{
	int m;
	Test *next;
};
int main(void)
{
	Test *p = NULL;
	Test *q = NULL;
	p = (Test *)malloc(sizeof(Test) *2);
	p->m = 3;
	q = (p + 1);
	p->next = q;
	q->m = 4;
	printf("%d\n", p->m);
	printf("%d\n", q->m);

	free(p);
	return 0;
}