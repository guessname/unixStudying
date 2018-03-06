#include "common.h"


int main(void)
{
	strcpy(order1, "get_time_pos\n");
	strcpy(order2, "get_file_name\n");
	strcpy(porder2, "get_file_name\n");

	mkfifo("data", 0666);
	pid_t pid;
	system("./song");
	int fd[2] = {-1, -1};

	pipe(fd);
	pid = fork();
	if(pid == 0) {
	
			close(fd[0]);
			
			char buffer[100] = "./music/Hands.mp3";
			dup2(fd[1], 1);
			execlp("mplayer", "mplayer","-idle", "-slave", "-quiet", "-input", "file=data", buffer, (char *)0);
	}
	if(pid > 0) {

		pthread_t pid;
		pthread_t pidt;
		pthread_create(&pid, NULL, print_process, NULL);
		pthread_create(&pidt, NULL, get_key, NULL);

		pthread_detach(pid);
		pthread_detach(pidt);

		close(fd[1]);
		frist_process(fd);

	}

	return 0;
	

}
