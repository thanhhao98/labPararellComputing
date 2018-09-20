#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char ** argv){
    int NUM_THREADS = atoi(argv[2]);
    int NUM_STEPS = atoi(argv[1]);
    omp_set_num_threads(NUM_THREADS);
    int i;
    long double x,pi=0.0;
    long double step = 1.0/NUM_STEPS;
    double timeStart = omp_get_wtime();
    #pragma omp parallel
    {
        long double sum =0;
        int id = omp_get_thread_num();
        int n_threads = omp_get_num_threads();
        for(i=id;i<NUM_STEPS; i+=n_threads){
            x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
        }
        #pragma omp critical
        {
            pi+= (step*sum);
        }
    }
    printf("Pi is: %Lf\n",pi);
    return 0;
}