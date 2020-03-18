using System;
using System.Threading;

//线程创建和运行的实例。
class Test
{
	static void Main() 
	{
		ThreadStart threadDelegate = new ThreadStart(Work.DoWork);
		Thread newThread = new Thread(threadDelegate);
		newThread.Start();

		Work w = new Work();
		w.Data = 42;
		threadDelegate = new ThreadStart(w.DoMoreWork);
		newThread = new Thread(threadDelegate);
		newThread.Start();
	}
}
class Work 
{
	public static void DoWork() 
	{
		Console.WriteLine("Static thread procedure."); 
	}
	public int Data;
	public void DoMoreWork() 
	{
		Console.WriteLine("Instance thread procedure. Data={0}", Data); 
	}
}
