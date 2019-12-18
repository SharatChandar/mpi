#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) 
{
	MPI_Init(NULL, NULL);
	int nb_mpi_processes;
	MPI_Comm_size(MPI_COMM_WORLD, &nb_mpi_processes);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
	if(nb_mpi_processes != 2) { printf("This program is design to be run with 2 processes only"); return 0;}
 
	int ball = 0;
	int n;
	int niter = 6;
	for (n=1;n<=niter;n++) 
	{
		if(rank==0)
		{
			MPI_Send ( &ball , 1 , MPI_INTEGER , 1 , 0 , MPI_COMM_WORLD );
			MPI_Recv ( &ball , 1 , MPI_INTEGER , 1 , 0 , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			ball = ball + 1;
    	}
		if(rank==1)
		{
			MPI_Recv ( &ball , 1 , MPI_INTEGER , 0 , 0 , MPI_COMM_WORLD, MPI_STATUS_IGNORE );
			ball = ball + 1;
			MPI_Send ( &ball , 1 , MPI_INTEGER , 0 , 0 , MPI_COMM_WORLD );
		}
		printf("Process %d iter %d ball value is : %d\n",rank,n,ball);
		MPI_Barrier(MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}