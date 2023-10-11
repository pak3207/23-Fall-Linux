#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#define N 4 // child process number
#define MAXLINE 100
#include <string.h>
#include <stdlib.h>

void sinx_taylor(int num_elements, int terms, double* x, double* result)
{
	int pid;
	int fd[2*N];
	char message[MAXLINE], line[MAXLINE];
	
	for(int i=0; i<num_elements; i++)
	{
		int* p_fd = &fd[2*i];
		pipe(p_fd);
	}
	for(int i=0; i<num_elements; i++)
	{
		int* p_fd = &fd[2*i];
		if((pid = fork()) ==0)
		{
			close(p_fd[0]);
		 	int my_id = i;		
			double value = x[i];
			double number = x[i]*x[i]*x[i];
			double denom = 6.; // 3!
			int sign = -1;

			for(int j=1; j<terms; i++)
			{
				value += (double)sign * number / denom;
				number *= x[i] * x[i];
				denom *= (2.*(double)j+2.) * (2.*(double)j+3.);
				sign *= -1;
			}
			result[i] = value;
			sprintf(message, "%lf", result[i]);
			length = strlen(message)+1;
			write(p_fd[1], message, length);

			exit(my_id);
		}
		else
		{
			close(fd[0]);
		}
	}

	int stat;
	for(int i=0;  i<num_elements; i++)
	{
		wait(&stat);
		int child_id = stat >> 8;
		read(fd[2*child_id], line, MAXLINE);

		double result = atof(line);
		result[chile_id] = res;
	}

}
int main()
{
	double x[N] = {0, M_PI/6., M_PI/3., 0.134};
	double res[N];

	sinx_taylor(N, 3, x, res);
	for(int i=0; i<N; i++)
	{
		printf("sin(%.2f)by Taylor series = %f\n", x[i], res[i]);
		printf("sin(%.2f) = %f\n", x[i], sin(x[i]));
	}
	return 0;
}
