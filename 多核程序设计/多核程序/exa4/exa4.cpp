// exa4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <iostream>
#include <fstream>
using namespace std;

//**ʹ���¼�����ͬ���̵߳����ӡ�

//�����¼���
HANDLE evRead, evFinish;

void ReadThread(LPVOID param)
{
    //�ȴ����¼���
	WaitForSingleObject (evRead ,INFINITE);
	
	cout<<"Reading"<<endl;
	
	//��������¼���
	SetEvent (evFinish);
}
void WriteThread(LPVOID param)
{
	cout<<"Writing"<<endl;

	//������¼���
	SetEvent (evRead);
}
int main(int argc , char * argv[])
{
	//���������¼���ע���¼������ĺ��塣
	evRead = CreateEvent (NULL ,FALSE ,FALSE ,NULL) ;
	evFinish = CreateEvent (NULL ,FALSE ,FALSE ,NULL) ;

	_beginthread(ReadThread , 0 , NULL) ;
	_beginthread(WriteThread , 0 , NULL) ;

	//�ȴ������¼���
	WaitForSingleObject (evFinish,INFINITE) ;

	cout<<"The Program is End"<<endl;
	return 0 ;
}
