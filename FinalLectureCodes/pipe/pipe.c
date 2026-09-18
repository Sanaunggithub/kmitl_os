#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define SIZE 1024 // max size is 1023 because the last one is reserved for /0
#define READ_SIZE 5
int main(int argc, char **argv)
{
  int pfd[2];
  int nread;
  pid_t pid;
  char buf[SIZE];
  char buf_read[READ_SIZE+1];
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
    /* child */
    close(pfd[1]); // close write end
    // child waits for parent if nothing is to read yet
    while ((nread = read(pfd[0], buf_read, READ_SIZE)) != 0) {
      printf("child read %s\n", buf_read);
    }
    close(pfd[0]); // close read end
  } else {
    /* parent */
      close(pfd[0]); // close read end
      strcpy(buf, "hello world, hello mars, hello universe");
      sleep(2);
      /* include null terminator in write */
      //write(pfd[1], buf, strlen(buf)+1); // +1 means reserved for /0 else it will include from previous
      write(pfd[1], buf, strlen(buf));
      close(pfd[1]);
      wait(NULL);
  }
  exit(0);
}