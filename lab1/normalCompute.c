#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 64
#define NUM_LOOPS 5e7

void user_def_func(int funId){
	double result = 0.0;
	printf("Function %ld starting ...\n",funId);
	int i=0;
	for(i=0; i<NUM_LOOPS; i++){
		result = result + sin(i) * tan(i);
	}
	printf("Function %ld done. Result = %e\n", funId, result);
}
int main(int argc, char *argv[]){
	int i=0;
	for(i=0; i< NUM_THREADS; i++){
		printf("In main: call function %ld\n",i);
		user_def_func(i);
	}
	printf("Main: program completed. Exiting\n");
	return 0;
}



