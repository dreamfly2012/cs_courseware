// OpenMP3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "omp.h"

omp_lock_t lock;
int counter=0;

void inc_counter()
{
	printf("thread id=%d\n",omp_get_thread_num());
	for(int i=0;i<100000;i++)
	{
		omp_set_nest_lock(&lock);
		counter++;
		omp_unset_nest_lock(&lock);
	}
}

void dec_counter()
{
	printf("thread id=%d\n",omp_get_thread_num());
	for(int i=0;i<100000;i++)
	{
		omp_set_nest_lock(&lock);
		counter--;
		omp_unset_nest_lock(&lock);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	omp_init_nest_lock(&lock);
    #pragma omp parallel sections
	{
    #pragma omp section
		inc_counter();
    #pragma omp section
		dec_counter();
	}

	omp_destroy_nest_lock(&lock);
	printf("counter=%d\n",counter);

	return 0;
}

