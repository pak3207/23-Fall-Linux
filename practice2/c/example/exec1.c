#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	printf("Parent process\n");
	if(fork() == 0)
	{
		execl("/bin/echo","echo","hello",NULL);
		fprintf(stderr, "Failed");
		exit(1);
	}

	printf("End of parent process\n");
}
