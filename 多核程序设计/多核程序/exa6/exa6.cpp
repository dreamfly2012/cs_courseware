// exa6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <iostream>
using namespace std;

//**互斥量的使用方法。

#define THREAD_INSTANCE_NUMBER	3

LONG g_fResourceInUse = FALSE;
LONG g_lCounter = 0;

DWORD ThreadProc(void * pData) {

	int ThreadNumberTemp = (*(int*) pData);
	HANDLE hMutex;

	if ((hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "Mutex.Test")) == NULL) {
		cout << "Open Mutex error!" << endl;
	}
	
	//cout << "ThreadProc is running!!"  << ThreadNumberTemp <<endl;
	WaitForSingleObject(hMutex,INFINITE);//获取互斥量。
	cout << "ThreadProc is running!!"  << ThreadNumberTemp <<endl;
	cout << "ThreadProc gets the mutex-" << ThreadNumberTemp <<endl;
	
	ReleaseMutex(hMutex);//释放互斥量。
	CloseHandle(hMutex);
	return 0;
}

int main(int argc, char* argv[])
{

	int i;
	DWORD ID[THREAD_INSTANCE_NUMBER]; 
   	HANDLE h[THREAD_INSTANCE_NUMBER];
	HANDLE hMutex;
	if ( (hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "Mutex.Test")) == NULL) {
		if ((hMutex = CreateMutex(NULL, FALSE, "Mutex.Test")) == NULL ) //注意第二个参数，当前线程是否拥有创建的锁
		{
			cout << "Create Mutex error!" << endl;
			return 0;
		}
	}
	//ReleaseMutex(hMutex);                                  //ReleaseMutex(hMutex);ReleaseMutex(hMutex);

	//获取信号量的位置不同，将产生不同的结果。
   //WaitForSingleObject(hMutex,INFINITE);
	for (i=0;i<THREAD_INSTANCE_NUMBER;i++)
	{
       WaitForSingleObject(hMutex,INFINITE);//获取互斥量。本线程可重复获取，但解锁时需释放相同的次数。
		h[i] = CreateThread(NULL, 
							0,                          
							(LPTHREAD_START_ROUTINE) ThreadProc, 
							(void *)&ID[i],                    
							0,                       
							&(ID[i]));              
		
		if (h[i] == NULL)
			cout << "CreateThread error" << ID[i] << endl;
		else
			cout << "CreateThread: " << ID[i] << endl;
      ReleaseMutex(hMutex);
	}
	//ReleaseMutex(hMutex);

	WaitForMultipleObjects(THREAD_INSTANCE_NUMBER,h,TRUE,INFINITE);
	cout << "Close the Mutex Handle! " << endl;
	CloseHandle(hMutex);

	return 0;
}
