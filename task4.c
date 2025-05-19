#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int current = 1;

void* thread_func(void* arg) {
	int id = *(int*)arg;
	while (1) {
		pthread_mutex_lock(&lock);
		while (id != current) {
			pthread_cond_wait(&cond, &lock);
		}
		printf("%d ", id);
		fflush(stdout);
		current = (current % N) + 1;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
	return NULL;
}

int main() {
	pthread_t threads[N];
	int ids[N];
	for (int i = 0; i < N; i++) {
		ids[i] = i + 1;
		if (pthread_create(&threads[i], NULL, thread_func, &ids[i]) != 0) {
			perror("pthread_create");
			exit(1);
		}
	}
	for (int i = 0; i < N; i++) {
		pthread_join(threads[i], NULL);
	}
	return 0;
}
