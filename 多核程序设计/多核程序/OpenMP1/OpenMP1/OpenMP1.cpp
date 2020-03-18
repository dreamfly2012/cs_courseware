// OpenMP1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "omp.h"

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Hello from serial.\n");
	printf("Thread number = %d\n",omp_get_thread_num());  //����ִ��
	#pragma omp parallel                                        //��ʼ����ִ��
	{
		printf("Hello from parallel. Thread number=%d\n",omp_get_thread_num());
	}
	printf("Hello from serial again.\n");
	return 0;
}

