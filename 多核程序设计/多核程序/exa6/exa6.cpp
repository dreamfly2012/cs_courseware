// exa6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <iostream>
using namespace std;

//**��������ʹ�÷�����

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
	WaitForSingleObject(hMutex,INFINITE);//��ȡ��������
	cout << "ThreadProc is running!!"  << ThreadNumberTemp <<endl;
	cout << "ThreadProc gets the mutex-" << ThreadNumberTemp <<endl;
	
	ReleaseMutex(hMutex);//�ͷŻ�������
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
		if ((hMutex = CreateMutex(NULL, FALSE, "Mutex.Test")) == NULL ) //ע��ڶ�����������ǰ�߳��Ƿ�ӵ�д�������
		{
			cout << "Create Mutex error!" << endl;
			return 0;
		}
	}
	//ReleaseMutex(hMutex);                                  //ReleaseMutex(hMutex);ReleaseMutex(hMutex);

	//��ȡ�ź�����λ�ò�ͬ����������ͬ�Ľ����
   //WaitForSingleObject(hMutex,INFINITE);
	for (i=0;i<THREAD_INSTANCE_NUMBER;i++)
	{
       WaitForSingleObject(hMutex,INFINITE);//��ȡ�����������߳̿��ظ���ȡ��������ʱ���ͷ���ͬ�Ĵ�����
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
