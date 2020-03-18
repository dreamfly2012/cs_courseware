// OpenMP5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "omp.h"
#include "windows.h"

int _tmain(int argc, _TCHAR* argv[])
{
	__int64 counter_begin;
	__int64 counter_end;
	__int64 diff;
	__int64 sum=0;

	 
	//并行化带来的额外开销
	/*QueryPerformanceCounter((LARGE_INTEGER*)&counter_begin);
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<10000;i++)
		sum+=i;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter_end);
		
	diff=counter_end-counter_begin;
	printf("sum=%I64d execution with OpenMP, count=%I64d\n",sum,diff);

	sum=0;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter_begin);
	for(int i=0;i<10000;i++)
		sum+=i;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter_end);
		
	diff=counter_end-counter_begin;
	printf("sum=%I64d serial execution, count=%I64d\n",sum,diff);*/


    //同步的开销
	/*QueryPerformanceCounter((LARGE_INTEGER*)&counter_begin);
	for(int i=0;i<10000000;i++)
		sum+=i;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter_end);
	diff=counter_end-counter_begin;
	printf("sum=%I64d serial execution count=%I64d\n",sum,diff);

	sum=0;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter_begin);
    #pragma omp parallel for
	for(int i=0;i<10000000;i++)
    #pragma omp critical
		sum+=i;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter_end);
	diff=counter_end-counter_begin;
	printf("sum=%I64d parallel with critical count=%I64d\n",sum,diff);

	sum=0;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter_begin);
    #pragma omp parallel for reduction(+:sum)
	for(int i=0;i<10000000;i++)
		sum+=i;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter_end);
	diff=counter_end-counter_begin;
	printf("sum=%I64d parallel with reduction count=%I64d\n",sum,diff);  */

}

