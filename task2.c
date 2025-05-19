#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void *threadfunc(void* arg) {
	printf("I am thread %d\n", *(int*)arg);
	sleep(1);
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
	printf("I am the main thread\n");
	return 0;
}

