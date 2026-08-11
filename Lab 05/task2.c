#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *child_function(void *arg)
{
    int n = *(int *)arg;
    long long *result = malloc(sizeof(long long));

    *result = 0;

    for (int i = 1; i <= 2 * n; i++)
    {
        *result += i;
    }

    return result;
}

int main()
{
    int n;
    long long parent_result = 0;
    long long *child_result;

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    pthread_t child_thread;

    pthread_create(&child_thread, NULL, child_function, &n);

    for (int i = 1; i <= n; i++)
    {
        parent_result += i;
    }

    pthread_join(child_thread, (void **)&child_result);

    long long final_result = parent_result + *child_result;

    printf("Parent thread result: %lld\n", parent_result);
    printf("Child thread result: %lld\n", *child_result);
    printf("Final result: %lld\n", final_result);

    free(child_result);

    return 0;
}