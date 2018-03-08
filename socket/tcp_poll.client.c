#include "common.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>

int main(void)
{
	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		err_sys("socket fail\n");
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

	int ret;
	ret = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret != 0)
		err_sys("connect fail\n");

	while(1){
		struct pollfd fd[2];
		bzero(fd, sizeof(fd));
		fd[0].fd = 0;
		fd[0].events |= POLLIN;

		fd[1].fd = sockfd;
		fd[1].events |= POLLRDNORM;

		poll(fd, 2, -1);
		if(fd[0].events &POLLIN){
			char buf[1024];
			fgets(buf, 1024, stdin);
			if(strncmp(buf, "stop", strlen("stop")) == 0)
				break;
			send(sockfd, buf, strlen(buf), 0);
		}

		if(fd[1].events & POLLRDNORM){
			char buff[1024];
			int ret = recv(sockfd, buff, 1024, 0);
			if(ret == 0){
				printf("server close\n");
				break;
			}
			buff[ret] = '\0';
			printf("%s\n", buff);
		}
	}
	close(sockfd);
	return 0;
}
