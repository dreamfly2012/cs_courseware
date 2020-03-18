// OpenMP4.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "omp.h"

void work(int k)
{
	printf("thread id =%d k=%d\n",omp_get_thread_num(),k);
    #pragma omp ordered
	printf(" %d\n", k);
}
void ordered_func(int lb, int ub, int stride)
{
	int i;
    #pragma omp parallel for ordered schedule(dynamic)
	for (i=lb; i<ub; i+=stride)
		work(i);
}


int _tmain(int argc, _TCHAR* argv[])
{
	//��OMP_NUM_THREADS����Ϊ5
    ordered_func(0, 50, 5);

	return 0;
}

