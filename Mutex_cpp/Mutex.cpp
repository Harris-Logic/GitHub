// mutex.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include "windows.h"//for HANDLE
#include "stdio.h"

int tickets = 10;//全局变量，2个线程共享访问的公共数据。
//命名的系统互斥体在整个操作系统中都可见，可用于同步不同进程中的线程
char mutexName[20]="ticketsMutex";
//声明互斥对象hMutex，来保证对同一资源（这里是tickets）的互斥访问
HANDLE hMutex; 

//线程的工作函数声明
//线程1的入口函数
DWORD WINAPI Fun1Proc(LPVOID lpParameter);
//线程2的入口函数
DWORD WINAPI Fun2Proc(LPVOID lpParameter);
//线程3的入口函数
DWORD WINAPI Fun3Proc(LPVOID lpParameter);
//线程4的入口函数
DWORD WINAPI Fun4Proc(LPVOID lpParameter);

void main()
{
	HANDLE hThread1;
	DWORD thread1ID;
	//创建线程1
	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, &thread1ID);
	HANDLE hThread2;
	DWORD thread2ID;
	//创建线程2
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, &thread2ID);

	HANDLE hThread3;
	DWORD thread3ID;
	//创建线程3
	hThread3 = CreateThread(NULL, 0, Fun3Proc, NULL, 0, &thread3ID);
	HANDLE hThread4;
	DWORD thread4ID;
	//创建线程4
	hThread4 = CreateThread(NULL, 0, Fun4Proc, NULL, 0, &thread4ID);



	//关闭线程1的句柄。将使线程1的使用计数减1
	CloseHandle(hThread1); 
	//关闭线程2的句柄。将使线程2的使用计数减1
	CloseHandle(hThread2);

	//关闭线程3的句柄。将使线程3的使用计数增1
	CloseHandle(hThread3); 
	//关闭线程4的句柄。将使线程4的使用计数增1
	CloseHandle(hThread4);
	/*调用CloseHandle后，当线程结束时，线程内核对象被释放，
	  否则只有当进程结束，才释放线程的内核对象hThread1和hThread2
    */

    //创建一个互斥体对象,如果成功返回互斥对象的句柄,否则返回NULL
	hMutex = CreateMutex(NULL, FALSE, mutexName);
	//判断对象是否创建成功
	if (hMutex)	
	{	//判断是否已经有同名的互斥体
		if(ERROR_ALREADY_EXISTS == GetLastError())		
		{		
			puts("only one instance can run!");		
			return;		
		}	
	}
	Sleep(10000);//主线程睡眠4秒钟,给其它线程运行的时间,因为一旦主线程退出则进行退出,其它线程也将退出
}

//线程的工作函数的定义

/***********************下面两个是消费者*************************/
DWORD WINAPI Fun1Proc(LPVOID lpParameter)
{
	while(TRUE)
	{
		/*等待互斥对象，如果全局互斥对象是有信号状态,则获得该对象。否则阻塞，继续等待。
		直到调用ReleaseMutex之前,互斥对象是无信号状态,其它线程不能对互斥对象进行访问。		
		*/
		WaitForSingleObject(hMutex, INFINITE);

		if(tickets > 0 && tickets <= 10)	
		{
			Sleep(500);
			printf("Thread1 sell tickets : %d\n", tickets-- );
		}
		else
			break;
		//释放互斥体对象，将互斥体对象设置为有信号状态
		ReleaseMutex(hMutex);
	}
	return 0;
	
}
DWORD WINAPI Fun2Proc(LPVOID lpParameter)				  
{      
	while(TRUE)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if(tickets > 0 && tickets <= 10)	
		{	
			Sleep(500);
			printf("Thread2 sell tickets : %d\n", tickets-- );
		}
		else
			break;
		ReleaseMutex(hMutex);
		}
	return 0;
}
/***************************下面是生产者*******************************/
DWORD WINAPI Fun3Proc(LPVOID lpParameter)				  
{      
	while(TRUE)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets >= 10)
			break;
		else
		{	
			Sleep(500);
			printf("Thread3 add tickets : %d\n", tickets++ );
		}
			
		ReleaseMutex(hMutex);
		}
	return 0;
}

DWORD WINAPI Fun4Proc(LPVOID lpParameter)				  
{      
	while(TRUE)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets >= 10)
			break;
		else
		{	
			Sleep(500);
			printf("Thread4 add tickets : %d\n", tickets++ );
		}
			
		ReleaseMutex(hMutex);
		}
	return 0;
}