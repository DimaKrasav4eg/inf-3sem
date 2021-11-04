#include <stdio.h>
#include <sys/stat.h>
#include <malloc.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/poll.h>

int main(int argc, char** argv)
{
	//printf("start\n");
	struct pollfd* fifos = (struct pollfd*)calloc(argc-1, sizeof(struct pollfd));
	if (argc < 2)
	{
		printf("input?\n");
		return 0;
	}

	for (int i = 1; i < argc; ++ i)
	{
		//printf("for #1\n");
		int fd_in = open(argv[i], O_RDONLY|O_NONBLOCK);
		fifos[i].fd = fd_in;
		fifos[i].events = POLLIN;
	}

	int poll_out = 0;

	for (;;)
	{
		//printf("for #2\n");
		poll_out = poll(fifos, argc, -1);
		for (int i = 0; i < argc; ++ i)
		{
			//printf("for #3\n");
			if(fifos[i].revents > 0)
			{
				int output = 0;
				char c;
				while ((output = read(fifos[i].fd, &c, 1)) == 1)
                    printf("%c", c);
			}
		}
	}


}