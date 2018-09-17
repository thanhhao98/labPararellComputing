#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define NUM_THREADS 10
#define NUM_LOOPS 10000


void *user_def_function(void *thread_id){
    int TID = (int) thread_id;
    printf("Thread #%d starting... \n",TID);
    double result =0.0;
    for(int i=0;i<NUM_LOOPS;i++){
        result += (sin(i)+tan(i));
    }
    printf("Thread #%d end with result %e \n",TID,result);
    pthread_exit((void*)thread_id);
}

int main(char* argc, char ** argv){
    pthread_t threads[NUM_THREADS];
    int create_flag,join_flag;
    for(int i=0; i< NUM_THREADS; i++){
        printf("In main, create thread #%d\n",i);
        create_flag = pthread_create(&threads[i],NULL,user_def_function,(void*)i);
        if(create_flag){
            printf("ERROR: return code from pthread_create #%d",create_flag);
            exit(-1);
        }
    }
    void * status;
    for(int i=0; i< NUM_THREADS; i++){
        join_flag = pthread_join(threads[i],&status);
        if(join_flag){
            printf("ERROR: return code from pthread_join #%d\n",join_flag);
            exit(-1);
        }
            printf("In main, join thread #%d\n complete",i);
    } 
    printf("Main complete\n");
    pthread_exit(NULL);
    return 0;
}