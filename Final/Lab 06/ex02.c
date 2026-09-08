#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_sigterm(int sig)
{
    printf("Child: my id is %d, my parent has just terminated me\n", getpid());
    fflush(stdout);
    exit(0);
}

int main()
{
    pid_t children[5];

    for (int i = 0; i < 5; i++)
    {
        children[i] = fork();

        if (children[i] < 0)
        {
            printf("fork failed\n");
            return 1;
        }

        if (children[i] == 0)
        {
            // Child process
            printf("Child: my id is %d\n", getpid());
            fflush(stdout);

            signal(SIGTERM, handle_sigterm);

            while (1)
            {
                pause();
            }
        }
    }

    // Parent process
    sleep(2);

    for (int i = 0; i < 5; i++)
    {
        kill(children[i], SIGTERM);
    }

    for (int i = 0; i < 5; i++)
    {
        waitpid(children[i], NULL, 0);
    }

    printf("Parent: I have killed all of my children\n");

    return 0;
}