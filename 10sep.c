#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>



int main(int argc, char const *argv[])
{
	struct stat buff;
	stat(argv[1], &buff);
	int size = buff.st_size;
	int fd1 = open(argv[1], O_RDONLY, 0777);
	if (fd1 == -1)
	{
		printf ("were are input file?\n");
		return 0;
	}

	char* ptr = calloc(size, sizeof(char));
	read (fd1, (void*)ptr, size);

	int fd2 = open (argv[2], O_WRONLY|O_CREAT, 0666);
	if (fd2 == -1)
	{
		printf ("I can't write in file\n");
		return 0;
	}

	write (fd2, (void*)ptr, size);
	//printf("ok");
	close(fd1);
	close(fd2);

	return 0;
}