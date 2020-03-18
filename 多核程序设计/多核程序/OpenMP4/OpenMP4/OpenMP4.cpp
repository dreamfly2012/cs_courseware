// OpenMP4.cpp : 定义控制台应用程序的入口点。
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
	//把OMP_NUM_THREADS设置为5
    ordered_func(0, 50, 5);

	return 0;
}

