// exa7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <iostream>
using namespace std;

//**ʹ���ź�������ͬ���̡߳�

#define THREAD_INSTANCE_NUMBER	3
DWORD foo(void * pData) {

	int ThreadNumberTemp = (*(int*) pData);
	HANDLE hSemaphore;

	if ((hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Semaphore.Test")) == NULL) {
		cout << "Open Semaphore error!" << endl;
	}

	WaitForSingleObject(hSemaphore,INFINITE);//��ȡ�ź�����
	cout << "foo is running!!!"  << ThreadNumberTemp << endl;
	cout << "foo gets the semaphore-" << ThreadNumberTemp<< endl;
	
	ReleaseSemaphore(hSemaphore, 1, NULL);//�ͷ�һ����λ���ź���
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

	//�뻥����һ���������ȡ�ź�����λ�ò�ͬ���������ͬ�Ľ����
	for (i=0;i<THREAD_INSTANCE_NUMBER;i++)
	{
		WaitForSingleObject(hSemaphore,INFINITE);//��ȡ�ź������������롣
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
