// exa1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <iostream>
#include <fstream>
using namespace std;

//ʹ��_beginthread���������̵߳����ӡ�

void ThreadFunc1(PVOID param)
{
	while(1)
	{
		Sleep(1000);
		cout<<"  This is ThreadFunc1  "<<endl;
	} 
}
void ThreadFunc2(PVOID param)
{ 
	while(1)
	{
		Sleep(1000);
		cout<<"  This is ThreadFunc2  "<<endl;
	}
}

//���Զ��ִ�б����򣬲鿴�����̺߳���ִ�е�˳��

int main()
{
	int i=0;
	_beginthread(ThreadFunc1,0,NULL);
	_beginthread(ThreadFunc2,0,NULL);
	Sleep(5000);
	cout<<"end"<<endl;
	return 0;
}
