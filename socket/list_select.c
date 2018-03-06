#include "common.h"
#include "list.h"
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct
{
	int clifd;
	char name[20];
	struct list_head list;
}structlist;

typedef struct
{
	char sname[20];
	char rname[20];
	char msg[1024];
}stumsg;

int main(int argc, char *argv[])
{
	int ret;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		err_sys("socket fail\n");

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

	ret = bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(ret < 0)
		err_sys("bind fail\n");

	ret = listen(sockfd, 5);
	if(ret < 0)
		err_sys("listen fail");
	printf("listen......\n");

	struct list_head head;
	INIT_LIST_HEAD(&head);

	struct list_head *pos;
	structlist *pclient;
	while(1){
		fd_set set;
		FD_ZERO(&set);
		FD_SET(sockfd, &set);

		list_for_each(pos, &head){
			pclient = list_entry(pos, structlist, list);
			FD_SET(pclient->clifd, &set);
		}

		ret = select(FD_SETSIZE, &set, NULL, NULL, NULL);
		if(ret < 0)
			err_sys("select fail\n");
		
		if(FD_ISSET(sockfd, &set)){
			struct sockaddr_in cliaddr;
			socklen_t addlen = sizeof(cliaddr);

			int clifd = accept(sockfd, (struct sockaddr*)&cliaddr, &addlen);
			char buf[20] = {0};
			recv(clifd, buf, 20, 0);
			char ip[16] = {0};
			printf("client %s addr:%s\n", buf, inet_ntop(AF_INET, &cliaddr.sin_addr, ip, 16));
			printf("port: %d\n", ntohs(cliaddr.sin_port));
			//printf("%s\n", buf);
			
			structlist *tmp = (structlist *)malloc(sizeof(structlist));
			tmp->clifd = clifd;
			strcpy(tmp->name, buf);
			list_add(&(tmp->list), &head);
			continue;
		}

		list_for_each(pos, &head){
			pclient = list_entry(pos, structlist, list);
			if(FD_ISSET(pclient->clifd, &set)){
				stumsg sendmsg;
				bzero(&sendmsg, sizeof(sendmsg));
				int n = recv(pclient->clifd, &sendmsg, 1064, 0);
				if(n < 0)
					err_sys("recv fail\n");
				else if(n == 0){
					printf("client close\n");
					close(pclient->clifd);

					list_del(&(pclient->list));
					free(pclient);
					break;
				}else{
					//buf[n] = '\0';
					printf("%s to %s :%s\n", sendmsg.sname, sendmsg.rname, sendmsg.msg);
					int sendfd;
					list_for_each(pos, &head){
						pclient = list_entry(pos, structlist, list);
						if(strcmp(pclient->name, sendmsg.rname) == 0){
							sendfd = pclient->clifd;
						//	printf("%d\n", sendfd);
						}
						send(sendfd, &sendmsg, sizeof(sendmsg), 0);
					}
				}

			}

		}
	}
	struct list_head *m;
	list_for_each_safe(pos, m, &head){
		pclient = list_entry(pos, structlist, list);
		free(pclient);
	}
	return 0;
}