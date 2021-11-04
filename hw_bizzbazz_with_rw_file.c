#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	const int START_SIZE_PTR = 10;
	const char MINUS = '-';
	//=====================================================
	if (argc < 3)
	{
		printf ("You didn't enter output file!\n");
		return 0;
	}
	if (argc < 2)
	{
		printf ("You didn't enter input file!\n");
		return 0;
	}
	//=====================================================

	int read_int = 1;
	int sum_nums = 0, last_num = 0, minus = 0;

	struct stat buff;
	stat(argv[1], &buff);
	int size = buff.st_size;

	int fd_in = open(argv[1], O_RDONLY, 0666);
	int fd_out = open (argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666);

	if (fd_in == -1)
	{
		printf ("Were are input file?\n");
		return 0;
	}
	if (fd_out == -1)
	{
		printf ("I can't write in file\n");
		return 0;
	}

	char* ptr = (char*)calloc(START_SIZE_PTR, sizeof(char));
	int size_ptr = START_SIZE_PTR;

	for (int i = 0; size > 0; -- size)
	{
		//printf("i = %d, size = %d, minus = %d\n", i, size, minus);
		if (size_ptr <= i)
		{
			//printf("size_ptr <= i\n");
			ptr = (char*)realloc(ptr, size_ptr * 2);
			size_ptr *= 2;
		}
		read (fd_in, (void*)(&ptr[i]), 1);
		if (i == 0 && ptr[i] == '-')
		{
			//printf("minus!\n");
			minus = 1;
			continue;
		}
		//printf("ptr[%d] = %c;\n", i, ptr[i]);
		if (isdigit(ptr[i])&& read_int) 
		{
			//printf ("it's num!\n");
			sum_nums += ptr[i] - '0';
			sum_nums %= 3;
			last_num = ptr[i] - '0';
			//printf ("sum_nums = %d; last_num = %d\n", sum_nums, last_num);
		}
		

		else if (ptr[i] == ' ' || ptr[i] == '\0' || ptr[i] == '\n')
		{
			if (read_int)
			{
				if (i == 0)
				{
					//printf("minus = %d\n", minus);
					if (minus == 0)
						write (fd_out, (void*)(&ptr[i]), 1);
					else
					{
						write (fd_out, (void*)(&MINUS), 1);
						write (fd_out, (void*)(&ptr[i]), 1);
					}
				}
				else if (sum_nums == 0 && (last_num == 5 ||last_num == 0))
				{
					write (fd_out, (void*)("BizzBazz"), 8);
					write (fd_out, (void*)(&ptr[i]), 1);
					//printf("Writed BizzBazz\n");
				}
				else if (sum_nums == 0)
				{
					write (fd_out, (void*)("Bizz"), 4);
					write (fd_out, (void*)(&ptr[i]), 1);
					//printf("Writed Bizz\n");
				}
				else if (last_num == 5 || last_num == 0)
				{
					write (fd_out, (void*)("Bazz"), 4);
					write (fd_out, (void*)(&ptr[i]), 1);
					//printf("Writed Bazz\n");
				}
				else
				{ 
					//printf("minus = %d\n", minus);
					if (minus == 0)
						write (fd_out, (void*)ptr, i + 1);
					else
					{
						write (fd_out, (void*)(&MINUS), 1);
						write (fd_out, (void*)ptr, i + 1);
					}
					//printf("Writed num %s\n", ptr);
				}
			}
			else
			{
				if (minus == 0)
						write (fd_out, (void*)ptr, i + 1);
				else
				{
					write (fd_out, (void*)(&MINUS), 1);
					write (fd_out, (void*)ptr, i + 1);
				}
				//printf("Writed word %s\n", ptr);
			}
			//printf("creating new ptr...\n");
			i = -1;
			read_int = 1;
			sum_nums = 0;
			last_num = 0;
			minus = 0;
			free (ptr);
			//printf("pfff\n");
			ptr = (char*)calloc(START_SIZE_PTR, sizeof(char));
			size_ptr = START_SIZE_PTR;
			// if (ptr[i] == '\0')
			// 	break;
			//printf ("O'K!\n");
		}
		else
		{
			//printf("it's a charaster!\n");
			read_int = 0;

		}
		//printf("[%d]--------------------------\n", i);
		++i;
	}

	close(fd_in);
	close(fd_out);

	return 0;
}