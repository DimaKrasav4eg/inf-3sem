


int main(int argc, char const *argv[])
{

	int fd = open (argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf ("Can't open file!\n");
		return 0;
	}

	struct stat buff;
	stat (argv[1], &buff);		//Размер 
	int size = buff.st_size;
	ц
}