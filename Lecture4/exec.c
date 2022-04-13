#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
 // execl("/bin/ls","ls",0);
  printf("\n\n");
  system("ls");
  printf("\n\n");
  execl("/bin/ls","ls",0);
}
