#include <unistd.h>
#include "stdio.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main (int argc, char** argv)
{
	// fork();
	// printf("sosiska");
	// execl ("/bin/ls", "ls", "-la", (void*)0);
	// printf("sosiska");
	int fd = open ("input", O_RDONLY|O_WRONLY);

	//dup2(fd, STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	
	printf("sosiska");
}