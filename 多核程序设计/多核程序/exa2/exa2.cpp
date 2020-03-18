// exa2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <iostream> 
using namespace std;

//�򵥵Ķ��̴߳�����ִ�С�������ֹ�ĳ������ӡ�

DWORD WINAPI FunOne(LPVOID param){
  while(true)
  {
    Sleep(1000);
    cout<<"hello! ";
  }
  return 0;
} 
DWORD WINAPI FunTwo(LPVOID param){
  while(true)
  {
    Sleep(1000);
    cout<<"world! ";
  }
  return 0;
}

//ע�ⴴ���̺߳����ĵ�������������á�
//����1�ͷ�1���֣����Կ����̵߳���������ֹ��
//ע����������1�ͷ�1�����̵߳����������
//�̵߳���ֹ������

int main(int argc, char* argv[])
{
  int input=0;

  //�����̡߳�
  HANDLE hand1=CreateThread (NULL, 0, FunOne, (void*)&input, CREATE_SUSPENDED, NULL);
  HANDLE hand2=CreateThread (NULL, 0, FunTwo, (void*)&input, CREATE_SUSPENDED, NULL);
  while(true){
    cin>>input;
    if(input==1) 
    {
		//�ָ��߳�
		ResumeThread(hand1);
		ResumeThread(hand2);
    }
    else 
    {
		//�����߳�
		SuspendThread(hand1);
		SuspendThread(hand2);
    }
  };

  //��ֹ�߳�
  TerminateThread(hand1,1);
  TerminateThread(hand2,1);

  return 0;
}
