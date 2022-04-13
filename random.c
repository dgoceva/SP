/* random.c */
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
 
main()
  { 
    int i;
		time_t t1;
 
		(void) time(&t1);
		srand48((long) t1);
		/* use time in seconds to set seed */
		printf("5 random numbers (Seed = %d):n",(int) t1);
		for (i=0;i<5;++i)
		  printf("%d ", lrand48());
		printf("nn"); /* flush print buffer */
	}