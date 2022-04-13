#include <stdio.h>

#define XMAX 5
#define YMAX 5

int eval(int x, int y);
float density(int x, int y);

int main(void) {
  int x, y;
  float data[XMAX][YMAX];

  for (y=0; y < YMAX; y++) {
    for (x=0; x < XMAX; x++) {
      data[x][y]=density(x,y);
    }
  }
  
  for (y=0; y <= YMAX; y++) {
    for (x=0; x <= XMAX; x++) {
      printf("data[%i][%i] should be %f, is %f\n",x,y,eval(x,y)/5.0,data[x][y]);
    }
  }
  
  return 0;
}

int eval(int x, int y) {
  int result;

  result=((XMAX*XMAX)-(x*x))/((YMAX*YMAX)-(y*y));

  return result;
}

float density(int x, int y) {
  int result;

  result=eval(x,y);
  result=result/5;

  return (float)result;
}
