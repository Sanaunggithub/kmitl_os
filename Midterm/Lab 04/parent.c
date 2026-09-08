#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s num1 num2 num3 num4\n", argv[0]);
        return 1;
    }

    pid_t pid1, pid2;
    int status1, status2;

    pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0)
    {
        execl("./child", "child", argv[1], argv[2], (char *) NULL);

        perror("exec failed");
        exit(1);
    }

    pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0)
    {
        execl("./child", "child",
              argv[3], argv[4], (char *)NULL);

        perror("exec failed");
        exit(1);
    }

    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    int result1 = WEXITSTATUS(status1);
    int result2 = WEXITSTATUS(status2);

    int final = result1 + result2;

    printf("First child result: %d\n", result1);
    printf("Second child result: %d\n", result2);
    printf("Final result: %d\n", final);

    return 0;
}