#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32 //rozmiar bufora

int main(int argc, char *argv[]) {
    int pipefds[2];
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
    	close(pipefds[1]); //zamkniecie potoku write

        ssize_t n;
        while ((n = read(pipefds[0], buffer, sizeof(buffer) - 1)) > 0) 			{
            buffer[n] = '\0';
            printf("#%s#", buffer);

        }
        close(pipefds[0]);	      
    }
    else if (pid > 0) {
        FILE *fptr;
        if ((fptr = fopen(argv[1], "r")) == NULL) {
            perror("error opening file");
            exit(EXIT_FAILURE);
        }

        char singleLine[BUFFER_SIZE];
        close(pipefds[0]);
        //odczytywanie pliku
        while (fgets(singleLine, sizeof(singleLine), fptr)) {
            write(pipefds[1], singleLine, strlen(singleLine));
        }
        int error = ferror(fptr);
        fclose(fptr);
        if (error) {
            perror("error reading file");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }

    return 0;
}
