#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE	10

typedef int ElemType;
typedef int Status;//1-success, 0-failure
typedef int Bool;//1-true , 0-false

typedef struct queue_t{
	int size;
	int head;
	int tail;
	ElemType *q;
}Queue;

Queue * SQInitQueue(void)
{
	Queue *q = (Queue *)malloc(sizeof(Queue));
	if(q == NULL){
		printf("malloc queue struct fail\n");
		return NULL;
	}
	q->size = QUEUE_SIZE;
	q->q = (ElemType*)malloc(q->size * sizeof(ElemType));
	if(!q->q){
		free(q);
		printf("malloc queue space fail\n");
		return NULL;
	}
	q->head = q->tail = 0;
	return q;
}

Status SQIsFull(Queue *q)
{
	return ((q->tail - q->head) == q->size);//???????
}


Status SQEnQueue(Queue *q, ElemType e)
{
	assert(q);
	if(SQIsFull(q)){
		printf("queue is full\n");
		return 0;
	}
	q->q[q->tail % q->size] = e;
	q->tail++;
	return 1;
}
Status SQDeQueue(Queue *q, ElemType *e)
{
	assert(q);
	if(SQIsEmpty(q)){
		printf("queue is empty\n");
		return 0;
	}
	*e = q->q[q->head % q->size];
	q->head++;
	return 1;
}

Bool SQIsEmpty(Queue *q)
{
	assert(q);
	return q->tail == q->head;
}

int SQGetLength(Queue *q)
{
	return q->tail - q->head;
}

Status SQPrint(Queue *q)
{
	if(SQIsEmpty(q)){
		printf("queue is empty\n");
		return 0;
	}
	int i;
	for(i=0;i<SQGetLength(q);i++){
		printf("%d ",q->q[(i+q->head)%q->size]);
	}
	printf("\n");
	return 1;
}

Status SQFreeQueue(Queue *q)
{
	if(!q){
		printf("queue is null\n");
		return 0;
	}

	free(q->q);
	free(q);

	return 1;
}

int main(void)
{
	Queue *q=NULL;

	q = SQInitQueue();
	if(!q){
		return 1;
	}
	while(SQEnQueue(q,rand()%300));//填满队列
	SQPrint(q);
	ElemType e;
	while(SQDeQueue(q,&e))//出空队列
		printf("%d,",e);
	printf("\n");

	SQEnQueue(q,100);
	SQPrint(q);
	SQDeQueue(q,&e);
	SQEnQueue(q,120);
	SQPrint(q);
	SQEnQueue(q,160);
	SQPrint(q);
	SQEnQueue(q,10);
	SQPrint(q);

	SQFreeQueue(q);
	q=NULL;
	return 0;
}

