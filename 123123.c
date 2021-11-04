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

int main ()
{
       
       char* prod;
       int shmid = 0;
       int key = 2;
       char* input = "input";
       char* output = "output";
       struct stat buff;
       
       stat(input, &buff);
       int size = buff.st_size;
       //shmid = semget (key, 1, IPC_CREAT|0666);
       int shmgett = shmget (key, size, IPC_CREAT|0666);
       printf("shmid = %d, shmgett = %d\n", shmid, shmgett);
       prod = (char*) shmat (shmid, NULL, SHM_RDONLY);
       printf("%d\n", prod);
       
       // int fd1 = open(input, O_RDONLY);
       // read (fd1, (void*)prod, size);

       // printf("%d\n", prod);x


       semctl (shmid, 0, IPC_RMID);

}