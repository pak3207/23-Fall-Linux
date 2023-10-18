#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int S[100], A[100], B[100];
int i;

void *TaskCode(void *argument)
{	
	
	for(int i=0; i<100; i++)
	{
		S[i] = 0;
		A[i] = 0;
		B[i] = 0;
	}

	int tid;
	tid = *((int*)argument);
	for(int i = tid*25; i<(tid+1)*25; i++)
	{
		S[i] = A[i] + B[i];
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t threads[4];
	int args[4];
	int i;

	// create all threads
	for(i=0; i<4; ++i)
	{
		args[i] = i;
		pthread_create(&threads[i], NULL, TaskCode, (void *) &args[i]);
	}

	// wait for all threads to complete
	for(i=0; i<4; ++i)
	{
		pthread_join(threads[i],NULL);
	}
	
	return 0;
}
