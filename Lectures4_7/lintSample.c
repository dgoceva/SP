#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int *example1();
void alloc0(int **, int);
char * dup_string(char *s);

int main(int argc, char **argv) {
  example1();

  return EXIT_SUCCESS;
}

int *example1() {
  int *i;

  alloc0(&i, 0); // ok
  alloc0(&i, 1); // ok, malloc 
  alloc0(&i, 1); // leak: i overwritten
  return i;
}

void alloc0(int **i, int b) {
  if (b) *i = malloc(sizeof (int));
  else *i = 0;
}

char * dup_string(char *s) {
    char *copy = malloc(strlen(s+1));
    strcpy(copy, s);
    return copy;
}

