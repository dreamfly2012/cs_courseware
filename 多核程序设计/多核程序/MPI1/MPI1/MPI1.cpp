// MPI1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include "mpi.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int rank;
	int size;

    MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("Hello world from process %d of %d\n", rank, size);
	MPI_Finalize();

	return 0;
}

