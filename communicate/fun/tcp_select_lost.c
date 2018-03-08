#include "my.h"
#include "list.h"
#include "print.h"
#include "temp.h"

struct list_head head;
struct list_head *pos;
List psave;
List *pps;
List psend;

int test_name(List *p)
{
	int fd = -1;
	Cdata msg;
	fd = open("datasave", O_RDONLY);
	if(fd == -1) {
		perror("open datasave\n");
		return 1;
	}
	while(read(fd, &msg, sizeof(Cdata))) {	
		
		if(strcmp((p->msg).name, msg.name) == 0) {
			return 2;
		}
	}

	return 0;

}

void fun1(List *p)
{

	int num;
	char buffer[50] = "该用户名已存在！\n";
	char buffer2[50] = "注册成功！\n";
	bzero(&psend, sizeof(List));

	num = test_name(p);
	if(num == 2) {
	
		strncpy(psend.infor, buffer, strlen(buffer));
		psend.status = 0;
		strcpy(psend.fromname, "服务器\n");
		write(pps->sendfd, &psend, sizeof(List));
		return ;
	}

	bzero(&psend, sizeof(List));
	strncpy(psend.infor, buffer2, strlen(buffer2));
	psend.status = 1;
	strcpy(psend.fromname, "服务器\n");
	write(pps->sendfd, &psend, sizeof(List));
		
	int fd = -1;
	fd = open("datasave", O_RDWR | O_CREAT | O_APPEND, 0666);
	if(fd == -1) {
		perror("open datasave error!\n");
		return ;
	}
	Cdata *pdata = NULL;
	pdata = malloc(sizeof(Cdata));
	if(pdata == NULL) {
		perror("malloc error!\n");
		return ;
	}

	strcpy((pps->msg).name, (p->msg).name);
	strcpy((pps->msg).password, (p->msg).password);

	strcpy(pdata->name, (p->msg).name);
	strcpy(pdata->password, (p->msg).password);

	write(fd, pdata, sizeof(Cdata));

	close(fd);
	free(pdata);
}

void fun2(List *p)
{
	List *pclifd = NULL;
	bzero(&psend, sizeof(List));

	list_for_each(pos, &head) {

		pclifd = mlist_entry(pos, List, list);

		if(strcmp(p->toname, (pclifd->msg).name) == 0) {
//			printf("%s\n", p->infor);
			strncpy(psend.infor, p->infor, strlen(p->infor));
			psend.status = 1;
			strncpy(psend.fromname, (pps->msg).name, strlen((pps->msg).name));
			write(pclifd->sendfd, &psend, sizeof(List));
			break;	
		}
		}
	
}

void fun3(List *p)
{
	int fd;
	Cdata msg;
	char buf1[20] = "登录成功\n";
	char buf2[20] = "密码不正确\n";
	char buf3[50] = "用户名不存在，请注册\n";
	fd = open("datasave", O_RDONLY);

	while(read(fd, &msg, sizeof(Cdata))) 
	{
	
		if(strcmp((p->msg).name, msg.name) == 0) 
		{
			if(strcmp((p->msg).password, msg.password) == 0) 
			{
				
				strcpy((pps->msg).name, (p->msg).name);
				strcpy((pps->msg).password, (p->msg).password);

				bzero(&psend, sizeof(List));
				strncpy(psend.infor, buf1, strlen(buf1));
				psend.status = 1;
				strcpy(psend.fromname, "服务器\n");
				write(pps->sendfd, &psend, sizeof(List));
				return ;
			}
			else 
			{
				bzero(&psend, sizeof(List));
				strncpy(psend.infor, buf2, strlen(buf2));
				psend.status = 0;
				strcpy(psend.fromname, "服务器\n");
				write(pps->sendfd, &psend, sizeof(List));
				return ;
			}
		}
	}

	bzero(&psend, sizeof(List));
	strncpy(psend.infor, buf3, strlen(buf3));
	psend.status = 0;
	strcpy(psend.fromname, "服务器\n");
	write(pps->sendfd, &psend, sizeof(List));

	close(fd);
	return ;

}

Table number[5] = {{1, fun1, NULL}, {2, fun2, NULL}, {3, fun3, NULL}};

int main(void) 
{
	int serfd;
	int consfd;
	int n;
	fd_set fdmsg;
	serfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serfd == -1)
		perror("socket error");
	
	struct sockaddr_in seraddr;
	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(PORT);

	inet_pton(AF_INET, "192.168.8.88", &(seraddr.sin_addr.s_addr));

	struct sockaddr_in saveaddr;
	bzero(&saveaddr, sizeof(saveaddr));
	socklen_t length = sizeof(saveaddr);
	char buffer[16];
	char buf[1024];
	bzero(buf, 1024);

	bind(serfd, (struct sockaddr*)&seraddr, sizeof(seraddr));

	listen(serfd, 5);
	printf("listening....\n");	

	INIT_LIST_HEAD(&head);
	List *pclifd;

	while(1) {
	
		FD_ZERO(&fdmsg);		
		FD_SET(serfd, &fdmsg);

		list_for_each(pos, &head) {

			pclifd = mlist_entry(pos, List, list);
			FD_SET(pclifd->sendfd, &fdmsg);
		}

		select(FD_SETSIZE, &fdmsg, NULL, NULL, NULL);

		if(FD_ISSET(serfd, &fdmsg)) {
		
			consfd = accept(serfd, (struct sockaddr*)&saveaddr, &length);
			if(consfd == -1)
				perror("accept error");
			printf("accept success.....\n");
			bzero(buffer, 16);
			inet_ntop(AF_INET, &(saveaddr.sin_addr.s_addr), buffer, 16);
			printf("IP: %s	PORT: %d\n", buffer, ntohs(saveaddr.sin_port));

			List *ptemp = NULL;
			ptemp = (List*)malloc(sizeof(List));
			ptemp->sendfd = consfd;
			list_add(&(ptemp->list), &head);
			continue;
		}

		list_for_each(pos, &head) {

			pclifd = mlist_entry(pos, List, list);
			if(FD_ISSET(pclifd->sendfd, &fdmsg)) {
		
				n = recv(pclifd->sendfd, &psave, sizeof(List), 0);
				pps = pclifd;
				if(n < 0) {
					perror("recv error!\n");
					break;
				}
				if(n > 0) {
					int i = 0;
					while(1) {
						if(number[i].pbit == psave.bit) {
						
							number[i].pfun(&psave);
							break;
						}
						i++;
						if(i == 5)
							break;
					}
				}
				if(n == 0) {
					printf("sockfd number is %d close!\n", pclifd->sendfd);
					close(pclifd->sendfd);
					FD_CLR(pclifd->sendfd, &fdmsg);
					list_del(&(pclifd->list));
					free(pclifd);
					break;
					}
			}

		}

	}

	close(serfd);
	return 0;

}
