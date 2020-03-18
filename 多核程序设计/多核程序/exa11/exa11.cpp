// exa11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <conio.h>
#include <stdio.h>
#define THREAD_INSTANCE_NUMBER	3


LONG g_fResourceInUse = FALSE;
LONG g_lCounter = 0;
 
CRITICAL_SECTION cs;

DWORD ThreadProc1(void * pData) {

	int ThreadNumberTemp = (*(int*) pData);
	printf("ThreadProc1: %d is running!\n",ThreadNumberTemp );

	EnterCriticalSection(&cs);
	printf("ThreadProc1 %d enters into critical section\n",ThreadNumberTemp);
	Sleep(1000);
	LeaveCriticalSection(&cs);

	return 0;
}

DWORD ThreadProc2(void * pData) {

	int ThreadNumberTemp = (*(int*) pData);
	printf("ThreadProc2: %d is running!\n",ThreadNumberTemp );

	EnterCriticalSection(&cs);
	printf("ThreadProc2 %d enters into critical section\n",ThreadNumberTemp);
	Sleep(1000);
	LeaveCriticalSection(&cs);

	return 0;
}

int main(int argc, char* argv[])
{

	int i;
	DWORD ID1,ID2; 
   	HANDLE h1,h2;

	i=123;
		
    for(int j=0;j<10;j++)
	{
        printf("¶Ïµã²âÊÔ %d \n",j);
	}
	
	InitializeCriticalSection(&cs);
	printf("Create the critical section \n");
	h1 = CreateThread(NULL, 
							0,                          
							(LPTHREAD_START_ROUTINE) ThreadProc1, 
							(void *)&ID1,                    
							0,                       
							&(ID1));        
	
	if (h1 == NULL)
		printf("CreateThread error %d \n",ID1);
	else
		printf("CreateThread  %d \n",ID1);


	h2= CreateThread(NULL, 
							0,                          
							(LPTHREAD_START_ROUTINE) ThreadProc2, 
							(void *)&ID2,                    
							0,                       
							&(ID2));              
		
	if (h2== NULL)
		printf("CreateThread error %d \n",ID2);
	else
		printf("CreateThread  %d \n",ID2);

	WaitForSingleObject (h1,INFINITE);
	WaitForSingleObject (h2,INFINITE);
	printf("Delete the critical section \n");
	
	DeleteCriticalSection(&cs);
	getch();
	return 0;
}
