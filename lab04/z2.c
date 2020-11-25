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

	//tworzenie potomnego potoku
    pid_t pid = fork();

    if (pid == 0) {
    	close(pipefds[1]);
        close(0);
        dup(pipefds[0]);
        close(pipefds[0]);

        //!!!REALLY IMPORTANT!!!
        //Arguments which you pass to execlp depends on image dispaly program that you are
        //using. Always check what arguments need to be provided in order to read the image
        //from stdin. E.g. ImageMagick accepts NULL or "-".GraphicsMagick on the other hand
        //accepts only "-".
        execlp("display", "display", "-", NULL);	      
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
