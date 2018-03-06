#include "common.h"

int frist_process(int *fd)

{
		
		char buffer[100];
		int fd_t;
		int i = 1;
		int t = 0;
		char temp[20];
		char sp[20];
		bzero(temp, 20);
		bzero(buffer, 100);
		pt = count_lrc();
		fd_t = open("data", O_WRONLY);
		while(1) {

		if(i == 1) {	
			write(fd_t, order1, strlen(order1));
			bzero(buffer, 100);
			read(fd[0], buffer, 100);
			sscanf(buffer, "%*[^=]=%[0-9]", temp);
			timet = atoi(temp);
			usleep(300000);
			i--;
		}
		if(i == 0) {
			if(strcmp(order2, porder2) != 0)
				t = 1;

			write(fd_t, order2, strlen(order2));

			if(t == 1) {
				if(strcmp(order2, "pause\n") == 0) {
					strcpy(sp, order2);
					while(1) {
						sleep(1);
						if(bit == 1)
							break;
					}
				}
				strcpy(order2, porder2);
				t = 0;
			}
			bzero(buffer, 100);
			usleep(300000);
			if(strcmp(sp, "pause\n") != 0)
				read(fd[0], buffer, 100);
			sscanf(buffer, "%*[^-]-%[^.]", name);
//			printf("%s\n", name);
			i++;	
		}
	}
	return 0;

}	


void *print_process(void *temp)
{
	
	usleep(500000);
	do {
		Data *head = NULL;
		char word[100];
		CLEAR();

		head = Open_File(head, word);
		Print_Start();

		Print_Song(head);
		free(head);
	} while(1);
				
	return NULL;
}

void *get_key(void  *temp)
{
	
	bit = 1;
	int sound = 0;
	char **p;
	num = 2;
	p = count_order();
	while(1) {

	scanf("%c", &c);
	switch(c) {
		case 'q':
				num++;
				strcpy(order2, p[num]);
				break;
		case 'a':
				num--;
				strcpy(order2, p[num]);
				break;
		case 'w':
				strcpy(order2, "seek +15\n");
				break;
		case 's':
				strcpy(order2, "seek -15\n");
				break;
		case 'k':
				bit = ~bit;
				strcpy(order2, "pause\n");
				break;
		case 'e':
				strcpy(order2, "volume 80 1\n");	
				break;
		case 'd':
				strcpy(order2, "volume 30 1\n");
				break;
		
		}
	usleep(300000);

	}

	return NULL;

}

int print_time(void)

{
	

}

int Print_Song(Data *head)
{

	int max = 0;
	int t = 0;
	int i = 0;
	char buffer[30] = "hahda";
	FILE *fp;
	
	fp = fopen("test", "r");
	Data *psave = head;
	while(head->next != psave){
	
		head = head->next;
	}
	max = head->c_time;
	head = psave;

	while(1){

		if(c == 'q' || c == 'a') {
			c = 'm';
			break;
			}

		MOVETO(75, 6);
		printf(BLUE"%02d:%02d"NONE,timet/60,timet%60);
		fflush(stdout);

		psave = head;
		do{
	
			if(t == 0) {
				MOVETO(4, 5);
				printf("歌曲目录:");
				while(fgets(buffer, 30, fp) != NULL) {
					
					if(i == num) {
						MOVETO(4,8+i);
						printf(DEPBLUE"%s"NONE, buffer);
						}
					else { 
						MOVETO(4,8+i);
						printf("%s", buffer);
						}	
					i++;	
				}
				rewind(fp);
				t++;
				}

				i = 0;

			if(timet == head->c_time){
				CLEAR();
				Print_Start();
	
				MOVETO(4, 5);
				printf("歌曲目录:");
				while(fgets(buffer, 30, fp) != NULL) {
					
					if(i == num) {	
						MOVETO(4,8+i);
						printf(DEPBLUE"%s"NONE, buffer);
						}
					else {
						MOVETO(4,8+i);
						printf("%s", buffer);
						}
					i++;	
				}
				rewind(fp);

				if(head != psave){
				MOVETO(70,8);
				printf("%s\n", head->prep->data);}
				MOVETO(70,9);
				printf(RED"%s\n"NONE, head->data);
				if(head->next != psave){
				MOVETO(70,10);
				printf("%s\n", head->next->data);
				MOVETO(70,11);
				printf("%s\n", head->next->next->data);}
				break;

			}
			if(timet > max)return 0;
			head = head->next;
		} while(head != psave);
		head = psave;
			usleep(300000);
		}

	return 0;
}

