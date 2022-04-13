#include <stdio.h>
#include <unistd.h>

int main()
{
  int retValue;

  retValue = fork();
  printf("returns: %d, PID: %u, parent PID: %u\n",retValue, getpid(), getppid());
  return 0;
}
