// exa3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <iostream> 
using namespace std;

//使用全局变量同步线程的例子。

//全局变量。
int globalvar = false;

DWORD WINAPI ThreadFunc(LPVOID pParam)
{
	cout<<"  ThreadFunc  "<<endl;
	Sleep(200);

	//修改全局变量的值。
	globalvar = true;

	return 0;
}
DWORD WINAPI ThreadFunc1(LPVOID pParam)
{
	while(1)
	cout<<"  ThreadFunc111  "<<endl;
	return 0;
}
DWORD WINAPI ThreadFunc2(LPVOID pParam)
{
	while(1)
	cout<<"  ThreadFunc222  "<<endl;
	return 0;
}

//这种方式可能存在一些问题。

int main()
{
	//HANDLE hthread1 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);
	HANDLE hthread2 = CreateThread(NULL, 0, ThreadFunc2, NULL, 0, NULL);
	HANDLE hthread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
	if (!hthread)
	{
		cout<<"Thread Create Error ! "<<endl;
		CloseHandle(hthread);
	}
	//bool b =SetThreadPriority(hthread,15);
	//cout<<GetThreadPriority(hthread1)<<endl;cout<<GetThreadPriority(hthread2)<<endl;cout<<GetThreadPriority(hthread)<<endl;

	//循环判断全局变量的值。
	while (!globalvar)
			cout<<"Thread while"<<endl;

	cout<<"Thread exit"<<endl;
	return 0;
}
