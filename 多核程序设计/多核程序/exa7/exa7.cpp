// exa7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <iostream>
using namespace std;

//**使用信号量机制同步线程。

#define THREAD_INSTANCE_NUMBER	3
DWORD foo(void * pData) {

	int ThreadNumberTemp = (*(int*) pData);
	HANDLE hSemaphore;

	if ((hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Semaphore.Test")) == NULL) {
		cout << "Open Semaphore error!" << endl;
	}

	WaitForSingleObject(hSemaphore,INFINITE);//获取信号量。
	cout << "foo is running!!!"  << ThreadNumberTemp << endl;
	cout << "foo gets the semaphore-" << ThreadNumberTemp<< endl;
	
	ReleaseSemaphore(hSemaphore, 1, NULL);//释放一个单位的信号量
	CloseHandle(hSemaphore);
	return 0;
}

int main(int argc, char* argv[])
{

	int i;
	DWORD ThreadID[THREAD_INSTANCE_NUMBER]; 
   	HANDLE hThread[THREAD_INSTANCE_NUMBER];
	HANDLE hSemaphore;

	
	if ((hSemaphore = CreateSemaphore(NULL,1,1, "Semaphore.Test")) == NULL ) 
	{
		cout << "Create Semaphore error!" << endl;
		return 0;
	}	

	//与互斥量一样，这里获取信号量的位置不同，会产生不同的结果。
	for (i=0;i<THREAD_INSTANCE_NUMBER;i++)
	{
		WaitForSingleObject(hSemaphore,INFINITE);//获取信号量。不可重入。
		hThread[i] = CreateThread(NULL, 
							0,                          
							(LPTHREAD_START_ROUTINE) foo, 
							(void *)&ThreadID[i],                    
							0,                       
							&(ThreadID[i]));              
		
		if (hThread[i] == NULL)

			cout << "CreateThread error" << ThreadID[i] << endl;
		else
			cout << "CreateThread: " << ThreadID[i] << endl;

	    ReleaseSemaphore(hSemaphore, 1, NULL);
	}

	WaitForMultipleObjects(THREAD_INSTANCE_NUMBER,hThread,TRUE,INFINITE);
	cout << "Close the Semaphore Handle! " << endl;
	CloseHandle(hSemaphore);

	return 0;
}
