#include "common.h"
#include <signal.h>

int global = 1;
void handler1(int signa)
{
	int global = 5;
	printf("%d\n", global);
	sleep(1);
}
void handler2(int signa)
{
	//global = 0;
	sleep(3);
}

int main(void)
{
	pid_t pid, ppid;
	pid = fork();
	if(pid < 0){
		err_sys("fork fail\n");
	}else if(pid == 0){
		while(1){
			ppid = getppid();
			sleep(3);
			kill(ppid, SIGALRM);
			signal(SIGINT, SIG_IGN);
		}
	}else{
		while(1){
			signal(SIGALRM, handler1);
			//signal(SIGALRM, SIG_DFL);
			int ret;	
			struct sigaction s;
			bzero(&s, sizeof(s));

			s.sa_handler = handler2;
			sigemptyset(&s.sa_mask);
			sigaddset(&s.sa_mask, SIGALRM);
			s.sa_flags = 0;

			ret = sigaction(SIGINT, &s, NULL);
			if(ret < 0){
				err_sys("sigaction fail");
			}
			printf("%d\n", global);
			sleep(1);
		}
	}
	return 0;
}