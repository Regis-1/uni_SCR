#include <pthread.h>
#include <stdio.h>

#define N_thr 5

void *thread_function()
{
	printf("Hello SCR. Written by thread %ld\n", pthread_self());

	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	pthread_t thr_id[N_thr];
	int error;

	for(int i = 0; i < N_thr; ++i)
	{
		error = pthread_create(&thr_id[i], NULL, thread_function, NULL);

		if(error)
			fprintf(stderr, "Thread was not properly created!");
	}

	for(int i = 0; i < N_thr; ++i)
		pthread_join(thr_id[i], NULL);

	pthread_exit(NULL);
}
