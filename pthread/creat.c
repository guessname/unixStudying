#include "common.h"
#include <pthread.h>
/*
void *pfun(void *tmp)
{
	static int ret;
	int a = (int)tmp;
	printf("%d\n", a);
	pthread_exit(&ret);
}*/
struct thread_g
{
	void* (*pfun)(void*, void*, void*, void*);
	void *arg1;
	void *arg2;
	void *arg3;
	void *arg4;
};

static void *sa(void *tmp)
{
	struct thread_g *p = (struct thread_g *)tmp;
	(p->pfun)(p->arg1,p->arg2, p->arg3, p->arg4); 
}

void *pthreadad(pthread_t *pid, void *(*pfun)(void*, void*, void*, void*), void*a, void*b, void*c, void*d)
{
	struct thread_g arg;
	arg.pfun = pfun;
	arg.arg1 = a;
	arg.arg2 = b;
	arg.arg3 = c;
	arg.arg4 = d;

	pthread_create(pid, NULL, sa, &arg);
	pthread_join(*pid, NULL);
}

void *test(void *a, void *b, void *c, void *d)
{
	printf("%d\n", *(int *)a);
	printf("%d\n", *(int *)b);
	printf("%s\n", *(char **)c);
	printf("%f\n", *(float *)d);	
}

int main(void)
{
	pthread_t pid;
/*	void *p;
	pthread_creat(&pid, NULL, pfun, (void*)3);
	pthread_join(pid, &p);
	printf("%d\n", *((int *)p));
*/	int a = 1;
	int b = 2;
	char *c ="hello";
	float f = 3.14;
	pthreadad(&pid, test, (void*)&a, (void*)&b, (void*)&c , (void*)&f);
	return 0;
}