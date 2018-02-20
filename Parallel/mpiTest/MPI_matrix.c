#include "mpi.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])  
{
    srand(time(NULL));
    int numtasks, rank;
    MPI_Status status;   // required variable for Waitall routine

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int mat_size = 10;
    if (argc > 1)
        mat_size = atoi(argv[1]);

    int do_print = 1;
    if (mat_size > 10)
        do_print = 0;
  
    double start_time = MPI_Wtime();
    // determine left and right neighbors
	char buf[100];
	int token;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
  	MPI_Get_processor_name(processor_name, &name_len);

    //do matrix multiplication
    //node 0 will create matrix
    int i;
    int j;
    double** mat_1;
    double** mat_2;
    double** final_mat;
    if (rank == 0) {
        mat_1 = (double**)malloc(sizeof(double*) * mat_size);
        mat_2 = (double**)malloc(sizeof(double*) * mat_size);
        for (i = 0; i < mat_size; i++) {
            mat_1[i] = (double*)malloc(sizeof(double) * mat_size);
            mat_2[i] = (double*)malloc(sizeof(double) * mat_size);
            for (j = 0; j < mat_size; j++) {
                mat_1[i][j] = ((double)rand()/RAND_MAX)*100;
                mat_2[i][j] = ((double)rand()/RAND_MAX)*100;
            }
        }
        final_mat = (double**)malloc(sizeof(double*) * mat_size);
        for (i = 0; i < mat_size; i++) {
            final_mat[i] = (double*)malloc(sizeof(double) * mat_size);
            for (j = 0; j < mat_size; j++) {
                final_mat[i][j] = 0;
            }
        }
    }

    //all nodes will have a portion of the first matrix, and all of the second
    int num_rows = mat_size/numtasks;
    int start_row = num_rows * rank;
    int end_row = start_row + num_rows;
    if (rank == numtasks - 1) {
        end_row = mat_size;
        num_rows = end_row - start_row;
    }

    double** calc_mat_1 = (double**)malloc(sizeof(double*) * num_rows);
    double** calc_mat_2 = (double**)malloc(sizeof(double*) * mat_size);
    double** calc_mat_final = (double**)malloc(sizeof(double*) * num_rows);

    for (i = 0; i < num_rows; i++) {
       calc_mat_1[i] = (double*)malloc(sizeof(double) * mat_size );
       calc_mat_final[i] = (double*)malloc(sizeof(double) * mat_size );
    }
    for (i = 0; i < mat_size; i++) {
       calc_mat_2[i] = (double*)malloc(sizeof(double) * mat_size );
    }
    //now that it is created, populate it with the values from rank 0
    if (rank == 0) {
        int target_rank;
        for (target_rank = 1; target_rank < numtasks; target_rank++) {
            //send each row that this process needs
            int target_start = target_rank * num_rows;
            int target_end = target_start + num_rows;
            if (target_rank == numtasks - 1)
                target_end = mat_size;

            for (i = target_start; i < target_end; i++) {
                MPI_Send(mat_1[i], mat_size, MPI_DOUBLE, target_rank, 0, MPI_COMM_WORLD);
            }
            for (i = 0; i < mat_size; i++) {
                MPI_Send(mat_2[i], mat_size, MPI_DOUBLE, target_rank, 0, MPI_COMM_WORLD);
            }
        }
        //now rank 0 needs to populate its own calc array
        for (i = start_row; i < num_rows; i++) {
            calc_mat_1[i] = mat_1[i];
        }
        for (i = 0; i < mat_size; i++) {
            calc_mat_2[i] = mat_2[i];
        }
    }
    else {
        //if we aren't rank 0, we need to wait for it to send us the data
        for (i = 0; i < num_rows; i++) {
            MPI_Recv(calc_mat_1[i], mat_size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        }
        for (i = 0; i < mat_size; i++) {
            MPI_Recv(calc_mat_2[i], mat_size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        }
    }

    //now do the calculation
    int mat_1_row;
    int mat_2_col;
    int num_calc = 0;
    for (mat_1_row = 0; mat_1_row < num_rows; mat_1_row++) {
        for (mat_2_col = 0; mat_2_col < mat_size; mat_2_col++) {
            double curr_sum = 0;
            for (i = 0; i < mat_size; i++) {
                curr_sum += calc_mat_1[mat_1_row][i] * calc_mat_2[mat_2_col][i];
            }
            //put this sum in the final matrix
            calc_mat_final[mat_1_row][mat_2_col] += curr_sum;
            num_calc++;
        }
    }
    //now send the result back to rank 0

    if (rank != 0) {
        for (i = 0; i < num_rows; i++) {
            MPI_Send(calc_mat_final[i], mat_size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    }
    else {
        int target_rank;
        for (target_rank = 1; target_rank < numtasks; target_rank++) {
            //get ech row from the target process
            int target_start = target_rank * num_rows;
            int target_end = target_start + num_rows;
            if (target_rank == numtasks - 1)
                target_end = mat_size;
            for (i = target_start; i < target_end; i++) {
                MPI_Recv(final_mat[i], mat_size, MPI_DOUBLE, target_rank, 0, MPI_COMM_WORLD, &status);
            }
        }
        //now put your own calculated values into the matrix
        for (i = 0; i < num_rows; i++) {
            final_mat[i] = calc_mat_final[i];
        }
        //and its done!
        //print final matrix
        if (do_print){
            for (i = 0; i < mat_size; i++) {
                for (j = 0; j < mat_size; j++) {
                    printf("%f ", final_mat[i][j]);
                }
                printf("\n");
            }
        }
        printf("Finished in %f seconds\n", MPI_Wtime() - start_time);
    }

    MPI_Finalize();
}
