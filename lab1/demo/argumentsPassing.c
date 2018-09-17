#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 100

typedef struct{
    int thread_id;
    char *message;
}argumentPassing;

void *user_def_function(void *argument){
    argumentPassing* arg;
    arg = (argumentPassing*) argument;
    printf("Hello world! from thread #%ld with message %s\n",arg->thread_id, arg->message);
    pthread_exit(NULL);
}

int main(char* argc, char ** argv){
    pthread_t threads[NUM_THREADS];
    int create_flag;
    for(int i=0; i< NUM_THREADS; i++){
        argumentPassing *argument = malloc(sizeof(argumentPassing));
        argument->thread_id = malloc(sizeof(int));
        argument->message = malloc(sizeof(char));
        printf("In main, create thread #%d\n",i);
        argument->thread_id = 2*i;
        char charArray[] = "thanhhao";
        argument->message = charArray;
        create_flag = pthread_create(&threads[i],NULL,user_def_function,argument);
        if(create_flag){
            printf("ERROR: return code from pthread_create #%d",create_flag);
            exit(-1);
        }
    }    
    pthread_exit(NULL);
    return 0;
}