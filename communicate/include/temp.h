#ifndef _TEMP_H_
#define _TEMP_H_

#define PORT 8888

typedef struct cdata{

	char name[20];
	char password[20];
}Cdata;


typedef struct list_t{

	int bit;
	int sendfd;
	int status;
	short port;
	char infor[1024];
	char toname[50];
	char fromname[50];
	char ip[16];
	Cdata msg;
	struct list_head list;

}List;

typedef struct _msg
{
	long mtype;
	int bit;
	char mtext[100];
}MSG;

typedef struct table{

	int pbit;
	void (*pfun) (List *p);
	int (*funs) (int serfd);
}Table;


#endif
