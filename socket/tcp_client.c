#include "common.h"
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8888

int main(void)
{
	int ret;
	//创建套接字
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		err_sys("socket error");

	//定义地址结构，用于connect操作
	struct sockaddr_in dstaddr;
	bzero(&dstaddr, sizeof(dstaddr));
	dstaddr.sin_family = AF_INET;
	dstaddr.sin_port = htons(PORT);
	inet_pton(AF_INET, "192.168.0.34", &dstaddr.sin_addr);

	//发起连接
	ret = connect(sockfd, (struct sockaddr*)&dstaddr, sizeof(dstaddr));
	if(ret < 0)
		err_sys("connect error");

	printf("connect success\n");
	
	char buffer[1024] = {0};
	fgets(buffer, 1024, stdin);

	//发送数据
	send(sockfd, buffer, strlen(buffer), 0);

	int n;
	n = recv(sockfd, buffer, 1024, 0);
	buffer[n] = '\0';
	printf("client recv:%s\n", buffer);

	close(sockfd);
	return 0;
}


















