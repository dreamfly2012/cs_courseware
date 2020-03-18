// exa4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <iostream>
#include <fstream>
using namespace std;

//**使用事件机制同步线程的例子。

//两个事件。
HANDLE evRead, evFinish;

void ReadThread(LPVOID param)
{
    //等待读事件。
	WaitForSingleObject (evRead ,INFINITE);
	
	cout<<"Reading"<<endl;
	
	//激活结束事件。
	SetEvent (evFinish);
}
void WriteThread(LPVOID param)
{
	cout<<"Writing"<<endl;

	//激活读事件。
	SetEvent (evRead);
}
int main(int argc , char * argv[])
{
	//创建两个事件，注意事件参数的含义。
	evRead = CreateEvent (NULL ,FALSE ,FALSE ,NULL) ;
	evFinish = CreateEvent (NULL ,FALSE ,FALSE ,NULL) ;

	_beginthread(ReadThread , 0 , NULL) ;
	_beginthread(WriteThread , 0 , NULL) ;

	//等待结束事件。
	WaitForSingleObject (evFinish,INFINITE) ;

	cout<<"The Program is End"<<endl;
	return 0 ;
}
