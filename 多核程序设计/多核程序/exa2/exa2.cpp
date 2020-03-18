// exa2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <iostream> 
using namespace std;

//简单的多线程创建、执行、挂起、终止的程序例子。

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

//注意创建线程函数的第五个参数的运用。
//输入1和非1数字，可以控制线程的启动和终止。
//注意连续输入1和非1数字线程的运行情况。
//线程的终止函数。

int main(int argc, char* argv[])
{
  int input=0;

  //创建线程。
  HANDLE hand1=CreateThread (NULL, 0, FunOne, (void*)&input, CREATE_SUSPENDED, NULL);
  HANDLE hand2=CreateThread (NULL, 0, FunTwo, (void*)&input, CREATE_SUSPENDED, NULL);
  while(true){
    cin>>input;
    if(input==1) 
    {
		//恢复线程
		ResumeThread(hand1);
		ResumeThread(hand2);
    }
    else 
    {
		//挂起线程
		SuspendThread(hand1);
		SuspendThread(hand2);
    }
  };

  //终止线程
  TerminateThread(hand1,1);
  TerminateThread(hand2,1);

  return 0;
}
