// assert_sample.c : Defines the entry point for the console application.
//

#include <stdio.h>
#include <assert.h>
 
int test_assert ( int x )
{
   assert( x <= 4 );
   return x;
}
 
int main(int argc, char* argv[])
{
	  int i;
 
    for (i=0; i<=9; i++){
        test_assert( i );
        printf("i = %i\n", i);
    }
	return 0;
}

