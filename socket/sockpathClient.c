#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/un.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while (0)

void echo_ser(int conn)
{
    char recvbuf[1024];
    int n;
    while (1)
    {

        memset(recvbuf, 0, sizeof(recvbuf));
        n = read(conn, recvbuf, sizeof(recvbuf));
        if (n == -1)
        {
            if (n == EINTR)
                continue;

            ERR_EXIT("read error");
        }

        else if (n == 0)
        {
            printf("client close\n");
            break;
        }

        fputs(recvbuf, stdout);
        write(conn, recvbuf, strlen(recvbuf));
    }
    close(conn);
}

/* unix domain socket��TCP�׽�����Ƚϣ���ͬһ̨�����Ĵ����ٶ�ǰ���Ǻ��ߵ�������*/
int main(void)
{
    int listenfd;
    if ((listenfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
        ERR_EXIT("socket error");

    unlink("/tmp/test socket"); //��ַ����
    struct sockaddr_un servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, "/tmp/test socket");

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        ERR_EXIT("bind error");

    if (listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen error");

    int conn;
    pid_t pid;
    while (1)
    {
        conn = accept(listenfd, NULL, NULL);
        if (conn == -1)
        {
            if (conn == EINTR)
                continue;
            ERR_EXIT("accept error");
        }

        pid = fork();
        if (pid == -1)
            ERR_EXIT("fork error");
        if (pid == 0)
        {
            close(listenfd);
            echo_ser(conn);
            exit(EXIT_SUCCESS);
        }

        close(conn);
    }
    return 0;
}