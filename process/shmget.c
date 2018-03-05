//�����֮�乲���ڴ����:

#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 1024

extern int errno;

int main()
{
	int shmid;
	char *shmptr;
	key_t key;
	pid_t pid;
	
	if((pid = fork()) < 0)
	{
	    printf("fork error:%s\n", strerror(errno));
	    return -1;
	}
	else if(pid == 0){
		sleep(2);
	    if((key = ftok("/dev/null", 1)) < 0){
			printf("ftok error:%s\n", strerror(errno));
	    	return -1;
	    }
		if((shmid = shmget(key, SIZE, 0600)) < 0){
	    	printf("shmget error:%s\n", strerror(errno));
	    	exit(-1);
	   	}
	
		if((shmptr = (char*)shmat(shmid, 0, 0)) == (void*)-1){
	   		 printf("shmat error:%s\n", strerror(errno));
	   		 exit(-1);
		}
		//memcpy(shmptr, "hello world", sizeof("hello world"));
		printf("child:pid is %d,share memory from %lx to %lx, content:%s	\n",getpid(), (unsigned long)shmptr, (unsigned long)(shmptr + 	SIZE), shmptr);
		printf("child process sleep 2 seconds\n");
		sleep(2);
		
		if((shmctl(shmid, IPC_RMID, 0) < 0)){
	   		printf("shmctl error:%s\n", strerror(errno));
	    	exit(-1);
		}
	   	exit(0);
	}
 	//parent
	else{
	    if((key = ftok("/dev/null", 1)) < 0){
     		printf("ftok error:%s\n", strerror(errno));
	     	return -1;
	    }
		
		if((shmid = shmget(key, SIZE, 0600|IPC_CREAT|IPC_EXCL)) < 0){
	    	printf("shmget error:%s\n", strerror(errno));
	   		exit(-1);
		}
	
		if((shmptr = (char*)shmat(shmid, 0, 0)) == (void*)-1){
	    	printf("shmat error:%s\n", strerror(errno));
	    	exit(-1);
		}
		memcpy(shmptr, "hello world", sizeof("hello world"));
		printf("parent:pid is %d,share memory from %lx to %lx, content:%s\n",getpid(),(unsigned long)shmptr, (unsigned long)(shmptr + SIZE
		), shmptr);
		printf("parent process sleep 2 seconds\n");
		sleep(2);
		
		if((shmctl(shmid, IPC_RMID, 0) < 0)){
	    	printf("shmctl error:%s\n", strerror(errno));
	    	exit(-1);
		}
	}
	
	waitpid(pid,NULL,0);
	exit(0);
}