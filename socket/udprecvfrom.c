#include "common.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <fcntl.h>
#define PORT 6666
#define MAX 1024
typedef struct udp
{
	char filename[MAX];
	long filelen;
}udpfile;

int main(void)
{
	int ret;

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
		err_sys("socket fail\n");

	struct sockaddr_in local;
	bzero(&local, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_port= htons(PORT);
//	local.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, "127.0.0.1", &local.sin_addr);

	ret = bind(sockfd, (struct sockaddr*)&local, sizeof(local));
	if(ret < 0)
		err_sys("bind fail\n");

	
	int n;
	char buf[1024];
	struct sockaddr_in addr;
	socklen_t addrlen;
	addrlen = sizeof(addr);
	bzero(&addr, sizeof(addr));

	udpfile file;
	bzero(&file, sizeof(file));
	recvfrom(sockfd, &file, sizeof(file), 0, (struct sockaddr*)&addr, &addrlen);
	//			err_sys("read fail\n");
	printf("%s %ld\n", file.filename, file.filelen);

	int fd = -1;
	fd = open(file.filename, O_WRONLY|O_CREAT, 0666);
	if(fd < 0)
		err_sys("open fail\n");
	while(1){	
		n = recvfrom(sockfd, buf, 1024, 0, (struct sockaddr*)&addr, &addrlen);
		if(n > 0){
			//buf[n] = '\0';
			//printf("%s\n", buf);
			write(fd, buf, n);		//strlen()
			//sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
	}else{
			printf("receive finish\n");
			break;
		}
	}
	close(fd);
	close(sockfd);
	return 0;
}