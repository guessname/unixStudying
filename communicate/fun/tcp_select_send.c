#include "my.h"
#include "list.h"
#include "print.h"
#include "temp.h"

List data;
List psave;
int limit = 0;

int display_table(void)
{
	printf("================操作面板===============\n");
	printf("1-------->用户注册\n");
	printf("2-------->单人聊天\n");
	printf("3-------->用户登录\n");
	printf("4-------->传输文件\n");
	printf("5-------->显示在线人数\n");
	printf("6-------->退出客户端\n");

	return 0;

}

int new_built(int serfd) 
{
	if(limit == 0) {
		
		printf("请输入用户名：\n");
		fgets(data.msg.name, 20, stdin);
		printf("请输入密码：\n");
		fgets(data.msg.password, 20, stdin);

		send(serfd, &data, sizeof(List), 0);
		limit += 1;
	}
	else {
		printf(RED"用户已登录或注册，无效操作！\n"NONE);
	}

	return 0;


}
int user_login(int serfd)

{
	if(limit == 0) {
		
		printf("请输入用户名：\n");
		fgets(data.msg.name, 20, stdin);
		printf("请输入密码：\n");
		fgets(data.msg.password, 20, stdin);

		send(serfd, &data, sizeof(List), 0);
		limit += 1;
	}
	else {	
		printf(RED"用户已登录或注册，无效操作！\n"NONE);
	}

	return 0;

}

int get_onling(int serfd)
{
	printf(BLUE"=============当前在线的客户==============\n"NONE);
	send(serfd, &data, sizeof(List), 0);

	return 0;
}

int chat_other(int serfd)
{

	printf("请输入聊天用户名：\n");
	fgets(data.toname, 50, stdin);

	while(1) {

		printf("待输入：。。。。。\n");
		fgets(data.infor, 1024, stdin);
		if(strncmp(data.infor, "stop", 4) == 0)
			break;
		send(serfd, &data, sizeof(List), 0);
		bzero(data.infor, 1024);
	}

	return 0;
}

int recv_file(void)
{
	int fd;
	int ret;
	int filefd;
	int n;
	char buffer[1024];

	bzero(buffer, 1024);
	filefd = socket(AF_INET, SOCK_STREAM, 0);
	if(filefd == -1)
		perror("socket error");
	
	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(psave.port);
	inet_pton(AF_INET, psave.ip, &seraddr.sin_addr.s_addr);

	ret = connect(filefd, (struct sockaddr*)&seraddr, sizeof(seraddr));
	if(ret == -1)
		perror("connect error");
	printf("connect success\n");

	fd = open(psave.infor, O_RDWR | O_CREAT, 0666);
	while(1) {
		n = recv(filefd, buffer, 1024, 0);
		if(n > 0) {
			printf("%s", buffer);
			write(fd, buffer, n);
			bzero(buffer, 1024);
			}
		else {
			break;
		}	
	}

	close(fd);
	close(filefd);

	return 0;

}

int send_file(int serfd)
{

	int fd;
	int filefd;
	int consfd;
	int n;

	printf("请输入对方的用户名：\n");
	fgets(data.toname, 50, stdin);
	printf("请输入需要发送得文件名：\n");
	scanf("%s", data.infor);
	data.port = 9999;
	send(serfd, &data, sizeof(List), 0);

	filefd = socket(AF_INET, SOCK_STREAM, 0);
	if(filefd == -1)
		perror("socket error");
	
	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(9999);
	inet_pton(AF_INET, "192.168.1.44", &seraddr.sin_addr.s_addr);

	struct sockaddr_in saveaddr;
	bzero(&saveaddr, sizeof(saveaddr));
	socklen_t length = sizeof(saveaddr);

	bind(filefd, (struct sockaddr*)&seraddr, sizeof(seraddr));

	listen(filefd, 5);
	printf("等待对方接收\n");	
	consfd = accept(filefd, (struct sockaddr*)&saveaddr, &length);
	if(consfd == -1) {
		perror("accept error");
		return 1;
	}
	printf("传输就绪， 马上传输\n");
	
	fd = open(data.infor, O_RDONLY, 0666);
	if(fd == -1)
		perror("open file error!\n");
	while(1) {
		
		n = read(fd, &data.infor, 1024);
		if(n == 0)
			break;
		send(consfd, &data.infor, n, 0);
		usleep(3000);
	}

	return 0;

}

void *recv_msg(void *temp)
{

	fd_set fdmsg;

	int serfd = (int)temp;
	int n = 0;
	while(1) {

		FD_ZERO(&fdmsg);
		FD_SET(serfd, &fdmsg);

		select(FD_SETSIZE, &fdmsg, NULL, NULL, NULL);

		if(FD_ISSET(serfd, &fdmsg)) {
			n = recv(serfd, &psave, sizeof(List), 0);
			if(n > 0) {
				if(psave.status == 2) {
					printf(BLUE"%s"NONE, psave.infor);
				}
					else if(psave.status == 3) {
						recv_file();
					}
						else {
							printf(RED"来自：%s"NONE, psave.fromname);
							printf(RED"信息为：%s"NONE, psave.infor);
							if(psave.status == 0)
							limit -= 1;
						}
		bzero(psave.infor, 1024);
		}

	}

	}

	return NULL;
}

Table number[5] = {{1, NULL, new_built}, {2, NULL, chat_other}, {3, NULL, user_login},{4, NULL, send_file},{5, NULL, get_onling}};

int main(void) 

{
	int serfd;
	int ret;
	int i;
	serfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serfd == -1)
		perror("socket error");
	
	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(PORT);
	inet_pton(AF_INET, "192.168.8.88", &seraddr.sin_addr.s_addr);

	ret = connect(serfd, (struct sockaddr*)&seraddr, sizeof(seraddr));

	if(ret == -1)
		perror("connect error");
	printf("connect success\n");

	pthread_t fd;
	fd = pthread_create(&fd, NULL, recv_msg, (void *)serfd);
	pthread_detach(fd);

	CLEAR();
	MOVETO(1, 1);
	
	while(1) {
		
		display_table();
		printf("选择操作:\n");
		scanf("%d", &(data.bit));
		getchar();
		if(data.bit == 6)
			break;
		for(i = 0; i < 5; i++) {
		
			if(number[i].pbit == data.bit)
			{
				number[i].funs(serfd);
				break;
			}
		}

		usleep(50000);
	}

	close(serfd);

	return 0;

}
