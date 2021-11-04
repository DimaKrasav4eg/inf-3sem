#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>


int main ()
{
       

       int shmid = 0;
       key_t key1 = ftok("../", 1);
       key_t key2 = ftok("../", 2);
       char* input = "input";
       char* output = "output";
       
       int fd = open(input, O_RDONLY);
       if (fd == -1)
       {
              printf("Can't open\n");
              return 0;
       }
       struct stat buff;
       stat(input, &buff);
       int size = buff.st_size;

       int shmid1 = shmget (key1, sizeof(int), IPC_CREAT|0666);
       int shmid2 = shmget (key2, size, IPC_CREAT|0666);
       printf("shmid = %d, shmgett = %d\n", shmid1, shmid2);
       
       int* prod1 = (int*) shmat (shmid1, NULL, O_WRONLY);
       char* prod2 = (char*) shmat (shmid2, NULL, O_WRONLY);

       printf("prod1 = %d, prod2 = %d\n", prod1, prod2);
       
       read (fd, prod2, *prod1);

       printf("prod1 = %d, prod2 = %s", *prod1, prod2);

       shmdt((void*)prod1);
       shmdt((void*)prod2);
}