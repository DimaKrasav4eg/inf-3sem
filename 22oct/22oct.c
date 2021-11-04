#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

#define mtext_len 100

struct msgbuf
    {
        long mtype;
        char mtext[mtext_len];
    };

int main ()
{
    struct msgbuf mymsgbuf = {1, "London is the capital of great Britian"};
    key_t key = 2;
    int msgid = 0;
    msgid = msgget (key, IPC_CREAT|0666);
    int err = msgsnd (msgid, &mymsgbuf, mtext_len, IPC_NOWAIT);
    printf("msgid = %d, err = %d\n", msgid, err);
}