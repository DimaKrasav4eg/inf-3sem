#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


void handler2 (int sig)
{
	printf("is the capital of Great Britian\n");
}

void handler1 (int sig)
{
	printf("London");
	fflush(stdout);
}
int main ()
{
	printf("My pid is %d\n", getpid());
	struct sigaction act1;
	act1.sa_handler = &handler1;
	act1.sa_flags = SA_RESTART;

	struct sigaction act2;
	act2.sa_handler = &handler2;
	act2.sa_flags = SA_RESTART;

	sigaction(SIGUSR1, &act1, NULL);
	sigaction(SIGUSR2, &act2, NULL);
	fork();
	while (1)
	{
		//sleep(1);
	}	
}