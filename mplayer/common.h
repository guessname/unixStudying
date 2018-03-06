#ifndef __COMMON_H
#define __COMMON_H

/*
	File		:common.h
	Description	:自定义的头文件，包含常用的系统头文件，常用的宏，自定义的工具函数
*/

/*头文件统一包含*/

/*标准头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
/*linux系统调用头文件*/
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

#define MAXLINE 4096  /*一行的最大长度*/


/*自定义函数原型*/
/*以err_开头的是错误处理函数，用于出错时打印提示信息并进行相关操作*/

/*系统调用相关的非致命错误，打印用户提示信息和系统提示信息，然后返回*/
void err_ret(const char *msg, ...);

/*系统调用相关的致命错误，打印用户提示信息和系统提示信息，然后直接调用exit()终止程序*/
void err_sys(const char *msg, ...);

/*系统调用相关的致命错误，打印用户提示信息和系统提示信息并产生核心转储文件，然后调用exit()终止程序*/
void err_dump(const char *fmt, ...);

/*系统调用无关的非致命错误，打印用户提示信息，然后返回*/
void err_msg(const char *msg, ...);

/*系统调用无关的非致命错误，打印用户提示信息和error指定的系统提示信息，然后返回*/
void err_cont(int error, const char *msg, ...);

/*系统调用无关的致命错误，打印用户提示信息，然后调用exit()终止程序*/
void err_quit(const char *msg, ...);

/*系统调用无关的致命错误， 打印用户提示信息和error指定的系统提示信息，然后调用exit()终止程序*/
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




















