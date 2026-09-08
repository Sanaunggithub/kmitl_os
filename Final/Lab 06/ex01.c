#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t received = 0;

void handle_sigint(int sig)
{
    printf("get SIGINT from child\n");
    received = 1;
}

int main()
{
    pid_t pid;  

    pid = fork();

    if (pid < 0)
    {
        printf("fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("child: Sleeping for 5 seconds\n");
        fflush(stdout);

        sleep(5);

        pid_t parent_pid = getppid();

        kill(parent_pid, SIGINT);
        printf("child: sending SIGINT\n");
        fflush(stdout);

        printf("child: Bye\n");
        fflush(stdout);
    }
    else
    {
        printf("parent: Waiting for my child to send SIGINT\n");
        signal(SIGINT, handle_sigint);

        while (!received)
        {
            pause(); 
        }

        printf("parent: Bye\n");
    }

    return 0;
}