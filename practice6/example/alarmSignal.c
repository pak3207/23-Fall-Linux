#include <stdio.h>
#include <siganal.h>
#include <unistd.h>

void intHandler();
void intHandler2();

int main()
{
	signal(SIGALRM, intHandler);
	signal(SIGINT, intHandler2);
	alarm(10);

	int correct = 0;
	while(!correct){
		if(getchar() == '1'){
			if(getchar() == '2'){
				if(getchar() == '3'){
					correct = 1;
				}
			}
		}
	}
	printf("End of Main \n");
}

void intHandler()
{
	printf("Fire!\n");
	exit(0);
}

void intHandler2()
{
	printf("10sec reset...\n");
	alarm(10);
}

