#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <positive integer>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0)
    {
        printf("shmget failed\n");
        return 1;
    }

    printf("Parent: I have created a shared memory for result...\n");
    fflush(stdout);

    int *shared_result = (int *)shmat(shmid, NULL, 0);
    if (shared_result == (void *)-1)
    {
        printf("shmat failed\n");
        return 1;
    }

    printf("Parent: I have attached the shared memory...\n");
    fflush(stdout);

    printf("Parent: I am about to fork a child process...\n");
    fflush(stdout);

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child: I am calculating\n");
        fflush(stdout);

        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            sum += i;
        }

        *shared_result = sum;

        printf("Child: The result is %d\n", sum);
        fflush(stdout);

        printf("Child: Goodbye\n");
        fflush(stdout);

        shmdt(shared_result);
    }
    else
    {
        printf("Parent: Waiting for my child\n");
        fflush(stdout);

        waitpid(pid, NULL, 0);

        printf("Parent: sum from my child is %d\n", *shared_result);
        fflush(stdout);

        shmdt(shared_result);
        printf("Parent: I have detached the shared memory...\n");
        fflush(stdout);

        shmctl(shmid, IPC_RMID, NULL);
        printf("Parent: I have removed the shared memory...\n");
        fflush(stdout);

        printf("Parent: Goodbye\n");
        fflush(stdout);
    }

    return 0;
}