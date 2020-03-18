// OpenMP2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "omp.h"
#include <windows.h>    //ʹ��Sleep()������Ҫ������ͷ�ļ�

int global=88;
#pragma omp threadprivate(global)

int counter=10;   //using threadprivate
#pragma omp threadprivate(counter)

void inc_counter() {
	counter++;       }

int _tmain(int argc, _TCHAR* argv[])
{
    //�����2  
	

    //�����3��4
   int i;int j;
    #pragma omp parallel for   //���Գ���ȥ��private��䣬�鿴����ִ�н��
	for(i=0; i<2; i++)
		for(j=6; j<10; j++)
			printf( "i=%d j=%d\n", i , j);
	printf("######################\n");
	for(i=0; i<2; i++)
        #pragma omp parallel for
		for(j=6; j<10; j++)
			printf( "i=%d j=%d\n", i , j ); 

	//�����7
	int val=8;
    #pragma omp parallel for firstprivate(val) lastprivate(val) //�˴��ɳ�ָı�private��䣬�۲����ִ�н��
	for(int i=0;i<5;i++)
	{
		printf("i=%d val=%d thread=%d\n",i,val,omp_get_thread_num());
		if(i==2)
			val=10000;
		if(i==3)
			val=11111;
		printf("i=%d val=%d thread=%d\n",i,val,omp_get_thread_num());
	}
	printf("val=%d\n",val);  
	
	//�����9��10
	#pragma omp parallel
    for (int i=0;i<5;i++)
       printf("hello world i=%d\n", i);
	printf("###########################\n");
	#pragma omp parallel for
    for(int i=0;i<5;i++)
       printf("hello world i=%d\n",i); 

	//�����11
    /*#pragma omp parallel      
	for(int i=0; i<10000; i++)
	  inc_counter();
	printf("counter=%d\n",counter);  */
    
    //����counterֵΪ���̣߳�0���̣߳��ĸ�ֵ
    /*#pragma omp parallel     
	{
	    int i=omp_get_thread_num();
	    if(i==1 )  
		    Sleep(2000);
	    counter=omp_get_thread_num();
	    printf("counter=%d\n",counter);  
	}
	printf("counter=%d\n",counter);  */

	//�����12
	/*global=1000;
	#pragma omp parallel copyin(global)
	{
	    printf("global=%d, thread=%d\n",global,omp_get_thread_num());
	    global=omp_get_thread_num();      
	}
	printf("global=%d\n",global);
	printf("parallel again\n");
	#pragma omp parallel
		printf("global=%d\n",global); */
	
	//ʹ��copyin()�Ӿ�ı�������ͨ��threadprivate()������
	//parallel�����ʹ��private()�Ӿ䡢firstprivate()�Ӿ䣬����ʹ��lastprivate()�Ӿ�
	/*int g=100;
	#pragma omp parallel //private(g)
	{
		//g=omp_get_thread_num();   
	    printf("g=%d, thread=%d\n",g,omp_get_thread_num());
	    g=omp_get_thread_num();      
	}
	printf("g=%d\n",g);
	printf("parallel again\n");
	#pragma omp parallel
		printf("g=%d\n",g); */
   
	//�����15
	/*#pragma omp parallel
	{
		 printf("outside loop thread=%d\n",  omp_get_thread_num());
         #pragma omp for
		 for(int i=0;i<4;i++)
			printf("inside loop i=%d thread=%d\n", i, omp_get_thread_num());
	}  */

    //�����16
    /*#pragma omp parallel sections
	{
        #pragma omp section
		printf("section 1 thread=%d\n",omp_get_thread_num());
        #pragma omp section
		printf("section 2 thread=%d\n",omp_get_thread_num());
        #pragma omp section
		printf("sectino 3 thread=%d\n",omp_get_thread_num());
	}*/

      //�����18
	  /*int counter=0;
      #pragma omp parallel
      {
           for(int i=0;i<10000;i++)
            #pragma omp atomic  //atomic operation
            counter++;
       }
       printf("counter = %d\n",counter);*/

	  //�����20
	  /*#pragma omp parallel
	  {
        #pragma omp for nowait
		for(int i=0;i<9;i++)
             printf("i=%d thread=%d\n",i,omp_get_thread_num());

	    printf("finished\n");
	  }*/

	return 0;
}

