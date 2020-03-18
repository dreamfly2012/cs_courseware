// OpenMP1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "omp.h"

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Hello from serial.\n");
	printf("Thread number = %d\n",omp_get_thread_num());  //串行执行
	#pragma omp parallel                                        //开始并行执行
	{
		printf("Hello from parallel. Thread number=%d\n",omp_get_thread_num());
	}
	printf("Hello from serial again.\n");
	return 0;
}

