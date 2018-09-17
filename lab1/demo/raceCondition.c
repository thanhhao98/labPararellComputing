#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 64
#define NUM_LOOPS 5e7

void *user_def_func(void *threadId){
	long TID;
	TID = (long) threadId;
	int i;
	double result = 0.0;
	printf("Thread %ld starting ...\n",TID);
	for(i =0; i< NUM_LOOPS; i++){
		result = result + sin(i) *tan(i);
	}
	printf("Thread %ld done. Result = %e\n",TID, result);
	pthread_exit((void*) threadId);
}

int main(int argc, char *argv[]){
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	int creation_flag, join_flag;
	long i;
	void *status;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for(i=0; i< NUM_THREADS; i++){
		printf("In main, creating thread %ld\n",i);
		creation_flag = pthread_create(&threads[i], &attr, user_def_func, (void *) i);
		if (creation_flag){
			printf("ERROR: return code from thread_create() is %d\n", creation_flag);
			exit(-1);
		}
	}
	pthread_attr_destroy(&attr);
	for(i=0; i< NUM_THREADS; i++){
		join_flag = pthread_join(threads[i], &status);
		if(join_flag){
			printf("ERROR: return code from thread_join() is %d\n", join_flag);
			exit(-1);
		}
		printf("Main: completed join wiht thread %ld having a status of %ld\n",i, (long) status);
	}
	printf("Main: program completed. Exiting.\n");
	pthread_exit(NULL);
	return 0;
}
