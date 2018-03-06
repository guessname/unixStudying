#include <stdio.h>
#include "stack.h"

#define  INIT_SIZE 10
#define INSERT_SIZE 4

typedef int Elem;
typedef int Status;

typedef struct stack_t
{
	Elem *base;
	Elem *top;
	int stackSize;
}Stack;
Stack *InitStack(Stack *s)
{
	s = (Stack *)malloc(sizeof(Stack));
	if(s == NULL){
		printf("malloc fail\n");
		return NULL;
	}
	s->base = (Elem *)malloc(INIT_SIZE * sizeof(Elem));
	s->stackSize = INIT_SIZE;
	s->top = s->base;
	printf("init success\n");

	return s;
}

Status Free(Stack *s)
{
	if(s == NULL){
		printf("Stack NULL");
		return 0;
	}else{
		free(s->base);
		free(s);
		return 1;
	}
}

Status Push(Stack *s, Elem stat)
{
	assert(s);
	if((s->top - s->base) >= INIT_SIZE){
		printf("stack full\n");
		return 0;
#if 0
		s->base = (Elem *)realloc(s->base, (s->stackSize + INSERT_SIZE)\
				* sizeof(Elem));
		if(s->base == NULL){
			printf("malloc fail\n");
			return 0;
		}
		s->top = s->base + s->stackSize;
		s->stackSize += INSERT_SIZE;
#endif
	}
	*(s->top) = stat;
	++(s->top);

	return 1;
}

Status Pop(Stack *s, Elem *stat)
{
	assert(s);
	if(s->base == s->top){
		printf("stack empty\n");
		return 0;
	}
	--(s->top);
	*stat = *(s->top);

	return 1;
}

void print(Stack *s)
{
	assert(s);
	Elem *e = s->top;
	if(s->top == s->base){
		printf("stack empty\n");
		return;
	}
	e--;				//s->top指向栈顶元素的上一�?	for(;e != s->base; e--){
		printf("%d ", *e);
	}
	printf("\n");
}


int main(void)
{
	Stack *s = NULL;
	Elem sta = 1;
	int i = 1;

	s = InitStack(s);
	for(i = 1; i < 20; i++){
		Push(s, sta);
//		Pop(s, &sta);
//		printf("%d ", sta);
		sta += 1;
	}
//	printf("\n");
	print(s, sta);
	Free(s);
	s = NULL;

	return 0;
}
