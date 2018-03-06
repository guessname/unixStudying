#include "common.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

typedef struct
{
	char sname[20];
	char rname[20];
	char msg[1024];
}stumsg;

void *recvmag(void *tmp)
{	
	int clifd = (int)tmp;
	while(1){	
		fd_set setfd;
		FD_ZERO(&setfd);
			//FD_SET(0, &setfd);
		FD_SET(clifd, &setfd);

		select(FD_SETSIZE, &setfd, NULL, NULL, NULL);
		if(FD_ISSET(clifd, &setfd)){
			int ret;
			stumsg sendmsg;
			bzero(&sendmsg, sizeof(sendmsg));
			ret = recv(clifd, &sendmsg, 1064, 0);
			if(ret == 0){
				printf("server close\n");
				break;
			}
			printf("%s %s %s\n", sendmsg.sname, sendmsg.rname, sendmsg.msg);
		}
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
		err_sys("usage: client serverip\n");

	int clifd = socket(AF_INET, SOCK_STREAM, 0);
	if(clifd < 0)
		err_sys("socket fail\n");

	struct sockaddr_in cliaddr;
	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(6666);
	inet_pton(AF_INET, "127.0.0.1", &cliaddr.sin_addr);

	int ret;
	ret = connect(clifd, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
	if(ret < 0)
		err_sys("connect fail\n");
	printf("%s connect success\n", argv[1]);
	char buf[20] = {0};
	strncpy(buf, argv[1], strlen(argv[1]));
	send(clifd, buf, strlen(buf), 0);

	pthread_t fd;
	fd = pthread_create(&fd, NULL, recvmag, (void *)clifd);
	pthread_detach(fd);
	while(1){

		//if(FD_ISSET(0, &setfd)){
			//char buf[1024];
		stumsg sendmsg;
		bzero(&sendmsg, sizeof(sendmsg));
		strncpy(sendmsg.sname, argv[1], strlen(argv[1]));
		strncpy(sendmsg.rname, argv[2], strlen(argv[2]));
		//printf("%s:", sendmsg.sname);
		fgets(sendmsg.msg, 1024, stdin);
		if(strncmp(sendmsg.msg, "stop", sizeof("stop")) == 0)
			break;
		send(clifd, &sendmsg, sizeof(sendmsg), 0);
	//}

		//sendmsg.msg[ret] = '\0';
			//printf("%s\n", sendmsg.msg);
	}
	close(clifd);
	return 0;
}