int Print_Start(void)
{
	int i;
	for(i = 0; i < 4; i++){
	
		if(i == 0){
			MOVETO(72,i+2);
			printf("歌曲名: %s\n", pword[i]);}
		if(i == 1){
			MOVETO(72,i+2);
			printf("演唱: %s\n", pword[i]);}
		if(i == 2){
			MOVETO(72,i+2);
			printf("专辑: %s\n", pword[i]);}
		if(i == 3){
			MOVETO(72,i+2);
			printf("乐队: %s\n", pword[i]);}

	}

	return 0;

}

int Frist_Manage(char *p)
{
	static int i = 0;

	if(i == 0) {
	pword[i] = p1word;
	sscanf(p, "%*[^:]:%[^]]", p1word);
	i++;
	return 0;
	}
	if(i == 1) {
	pword[i] = p2word;
	sscanf(p, "%*[^:]:%[^]]", p2word);
	i++;
	return 0;
	}
	if(i == 2) {
	pword[i] = p3word;
	sscanf(p, "%*[^:]:%[^]]", p3word);
	i++;
	return 0;
	}
	if(i == 3) {
	pword[i] = p4word;
	sscanf(p, "%*[^:]:%[^]]", p4word);
	i++;
	if(i == 4)
		i = 0;
	return 0;
	}

}


Data *Open_File(Data *head, char *word)
{
	Data *ptemp;
	int i = 0;

	Data *plink = head;
	FILE *fp;

	fp = fopen(pt[num], "r");
	if(fp == NULL){
	
		perror("open");
		return NULL;
	}

	while(fgets(word, 100, fp)){
		if(i<4){
			Frist_Manage(word);
//			printf("%s\n", word);
			i++;
		}
		else {

		ptemp = Manage_Data(plink, word);
		plink = ptemp;
		}
	}
	fclose(fp);
	
	return ptemp;
}


Data *Manage_Data(Data *head, char *word)
{
	Data *ptemp;
	Data *plink = head;
	char *p = word;
	char *psave;
	char *p1[10];
	char *t;
	int a;
	int b;
	int c;
	int i = 0;
	int number = 0;
	int num;	
	p1[i] = strtok(p,"[]");
	if(p[i]){
	i++;
	}

	while(1) {
		p1[i] = strtok(NULL,"[]");
		if(p1[i])
			i++;
		else {
			break;
		}	

	}

	num = i;
	i = 0;
	for(i = 0; i < num-1; i++){
		
		a = (*(p1[i])-48)*10 + (*(p1[i]+1)-48);
		b = (*(p1[i]+3)-48)*10 + (*(p1[i]+4)-48); 
		number = a*60 + b;
		psave = p1[num-1];
		ptemp = Creat_Data_Link(plink, number, psave);
		plink = ptemp;

	
	}


	return ptemp;


}

Data *Creat_Data_Link(Data *head, int number,char *data)
{
	Data *ptemp = head;
	Data *p;
	int i = 0;
	p = malloc(sizeof(Data));
	if(p == NULL){
	
		printf("malloc error!\n");
		return NULL;
	}
	p->c_time = number;
	strcpy(p->data,data);

	if(ptemp == NULL){
	
		ptemp = p;
		p->next = p;
		p->prep = p;

		return ptemp;
	}
	else {
		while((p->c_time >= ptemp->c_time) && (ptemp->next != head)){
		
			ptemp = ptemp->next;
		}

		if(p->c_time < ptemp->c_time){
		
			ptemp->prep->next = p;
			p->next = ptemp;
			p->prep = ptemp->prep;
			ptemp->prep = p;
		}
		else {
	
		ptemp->next = p;
		p->prep = ptemp;
		head->prep = p;
		p->next = head;
		}

		return head;
		
	}
}

int free_link(Data *head) 
{
	if(head == NULL) {
	
		perror("free!\n");
		return 1;
	}
	Data *psave;
	psave = head;
	while(head != NULL) {
	
		free(head);
		head = psave->next;
		psave = head;
	
	}

	return 0;


}
