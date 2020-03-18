// exa5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <iostream>
#include <fstream>
using namespace std;

//**使用临界区机制同步线程。

int total = 100 ;
HANDLE evFin[2] ;
CRITICAL_SECTION cs ;//临界区。

//可以去掉临界区机制，查看是否出现错误。（需要辅助sleep函数）
void WithdrawThread1(LPVOID param)
{
	EnterCriticalSection(&cs) ;//进入临界区
	if ( total-90 >= 0)
	{//Sleep(100);
		total -= 90 ;
		cout<<"You withdraw 90"<<endl;
	}
	else
		cout<<"You do not have that much money"<<endl; 
	LeaveCriticalSection(&cs) ;//退出临界区
	SetEvent (evFin[0]) ;
}
void WithdrawThread2(LPVOID param)
{
	EnterCriticalSection(&cs) ;//进入临界区
	if ( total-20 >= 0)
	{
		total -= 20 ;
		cout<<"You withdraw 20"<<endl;
	}
	else
		cout<<"You do not have that much money"<<endl; 
	LeaveCriticalSection(&cs) ;//退出临界区
	//LeaveCriticalSection(&cs) ;
	SetEvent (evFin[1]) ;
}
int main(int argc , char * argv[])
{
	evFin[0] = CreateEvent (NULL,FALSE,FALSE,NULL) ;
	evFin[1] = CreateEvent (NULL,FALSE,FALSE,NULL) ;

	InitializeCriticalSection(&cs) ;//初始化临界区。

	_beginthread(WithdrawThread1 , 0 , NULL) ;//创建线程顺序影响执行的结果。
	_beginthread(WithdrawThread2 , 0 , NULL) ;
    //_beginthread(WithdrawThread1 , 0 , NULL) ;

	WaitForMultipleObjects(2 ,evFin ,TRUE ,INFINITE) ;//等待两个事件都激活。

	DeleteCriticalSection(&cs) ;//删除临界区

	cout<<total<<endl;
	return 0 ;
}
