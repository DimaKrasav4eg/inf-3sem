#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>



int main(int argc, char const *argv[])
{
	int fdin = 0, fdout = 0;
	void* input;
	void* output;

	struct stat buff;
	stat(argv[1], &buff);
	int size = buff.st_size;
	
	if (argc != 3)
	{
		printf ("wrong format!\n");
		return 0;
	}

	if ((fdin = open (argv[1], O_RDONLY)) = 0 )
	{
		printf ("I can't open %s file\n", argv[1]);
		return 0;
	}
	if ((fdout = open (argv[2], O_RDWR|O_CREAT|O_TRUNC, 0666)) < 0 )
	{
		printf ("I can't open or create %s file\n", argv[2]);
		return 0;
	}

	if ((input = mmap (0, size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED)
	{
		printf ("mmap fdin error\n");
		return 0;
	}
	
	if (lseek (fdout, size, SEEK_SET) == -1)
	{
		printf ("lseek error\n");
		return 0;
	}
	
	if ((output = mmap (0, size, PROT_WRITE, MAP_SHARED, fdin, 0)) == MAP_FAILED)
	{
		printf ("mmap fdin error\n");
		return 0;
	}
	memcpy(output, input, size);


	return 0;
}