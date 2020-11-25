#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define BUF_SIZE 256

int main() {

    pid_t pid;
    int fd[2], in_fd, n;
    char buf[BUF_SIZE];
    char fname[32];
    
    if(pipe(fd) < 0)
    {
        fprintf(stderr, "Failed creating pipe\n");
        return 1;
    }

    pid = fork();

    if(pid == 0)
    {
        printf("Child created!\n");
    }
    else
    {
        printf("Back in parent\n");
    } 
}
