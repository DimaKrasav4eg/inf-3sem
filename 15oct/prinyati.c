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
       
       int fd = open(output, O_WRONLY|O_CREAT, 0666);

       int shmid1 = shmget (key1, sizeof(int), IPC_CREAT|0666);
       int* prod1 = (int*) shmat (shmid1, NULL, O_WRONLY);

       int shmid2 = shmget (key2, *prod1, IPC_CREAT|0666);
       char* prod2 = (char*) shmat (shmid2, NULL, O_WRONLY);
       printf("shmid = %d, shmgett = %d\n", shmid1, shmid2);

       //printf("prod1 = %d, prod2 = %d\n", prod1, prod2);
       
       write (fd, prod2, *prod1);

       printf("prod1 = %d, prod2 = %s\n", *prod1, prod2);

       shmctl(shmid1, IPC_RMID, NULL);
       shmctl(shmid2, IPC_RMID, NULL);

       shmdt((void*)prod1);
       shmdt((void*)prod2);
}