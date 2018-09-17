#include "mat_mul_pthread.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <malloc.h>
typedef struct {
    int id;
    int dim;    // Dimension of matrices
    double **m_a;
    double **m_b;
    double **m_r;
    int *rows;  // Num of rows that each thread handles
} param_t;

int main(int argc, const char *argv[]){
    if(argc >= 3){
        printf("1. Get parameters from users...\n");
        int dim = atoi(argv[1]);
        int num_threads = atoi(argv[2]);
        int print_flag;
        if(argc == 4)
            print_flag = atoi(argv[3]);
        else
            print_flag = 0;
        int num_rows_per_thread[num_threads];
        int i, j;
        int row;
        int col;
        int t_left = num_threads;
        int r_left = dim;
        long rc;
        void *status;
        printf("2. Initialize matrices...\n");
        double **matrix_a;
        double **matrix_b;
        double **result;
        matrix_a = malloc(dim * sizeof(double *));
        matrix_b = malloc(dim * sizeof(double *));
        result = malloc(dim * sizeof(double *));
        for(row = 0; row < dim; ++row) {
            matrix_a[row] = malloc(dim * sizeof(double));
        }
        
        for(row = 0; row < dim; ++row) {
            matrix_b[row] = malloc(dim * sizeof(double));
        }
        
        for(row = 0; row < dim; ++row) {
            result[row] = malloc(dim * sizeof(double));
        }
        
        for (row = 0; row < dim; row++)
            for(col = 0; col < dim; col++)
                matrix_a[row][col] = rand() % 1000;

        for (row = 0; row < dim; row++)
            for(col = 0; col < dim; col++)
                matrix_b[row][col] = rand() % 1000;

        for(row = 0; row < dim; row++)
            for(col = 0; col < dim; col++)
                result[row][col] = 0;
	printf("3. Initialize pthreads...\n");
        pthread_t *thread;
        pthread_attr_t attr;
        thread = (pthread_t *) malloc(num_threads * sizeof(pthread_t));
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        printf("4. Partitioning workload for each thread...\n");
        for(i = 0; i < num_threads; i++){
            num_rows_per_thread[i] = r_left / t_left;
            r_left -= num_rows_per_thread[i];
            --t_left;
	}
        printf("5. Calculating...\n");
        int rows = dim;
        mul_mat(0, &rows, dim, matrix_a, matrix_b, result);
        if(print_flag == 1){
            printf("Printing out Matrix A: \n");
            print_matrix( matrix_a, dim );
            printf("Printing out Matrix B: \n");
            print_matrix( matrix_b, dim );
            printf("Printing out the result from A * B: \n");
            print_matrix( result, dim );
        }
        printf("6. Completed the main program. Exitting now.\n");
        return 1;
    }else{
        printf("Usage: ./mat_mul_pthread DIM NUM_THREADS [PRINT_FLAG]\n");
        printf("\t ./mat_mul_pthread 10 2 1\n");
        printf("\t ./mat_mul_pthread is run with matrix 10x10, 2 threads, print_flag = 1\n");
        return 0;
    }
}

void *worker(void *arg){
    param_t *p = (param_t *) arg;
    mul_mat(p->id, p->rows, p->dim, p->m_a, p->m_b, p->m_r);
    pthread_exit(0);
}

void mul_mat(int id, int *rows, int dim, double **matrix_a, double **matrix_b, double **result){
    int i, k;
    int row, col;
    double sum;
    for(row = 0; row < dim; row++){
        for(col = 0; col < dim; col++){
            sum = 0.0;
            for(k = 0; k < dim; k++){
                sum = sum + (matrix_a[row][k] * matrix_b[k][col]);
            }
            result[row][col] = sum;
        }
    }
}

void print_matrix( double **matrix, int dim ) {
    int row;
    int col;
    for(row = 0; row < dim; row++) {
        printf("[ ");
        for(col = 0; col < dim; col++) {
            printf(" %f ", matrix[row][col]);
        }
        printf(" ]\n");
    }
    printf("\n");
}
