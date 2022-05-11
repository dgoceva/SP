// C Program to multiply two matrix using pthreads
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// maximum size of matrix
#define MAX 10

// maximum number of threads
#define MAX_THREAD 10

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];
int step_i = 0;

void* multi(void* arg)
{
	int i = step_i++; //i denotes row number of resultant matC

	for (int j = 0; j < MAX; j++)
  	   for (int k = 0; k < MAX; k++)
		matC[i][j] += matA[i][k] * matB[k][j];
}

// Driver Code
int main()
{
	// Generating random values in matA and matB
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			matA[i][j] = rand() % 10;
			matB[i][j] = rand() % 10;
		}
	}

	// Displaying matA
	printf("\nMatrix A\n");
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			printf("%d\t",matA[i][j]);
		printf("\n");
	}

	// Displaying matB
	printf("\nMatrix B\n");
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			printf("%d\t",matB[i][j]);	
		printf("\n");
	}

	// declaring four threads
	pthread_t threads[MAX_THREAD];

	// Creating four threads, each evaluating its own part
	for (int i = 0; i < MAX_THREAD; i++) {
		int* p;
		pthread_create(&threads[i], NULL, multi, (void*)(p));
	}

	// joining and waiting for all threads to complete
	for (int i = 0; i < MAX_THREAD; i++)
		pthread_join(threads[i], NULL);

	// Displaying the result matrix
	printf("\nMultiplication of A and B\n");
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			printf("%d\t",matC[i][j]);	
		printf("\n");
	}
	return 0;
}

