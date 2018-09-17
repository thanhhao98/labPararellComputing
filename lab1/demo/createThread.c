#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 10


void *user_def_function(void *pid){
    int id = (int) pid;
    printf("Hello world! from thread #%d with message \n",id);
    pthread_exit(NULL);
}

int main(char* argc, char ** argv){
    pthread_t threads[NUM_THREADS];
    int create_flag;
    for(int i=0; i< NUM_THREADS; i++){
        printf("In main, create thread #%d\n",i);
        create_flag = pthread_create(&threads[i],NULL,user_def_function,(void*)i);
        if(create_flag){
            printf("ERROR: return code from pthread_create #%d",create_flag);
            exit(-1);
        }
    }    
    pthread_exit(NULL);
    return 0;
}