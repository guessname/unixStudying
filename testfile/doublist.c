#include <stdio.h>
#include <stdlib.h>

typedef struct student{
	int num;
	char name[20];
	int score;

	struct student *next;
	struct student *prep;
}STU;

STU *init(void);
STU *double_insert(STU *head, STU *p_new);
void double_delete(STU **head, int num);
void print(STU *head);
STU *link_append(STU *head, STU *p_new);	

STU *init(void)
{
	STU *head = NULL;
	STU *p = NULL;
	int n = 0;

	while(1){
		p = (STU *)malloc(sizeof(STU));
		if(p == NULL){
			printf("malloc fail\n");
			break;
		}
#if 0
		p->num = 100 + n++;
		sprintf(p->name, "name%d", n);
		p->score = 100 - n;		

		
		if(strcmp(p->name, "name10") == 0){
			free(p);
			p = NULL;
			break;
		}

			head = link_append(head, p);
#endif	
	printf("input the num name score:\n");
	scanf("%d %s %d", &p->num, p->name, &p->score);
	getchar();

	if(strcmp(p->name, "quit") == 0){
		free(p);
		p = NULL;
		break;
	}
		STU *pf = link_append(head, p);
		if(head ==NULL)
			head = pf;

	}
	return head;
}


#if 1
STU *link_append(STU *head, STU *p_new)	
{
	if(head == NULL){
		head = p_new;
		p_new->next = NULL;
		p_new->prep = NULL;
	}else{
		STU *p = head;
		while(p->next != NULL){
			p = p->next;
		}
		p->next = p_new;
		p_new->prep = p;
		p_new->next = NULL;
	}
	return head;

}
#endif
#if 1
STU *double_insert(STU *head, STU *p_new)
{
	if(head ==NULL){
		head = p_new;
		p_new->next = NULL;
		p_new->prep = NULL;
	}else{
		STU *p_mov = head;
		while((p_new->num > p_mov->num) && (p_mov->next != NULL)){
			p_mov = p_mov->next;
		}
		
		if(p_new->num < p_mov->num){
			p_new->next = p_mov;
			p_mov->prep->next = p_new;
			p_new->prep = p_mov->prep;
			p_mov->prep = p_new;
		}else{
			p_mov->next = p_new;
			p_new->prep = p_mov;
			p_new->next = NULL;
		}

	}
	return head;
}
#endif
#if 1
void double_delete(STU **head, int num)
{
	STU *p_mov = *head;
	if(*head == NULL){
		return;
	}
	while(p_mov->num != num && p_mov->next != NULL){
		p_mov = p_mov->next;
	}
	if(p_mov->num != num && p_mov->next == NULL){
		printf("not found num\n");
		return;
	}
	if(p_mov == *head){
		if(p_mov->next){
			p_mov->next->prep = NULL;
			*head = p_mov->next;
		}else{
			p_mov->prep->next =NULL;
		}
	}
	else if(p_mov->num == num && p_mov->next != NULL){
		p_mov->prep->next = p_mov->next;
		p_mov->next->prep = p_mov->prep;
	}
	else{
		p_mov->prep->next =NULL;
	}
	
	free(p_mov);
}
#endif


void print(STU *head)
{
	STU *p = head;

	STU *p_save;
	if(head == NULL){
		printf("list empty\n");
		return;
	}
	
	while(p != NULL){
		printf("num:%d name:%s score:%d\n", p->num, p->name, p->score);
		p_save = p;
		p = p->next;
	}
	printf("*********************\n");
	while(p_save){
		printf("num:%d name:%s score:%d\n", p_save->num, p_save->name, p_save->score);
		p_save = p_save->prep;
	}
	
}

int main(void)
{
	STU *head = NULL;
	STU *p = NULL;
	int num;

	head = init();
	print(head);
	
	printf("input message num name score:");
//	scanf("%d %s %d", &p->num, p->name, &p->score);
	double_insert(head, p);

	printf("input delete num:");
	scanf("%d", &num);
	double_delete(&head, num);
	print(head);

	return 0;
}
