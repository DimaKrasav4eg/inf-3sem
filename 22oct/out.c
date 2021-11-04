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
    struct msgbuf mymsgbuf;
    key_t key = 2;
    int msgid = 0;
    msgid = msgget (key, 0666);
    int err = msgrcv (msgid, &mymsgbuf, mtext_len, 1, 0);
    printf("%s\n", mymsgbuf.mtext);
}