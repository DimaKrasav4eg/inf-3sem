#include <sys/types.h>
#include <signal.h>


int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		printf("too few arguments in input\n");`
		return 0;
	}

	int fd = open(argv[1], O_RDONLY, 0666);

	struct stat buff;
	stat(argv[1], &buff);
	int size = buff.st_size;

	void* data = malloc(size);
	read(fd, data, size);

	for (int i = 0; i < size; i += 1)
	{	
		
		kill (arv[2], i);
		sleep(0.5);
	}

}