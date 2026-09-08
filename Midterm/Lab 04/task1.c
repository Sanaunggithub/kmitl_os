#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int choice;
    pid_t pid;

    while (1)
    {
        
        printf("1. ls\n");
        printf("2. date\n");
        printf("3. ps\n");
        printf("0. Exit\n");

        printf("Choose option: ");
        scanf("%d", &choice);

        if(choice == 0)
        {
            printf("Program terminated.\n");
            break;
        }

        if (choice < 0 || choice > 3)
        {
            printf("Invalid option. Please try again.\n");
            continue;
        }

        pid = fork();

        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        
        if (pid == 0)
        {
            switch (choice)
            {
            case 1:
                execlp("ls", "ls", NULL);
                break;

            case 2:
                execlp("date", "date", NULL);
                break;

            case 3:
                execlp("ps", "ps", NULL);
                break;
            }

            perror("exec failed");
            exit(1);
        }

        else
        {
            wait(NULL);
        }
        }
    return 0;
    
}