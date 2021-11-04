#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main ()
{
    int fd_out = open("output", O_WRONLY|O_CREAT, 0666);

    int pid = 0;
    for (int i = 0; i < 1; ++ i)
    {
        pid = fork ();
        write(fd_out, (void*)pid, );

        if(pid == 0)
            printf("%d\n", getpid());

    }
}