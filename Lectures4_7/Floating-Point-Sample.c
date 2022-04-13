// Floating-Point-Sample.c : Defines the entry point for the console application.
// try 4.1, 4.6, 5.1 and 4.2, 5.2

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
	char s[10];
	double f;
	int d;

	do {
		gets(s);
		f = atof(s);
		d = f*100;
		printf("%d\n", d%10);
	} while (f!=0);

	return 0;
}

