#include "common.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 6666
#define MAX 1024

typedef struct udp
{
	char filename[MAX];
	long filelen;
}udpfile;

int main(int argc, char *argv[])
{
//	int ret;

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
		err_sys("socket fail\n");

	struct sockaddr_in myaddr;
	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(PORT);
//	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, "127.0.0.1", &myaddr.sin_addr);

	int fd = -1;
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		err_sys("open fail\n");

	udpfile file;
	bzero(&file, sizeof(file));
	strncpy(file.filename, argv[1], strlen(argv[1]));
	file.filelen = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	sendto(sockfd, &file, sizeof(file), 0, (struct sockaddr*)&myaddr, sizeof(myaddr));
//		err_sys("write fail\n"); 
	printf("%s %ld\n", file.filename, file.filelen);
	char buf[1024] = {0};

	while(1){
		int m;
		bzero(buf, 1024);
		m = read(fd, buf, 1024);
		//printf("%s\n", buf);
		usleep(30);		
		sendto(sockfd, buf, m, 0, (struct sockaddr*)&myaddr, sizeof(myaddr));
		if(m == 0)
			break;
	}
	close(fd);
	close(sockfd);

	return 0;
}