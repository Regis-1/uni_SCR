#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define BUF_SIZE 256

int main(int argc, char** argv) {

    pid_t pid;
    int fd[2], in_fd, n;
    char buf[BUF_SIZE];
    char* fname = NULL;
    
    if(argc > 1)
    {
    	printf("No filename as program's argument!\n");
		return 1;
	}
    
    if(pipe(fd) < 0)
    {
        fprintf(stderr, "Failed creating pipe\n");
        return 2;
    }

    pid = fork();

    if(pid == 0)
    {
    	close(fd[1]);
        
    }
    else
    {
    	close(fd[0]);
    
        if((in_fd = open(fname, O_RDONLY)) < 0)
        {
            fprintf(stderr, "Failed opening file\n");
            return 3;
        }
        
        while((n = read(in_fd, &buf, BUF_SIZE)) > 0)
        {
            if(write(fd[1], &buf, n) < 0) {
                fprintf(stderr, "Failed writing to pipe\n");
                return 4;
            }  
        }
    } 
}
