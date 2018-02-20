#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>


int main(int argc, char** argv) {
    double t_start = omp_get_wtime();
    srand(time(NULL));

    if (argc < 3) {
        printf("Usage: %s [matrix_size] [thread_count]\n", argv[0]);
        return 1;
    }
    int mat_size = atoi(argv[1]);
    int thread_count = atoi(argv[2]);
    bool print = true;
    if (mat_size > 10) {
        print = false;
    }

    double** mat_1 = (double**)malloc(sizeof(double*) * mat_size);
    double** mat_2 = (double**)malloc(sizeof(double*) * mat_size);
    for (int i = 0; i < mat_size; i++) {
        mat_1[i] = (double*)malloc(sizeof(double) * mat_size);
        mat_2[i] = (double*)malloc(sizeof(double) * mat_size);
        for (int j = 0; j < mat_size; j++) {
            mat_1[i][j] = ((double)rand()/RAND_MAX)*100;
            mat_2[i][j] = ((double)rand()/RAND_MAX)*100;
        }
    }
    double** final_mat = (double**)malloc(sizeof(double*) * mat_size);
    for (int i = 0; i < mat_size; i++) {
        final_mat[i] = (double*)malloc(sizeof(double) * mat_size);
        for (int j = 0; j < mat_size; j++) {
            final_mat[i][j] = 0;
        }
    }


    //go row by row of the first matrix, and column by column for the second.
    //[row][col] for matrix a
    //[col][row] for matrix b
    //divide work by columns of the first matrix
#pragma omp parallel num_threads(thread_count)
    {
        int my_id = omp_get_thread_num();

        
        int size = mat_size/thread_count;
        int start = my_id*size;
        int end;
        if (my_id == thread_count-1) {
            end = mat_size;
        }
        else {
            end = start+size;
        }
#pragma omp critical
        if (print) {
            printf("%d: %d - %d\n", my_id, start, end-1);
        }
 
        for (int mat_1_row = start; mat_1_row < end; mat_1_row++) {
            //now go through each column in the second matrix
            for (int mat_2_col = 0; mat_2_col < mat_size; mat_2_col++) {
                //now go down the column and across the row
                double curr_sum = 0;
                for (int i = 0; i < mat_size; i++) {
                    curr_sum += mat_1[mat_1_row][i] * mat_2[mat_2_col][i];
                }
                //put this sum in the final matrix
                final_mat[mat_1_row][mat_2_col] += curr_sum;
            }
        }
    }
    //should be done?
    for (int i = 0; i < mat_size; i++) {
        for (int j = 0; j < mat_size; j++) {
            if (print)
                printf("%f,",final_mat[i][j]);
        }
        if (print)
            printf("\n");
    }
    if (print)
        printf("\n");

    double time = omp_get_wtime() - t_start;
    printf("threads:%d\nsize:%d\ntime: %f\n", thread_count, mat_size, time);
    for (int i = 0; i < mat_size; i++) {
        free(mat_1[i]);
        free(mat_2[i]);
        free(final_mat[i]);
    }
    free(mat_1);
    free(mat_2);
    free(final_mat);

}
