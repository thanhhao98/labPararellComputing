#include <omp.h>
#include <stdio.h>

#define N 50
#define CHUNKSIZE 100
#define OMP_NUM_THREADS 5
#define MAX_THREAD 48

int cout[MAX_THREAD];
int main(int argc, char ** argv){
    int i, chunk;
    float a[N], b[N], c[N];
    int count[OMP_NUM_THREADS];
    for (i=0; i < N; i++){
        a[i] = b[i] = i*1.0;
    }
    for (i=0; i < N; i++){
        count[i] =0;
    }
    chunk = CHUNKSIZE;
    #pragma omp parallel shared(a,b,c,chunk) private(i)
    {   
        printf("%d\n",i);
        omp_set_num_threads(OMP_NUM_THREADS);
        #pragma omp for schedule(dynamic,chunk) nowait
        for(i=0; i < N; i++){
            int tid = omp_get_thread_num();
            printf("Iter from thread %d\n",tid);
            c[i] = a[i] + b[i];
            count[tid]++;
        }
    }
    printf("Vector c:\n");
    for (i=0; i < N; i++){
        printf(" %f ", c[i]);
    }
    printf("\n");
    return 0;
}
