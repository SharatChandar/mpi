#include <mpi.h>
#include <stdio.h>
int main(int argc, char** argv)
{
	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	printf("Hello world from processor %s, rank %d out of %d processors\n",	processor_name, world_rank, world_size);
	int token;
	if (world_rank != 0) 
    {
		MPI_Recv(&token, 1, MPI_INT, world_rank - 1, 0,	MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d received token %d from process %d\n", world_rank, token, world_rank - 1);
	}
	else 
    {
		token = 112;
	}
	MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size,0, MPI_COMM_WORLD);
	if (world_rank == 0) 
    {
		MPI_Recv(&token, 1, MPI_INT, world_size - 1, 0,	MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d received token %d from process %d\n", world_rank, token, world_size - 1);
	}
	MPI_Finalize();
}