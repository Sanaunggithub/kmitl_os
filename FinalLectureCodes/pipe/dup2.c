/* Prog: dup2.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int pfd[2];
    int pid;

    if (pipe(pfd) == -1)
    {
        perror("pipe failed");
        exit(1);
    }
    if ((pid = fork()) < 0)
    {
        perror("fork failed");
        exit(2);
    }
    if (pid == 0)
    { 
        close(pfd[0]); // close read end
        dup2(pfd[1], 1); // child duplicate fd1 (output)
        close(pfd[1]); // close write end
        execlp("ls", "ls", NULL); // child
        perror("ls failed");
        exit(3);
    }
    else
    {
        close(pfd[1]);
        dup2(pfd[0], 0); // duplicate read end
        close(pfd[0]);
        execlp("wc", "wc", NULL); // parent
        perror("wc failed");
        exit(4);
    }
    exit(0);
}