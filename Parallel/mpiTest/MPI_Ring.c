#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])  
{
   int numtasks, rank;
   MPI_Status status;   // required variable for Waitall routine

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   
    // determine left and right neighbors
	char buf[100];
	int token;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
  	MPI_Get_processor_name(processor_name, &name_len);

    int dest = rank-1;
    int src = rank+1;
    if (rank == 0)
        dest = numtasks-1;
    if (rank == numtasks-1) {
        src=0;
        token = 100;
        MPI_Send(&token, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }
    MPI_Recv(&token, 1, MPI_INT, src, 0, MPI_COMM_WORLD, &status);
    printf("%d got a token! val:%d\n", rank, token);
    token++;
    if (rank != numtasks-1)
        MPI_Send(&token, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);

    MPI_Finalize();
}
