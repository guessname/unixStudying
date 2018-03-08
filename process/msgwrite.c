#include "common.h"
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct msg
{
	long mtype;
	char mname[20];
}MSG;

int main(void)
{
	key_t key;
	int msgid;
	MSG msg;
	int i;

	key = ftok("./", 123);
	if(key < 0)
		err_sys("ftok fail\n");
	msgid = msgget(key, IPC_CREAT|0666);
	if(msgid < 0)
		err_sys("msgget fail\n");

	for(i = 0; i < 10; i++){
		bzero(&msg, sizeof(msg));
		msg.mtype = i;
		sprintf(msg.mname, "%d mname", i);
		msgsnd(msgid, &msg, sizeof(msg.mname), 0);
	}
	return 0;

}