// exa5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <iostream>
#include <fstream>
using namespace std;

//**ʹ���ٽ�������ͬ���̡߳�

int total = 100 ;
HANDLE evFin[2] ;
CRITICAL_SECTION cs ;//�ٽ�����

//����ȥ���ٽ������ƣ��鿴�Ƿ���ִ��󡣣���Ҫ����sleep������
void WithdrawThread1(LPVOID param)
{
	EnterCriticalSection(&cs) ;//�����ٽ���
	if ( total-90 >= 0)
	{//Sleep(100);
		total -= 90 ;
		cout<<"You withdraw 90"<<endl;
	}
	else
		cout<<"You do not have that much money"<<endl; 
	LeaveCriticalSection(&cs) ;//�˳��ٽ���
	SetEvent (evFin[0]) ;
}
void WithdrawThread2(LPVOID param)
{
	EnterCriticalSection(&cs) ;//�����ٽ���
	if ( total-20 >= 0)
	{
		total -= 20 ;
		cout<<"You withdraw 20"<<endl;
	}
	else
		cout<<"You do not have that much money"<<endl; 
	LeaveCriticalSection(&cs) ;//�˳��ٽ���
	//LeaveCriticalSection(&cs) ;
	SetEvent (evFin[1]) ;
}
int main(int argc , char * argv[])
{
	evFin[0] = CreateEvent (NULL,FALSE,FALSE,NULL) ;
	evFin[1] = CreateEvent (NULL,FALSE,FALSE,NULL) ;

	InitializeCriticalSection(&cs) ;//��ʼ���ٽ�����

	_beginthread(WithdrawThread1 , 0 , NULL) ;//�����߳�˳��Ӱ��ִ�еĽ����
	_beginthread(WithdrawThread2 , 0 , NULL) ;
    //_beginthread(WithdrawThread1 , 0 , NULL) ;

	WaitForMultipleObjects(2 ,evFin ,TRUE ,INFINITE) ;//�ȴ������¼������

	DeleteCriticalSection(&cs) ;//ɾ���ٽ���

	cout<<total<<endl;
	return 0 ;
}
