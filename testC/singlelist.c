#include <stdio.h>
#include <stdlib.h>

typedef struct data
{
	int data;

	struct data *next;
}DATA;

DATA *create(void)
{
	DATA *head = NULL;
	DATA *p = NULL;
	DATA *pf = NULL;
	int n = 0;

	p = (DATA *)malloc(sizeof(DATA));
	pf = p;
	if(p == NULL){
		printf("malloc fail\n");
		return;
	}
	
	printf("input num:");
	scanf("%d", &p->data);

	while(p->data != 0){
		n++;	
		if(head == NULL){
			head = p;
			p->next = NULL;
		}else{
			pf->next = p;
		}
		pf = p;
		p = (DATA *)malloc(sizeof(DATA));
		scanf("%d", &p->data);
	}
	pf = NULL;
	free(pf);

	return head;
}

void print(DATA *head)
{
	DATA *p = head;
	while(p != NULL){
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

DATA *insert(DATA *head, DATA *p_new)
{
	DATA *p, *p_mov;
	p = p_mov = head;
	
	if(head == NULL){
		head = p_new;
		p_new->next = NULL;
	}
	while((p_new->data > p_mov->data) && (p_mov->next != NULL)){
		p = p_mov;
		p_mov = p_mov->next;
	}
	if(p_new->data < p_mov->data){
		if(p_mov == head){
			p_new->next = p_mov;
			head = p_new;
		}else{
			p->next = p_new;
			p_new->next = p_mov;
		}
	}else{
		p_mov->next = p_new;
		p_new->next = NULL;
	}
	return head;
}

DATA *delete(DATA **head, int n)
{
	DATA *p, *p_mov;
	p = p_mov = *head;

	if(*head == NULL){
		printf("list empty\n");
		return;
	}
	while((p_mov->data != n) && (p_mov->next != NULL)){
		p = p_mov;
		p_mov = p_mov->next;
	}
	if((p_mov->data != n) && (p_mov->next == NULL)){
		printf("not found\n");
		return;
	}else{
		if(p_mov == *head){
			*head = p_mov->next;
		}else{
			p->next = p_mov->next;
		}
		free(p_mov);
	}
	return *head;

}
DATA *Free(DATA *head){
	DATA *p = head;
	while(p != NULL){
		free(p);
		p = p->next;
	}
	printf("success\n");
}

int main(void)
{
	DATA *head = NULL;
	int m = 0;
	head = create();
	print(head);

	DATA *p_new = NULL;
	p_new = (DATA *)malloc(sizeof(DATA));
	scanf("%d", &p_new->data);
	insert(head, p_new);
	print(head);

	scanf("%d", &m);
	delete(&head, m);
	print(head);

	Free(head);
	
	return 0;
}
