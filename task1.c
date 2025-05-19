#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>

static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *threadfunc(void* arg){
	int loop = 1000;
	printf("Threadfunc gets executed first\n");
	int ret = pthread_mutex_lock(&mtx);
	for(int j=0; j<loop; j++){
		glob++;
	}
	ret = pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(int argc, char* argv[]){
	pthread_t t1,t2,t3,t4,t5,t6,t7,t8,t9,t10;

	pthread_t arr_threads[10] = {t1,t2,t3,t4,t5,t6,t7,t8,t9,t10};
	for(int i=0; i<10; i++){
		int s = pthread_create(&t1,NULL,threadfunc,NULL);
		if(s!=0){
			perror("Thread Create\n");
			exit(1);
		}
		s = pthread_join(t1, NULL);
		if(s!=0){
                        perror("Thread Join\n");
                        exit(1);
                }
	}
	printf("%d\n", glob);
	exit(0);
}
