#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 32 //rozmiar bufora

int main(int argc, char *argv[]) {
    int pipefds[2], in_fd, n;
    char buffer[BUFFER_SIZE];

	//sprawdzanie argumentow
    if (argc < 2) {
        fprintf(stderr, "usage: progname <filename>");
        exit(EXIT_FAILURE);
    }

	//tworzenie pipe'ow
    if (pipe(pipefds) == -1) {
        perror("PIPE ERROR");
        exit(EXIT_FAILURE);
    }

	//tworzenie potomnego procesu
    pid_t pid = fork();

    if (pid == 0) {
    	//potomek
        close(pipefds[1]); //zamkniecie potoku write
        close(0);
        dup(pipefds[0]); //duplikacja potoku
        close(pipefds[0]);

        //wykorzystanie funkcji display programu ImageMagick
        //z parametrem "-" do pobrania danych odczytanych przez potok
        execlp("display", "display", "-", NULL);	      
    }
    else if (pid > 0)
    {
    	//rodzic
        FILE *fptr;
        if ((fptr = fopen(argv[1], "r")) == NULL) {
            perror("error opening file");
            exit(EXIT_FAILURE);
        }
        close(pipefds[0]);

        if((in_fd = open(argv[1], O_RDONLY)) < 0)
        {
            
            fprintf(stderr, "Failed opening file\n");
            return 2;
        }
        
        while((n = read(in_fd, &buffer, BUFFER_SIZE)) > 0)
        {
        	//odczytywanie danych z wybranego obrazu
            if(write(pipefds[1], &buffer, n) < 0)
            {
                fprintf(stderr, "Failed writing to pipe\n");
                return 3;
            }  
        }
        close(in_fd);
    }

    return 0;
}
