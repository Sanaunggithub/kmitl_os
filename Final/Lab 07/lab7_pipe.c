#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <positive integer>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int fd[2];
    pid_t pid;

    if (pipe(fd) < 0)
    {
        printf("pipe failed\n");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        printf("fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
       
        close(fd[0]);

        printf("Child: I am calculating\n");
        fflush(stdout);

        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            sum += i;
        }

        printf("Child: the result is %d\n", sum);
        fflush(stdout);

        char str[64];
        sprintf(str, "%d", sum);
        write(fd[1], str, strlen(str) + 1);

        printf("Child: I am sending data\n");
        fflush(stdout);

        printf("Child: Goodbye\n");
        fflush(stdout);

        close(fd[1]);
    }
    else
    {
        close(fd[1]);

        printf("Parent: waiting for my child\n");
        fflush(stdout);

        waitpid(pid, NULL, 0);

        char buf[64];
        read(fd[0], buf, sizeof(buf));
        close(fd[0]);

        int sum = atoi(buf);
        printf("Parent: sum from my child is %d\n", sum);
        fflush(stdout);

        printf("Parent: Goodbye\n");
        fflush(stdout);
    }

    return 0;
}