#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    // Parent creates 5 initial children
    for (int i = 0; i < 5; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            int sub_count = (i % 2 == 0) ? 4 : 5; // even index -> 4, odd index -> 5

            for (int j = 0; j < sub_count; j++)
            {
                pid_t sub_pid = fork();

                if (sub_pid < 0)
                {
                    perror("fork failed");
                    exit(1);
                }

                if (sub_pid == 0)
                {
                    printf("I am sub-child %d of child %d\n", j, i);
                    exit(0);
                }
            }
        
            for (int j = 0; j < sub_count; j++)
            {
                wait(NULL);
            }

            printf("I am child %d\n", i);
            exit(0); 
        }
    }

    for (int i = 0; i < 5; i++)
    {
        wait(NULL);
    }

    printf("I am parent\n");
    return 0;
}