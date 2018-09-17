#include <omp.h>

int main(int argc, char** argv){
    int numThread, threadId;
    #pragma omp parallel private(threadId)
    {
        threadId = omp_get_thread_num();
        printf("Hello from thread# %d\n",threadId);
        if(threadId==0){
            numThread = omp_get_thread_num();
            printf("Number of thread %d\n",numThread);
        }
    }

    return 0;
}