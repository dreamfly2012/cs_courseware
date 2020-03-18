using System;
using System.Threading;

//以银行取款为例的同步机制使用。
class Test
{
	static int total = 100;
    static object lock_total = new object();//创建同步对象。

	public static void WithDraw1()
	{
		int n=90;
        lock (lock_total)   //同步
        {
            if (n <= total)
            {
                total -= n;
                Console.WriteLine("You have withdrawn. n={0}", n);
                Console.WriteLine("total={0}", total);
            }
            else
            {
                Console.WriteLine("You do not enough money. n={0}", n);
                Console.WriteLine("total={0}", total);
            }
        }
	}
	public static void WithDraw2()
	{
		int n = 20;
        lock (lock_total)
        {
            if (n <= total)
            {
                total -= n;
                Console.WriteLine("You have withdrawn. n={0}", n);
                Console.WriteLine("total={0}", total);
            }
            else
            {
                Console.WriteLine("You do not enough money. n={0}", n);
                Console.WriteLine("total={0}", total);
            }
        }
	}
	public static void Main()
	{
		ThreadStart thread1 = new ThreadStart(WithDraw1);
		Thread newThread1 = new Thread(thread1);
		ThreadStart thread2 = new ThreadStart(WithDraw2);
		Thread newThread2 = new Thread(thread2);
		newThread1.Start();
		newThread2.Start();
        
	}
}
