#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int file;
	int newFile;
	int mappedFile;
	int map;
	char buff[1024];
	char newBuff[1024];
	char userInput[128];
	struct stat statbuf;
	char *memFile;
	int odczyt;
	int swpFile;

	while(1)
	{
		printf("Enter a picture for mapping:");
		scanf("%s", userInput);

		if(strcmp(userInput, "quit") == 0)
			break;

		if(fork() == 0)
		{
			execlp("display", "", "-update", "1", "-delay", "2", "plik", NULL);
		}
		else
		{
			if(( file = open(userInput, O_RDWR, S_IRUSR | S_IWUSR)) < 0 ) 
				printf("\n%s couldn't be opened!\n", userInput);

			swpFile = open("plik", O_RDWR | O_CREAT);  
			if(fstat(file, &statbuf) < 0)
			{
				printf("\nCouldn't retreive the file stats\n");
				return -1;
			}

			truncate("plik", statbuf.st_size);
			memFile = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, swpFile, 0 );
			read(file, memFile, statbuf.st_size);

			msync(memFile, statbuf.st_size, MS_SYNC);
			munmap(memFile, statbuf.st_size);
			close(file);
		}
	}

	return 0;
}


