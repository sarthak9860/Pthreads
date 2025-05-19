#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int current = 0;

void *threadfunc(void* arg) {
	int id = *(int*)arg;
	sleep((rand() % 10) + 1);
	pthread_mutex_lock(&mtx);
	while(id!=current){
		pthread_cond_wait(&cond, &mtx);
	}
	printf("I am thread %d\n", *(int*)arg);
	current++;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main() {
	int n, s;
	printf("Enter the number of threads you want to create: ");
	scanf("%d", &n);
	pthread_t threads[n];
	for (int i = 0; i < n; i++) {
		int* id = malloc(sizeof(int));
		*id = i;
		s = pthread_create(&threads[i], NULL, threadfunc, id);
		if (s != 0) {
			perror("pthread_create");
			exit(1);
		}
	}
	for(int i = 0; i < n; i++){
		s = pthread_join(threads[i], NULL);
		if (s != 0) {
			perror("pthread_join");
			exit(1);
		}
	}
	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);
	printf("I am the main thread\n");
	return 0;
}

