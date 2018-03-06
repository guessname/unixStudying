#ifndef __COMMON_H
#define __COMMON_H

/*
	File		:common.h
	Description	:�Զ����ͷ�ļ����������õ�ϵͳͷ�ļ������õĺ꣬�Զ���Ĺ��ߺ���
*/

/*ͷ�ļ�ͳһ����*/

/*��׼ͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
/*linuxϵͳ����ͷ�ļ�*/
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>

#define BLUE "\033[0;32;24m"
#define RED "\033[0;31;24m"
#define NONE "\033[0m"
#define DEPBLUE "\033[0;34;24m"
#define CLEAR() printf("\033[2J")

#define MOVETO(x,y) printf("\033[%d;%dH", (y), (x))

#define MAXLINE 4096  /*һ�е���󳤶�*/


/*�Զ��庯��ԭ��*/
/*��err_��ͷ���Ǵ������������ڳ���ʱ��ӡ��ʾ��Ϣ��������ز���*/

/*ϵͳ������صķ��������󣬴�ӡ�û���ʾ��Ϣ��ϵͳ��ʾ��Ϣ��Ȼ�󷵻�*/
void err_ret(const char *msg, ...);

/*ϵͳ������ص��������󣬴�ӡ�û���ʾ��Ϣ��ϵͳ��ʾ��Ϣ��Ȼ��ֱ�ӵ���exit()��ֹ����*/
void err_sys(const char *msg, ...);

/*ϵͳ������ص��������󣬴�ӡ�û���ʾ��Ϣ��ϵͳ��ʾ��Ϣ����������ת���ļ���Ȼ�����exit()��ֹ����*/
void err_dump(const char *fmt, ...);

/*ϵͳ�����޹صķ��������󣬴�ӡ�û���ʾ��Ϣ��Ȼ�󷵻�*/
void err_msg(const char *msg, ...);

/*ϵͳ�����޹صķ��������󣬴�ӡ�û���ʾ��Ϣ��errorָ����ϵͳ��ʾ��Ϣ��Ȼ�󷵻�*/
void err_cont(int error, const char *msg, ...);

/*ϵͳ�����޹ص��������󣬴�ӡ�û���ʾ��Ϣ��Ȼ�����exit()��ֹ����*/
void err_quit(const char *msg, ...);

/*ϵͳ�����޹ص��������� ��ӡ�û���ʾ��Ϣ��errorָ����ϵͳ��ʾ��Ϣ��Ȼ�����exit()��ֹ����*/
void err_exit(int error, const char *msg, ...);
void setup_sigsegv(void); 
	

typedef struct data_t{

	int c_time;

	char data[80];

	struct data_t *next;
	struct data_t *prep;
}Data;

char order1[50];
char order2[50];
char porder2[50];

int num;
int bit;

int timet;
char **pt;
char name[100];
char c;
char *pword[4];


char p1word[20] ;
char p2word[20] ;
char p3word[20] ;
char p4word[20] ;

int Print_Song(Data *head);
int Print_Start(void);
int Frist_Manage(char *p);

Data *Open_File(Data *head,char *word);
Data *Manage_Data(Data *head,char *word);
Data *Creat_Data_Link(Data *head, int number, char *data);
int free_link(Data *head);
int print_sname(void);
char **count_order(void);
char **count_lrc(void);
void *get_key(void *);
void *print_process(void *);
int frist_process(int *fd);
#endif




















