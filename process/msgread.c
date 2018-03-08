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

	key = ftok(".", 123);

	msgid = msgget(key, IPC_CREAT | 0666);
	if(msgid < 0)
		err_msg("msgget fail\n");

	while((msgrcv(msgid, &msg, sizeof(msg.mname), 0, IPC_NOWAIT)) != -1){
		printf("msg: %s\n", msg.mname);
	}

	if(msgctl(msgid, IPC_RMID, NULL) == -1)
		err_msg("msgctl fail\n");

	return 0;
}