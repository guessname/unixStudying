#include <stdio.h>
#include <stdlib.h>

typedef struct _test Test;
struct _test{
	int m;
	Test *next;
};
void test(Test *n){
	printf("%d\n", n->next->m);
}
int main(void)
{
	Test *p = NULL;
	Test *q = NULL;
	p = (Test *)malloc(sizeof(Test) *2);
	p->m = 3;
	q = (p + 1);
	p->next = q;
	q->m = 4;
	
	Test n;
	n.next = p->next;
	printf("%d\t", p->m);
	printf("%d\n", p->next->m);
	
	printf("%d\t", n.next->m);
	
	test(&n);

	free(p);
	return 0;
}