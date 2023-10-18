#include <pthread.h>
#include <stdio.h>
#include <math.h>

struct ThreadData
{
	int num_elements;
	int terms;
	double *x;
	double *result;
}

void *sinx_taylor_parallel(void *arg)
{
	struct ThreadData *data = (struct ThreadData *)arg;
	int num_elements = data->num_elements;
	int terms = data->terms;
	double *x = data->x;
	double *result = data->result;

	for(int i=0; i<num_elements; i++)
	{
		double value = x[i];
		double numer = x[i] * x[i] * x[i];
		double denom = 6.; // 3!
		int sign = -1;

		for (int j=1; j<=terms; j++)
		{
			value += (double)sign * numer / denom;
			numer *= x[i] * x[i];
			denom *= (2.*(double)j+2.) * (2.*(double)j+3.);
			sign *= -1;
		}
		result[i] = value;
	}
	pthread_exit(NULL);
}


int main()
{
	int num_elements= 10; //배열 요소 수
	int terms = 3; //급수의 항 수
	double x[num_elements]; // 입력 데이터 배열
	double result[num_elements]; // 결과 저장 배열

	// 입력 데이터 초기화
	for(int i=0; i<num_elements; ++i)
	{
		x[i] = i + 1.0;
	}

	struct ThreadData thread_data;
	thread_data.num_elements = num_elements;
	thread_data.terms = terms;
	thread_data.x = x;
	thread_data.result = result;

	pthread_t = thread;

	// 쓰레드 생성
	if(pthread_create(&thread, NULL, sinx_taylor_parallel, (void *)&thread_data) != 0)
	{
		perror("pthread_create");
		return 1;
	}

	// 쓰레드 종료 대기
	if(pthread_join(thread, NULL) !=0)
	{
		perror("pthread_join");
		return 1;
	}

	// 결과 출력 
	for(int i=0; i<num_elements; ++i)
	{
		printf("Result[%d]: %f\n", i, result[i]);
	}

	return 0;
}
