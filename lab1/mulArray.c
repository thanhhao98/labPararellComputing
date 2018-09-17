#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 8
#define VEC_LEN 1e5

pthread_mutex_t mutexsum;
int *a, *b;
long sum = 0;
void *dotProd(void *arg){
	int i, start, end, offset;
	long tid = (long) arg;
	offset = tid;
	start = offset*VEC_LEN;
	end = start+ VEC_LEN;
	printf("Thread: %ld starting. start=%d end=%d\n", tid, start,end-1);
	for(i=start; i<end; i++){
		pthread_mutex_lock(&mutexsum);
		sum = sum + (a[i]*b[i]);
		pthread_mutex_unlock(&mutexsum);
	}
	printf("Thread: %ld done. Glogal sum now is=%li\n",tid,sum);
	pthread_exit((void*) 0);
}

int main(){
	long i;
	void *status;
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	a = (int*) malloc (NUM_THREADS*VEC_LEN*sizeof(int));
	b = (int*) malloc (NUM_THREADS*VEC_LEN*sizeof(int));
	for (i=0; i<VEC_LEN; i++){
		a[i] = b[i] =1;
	}
	pthread_mutex_init(&mutexsum, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for(i=0; i< NUM_THREADS; i++){
		pthread_create(&threads[i], &attr, dotProd, (void *) i);
	}
	pthread_attr_destroy(&attr);
	for(i=0;i<NUM_THREADS; i++){
		pthread_join(threads[i], &status);
	}
	printf("Final Global Sum=%li\n",sum);
	free(a);
	free(b);
	pthread_mutex_destroy(&mutexsum);
	pthread_exit(NULL);
}
