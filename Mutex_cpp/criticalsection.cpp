/*
函数功能：演示两个线程在不使用临界区的情况下修改同一个全局变量count。
*/
/*#include "stdafx.h"*/
#include "stdio.h"
#include "windows.h"

//定义一个共享的全局变量
int count=10;

//临界区对象
CRITICAL_SECTION g_cs;

//线程的工作函数
DWORD  WINAPI FunctionOfThread1( LPVOID lpParameter );
DWORD  WINAPI FunctionOfThread2( LPVOID lpParameter );
DWORD  WINAPI FunctionOfThread3( LPVOID lpParameter );
DWORD  WINAPI FunctionOfThread4( LPVOID lpParameter );
DWORD  WINAPI FunctionOfThread5( LPVOID lpParameter );
DWORD  WINAPI FunctionOfThread6( LPVOID lpParameter );

int main()
{
	//初始化临界区对象
	InitializeCriticalSection( &g_cs );
	//创建线程
	HANDLE hThread1=CreateThread(NULL,0,FunctionOfThread1,NULL,0,NULL);
	HANDLE hThread2=CreateThread(NULL,0,FunctionOfThread2,NULL,0,NULL);
	HANDLE hThread3=CreateThread(NULL,0,FunctionOfThread3,NULL,0,NULL);
	HANDLE hThread4=CreateThread(NULL,0,FunctionOfThread4,NULL,0,NULL);
	HANDLE hThread5=CreateThread(NULL,0,FunctionOfThread5,NULL,0,NULL);
	HANDLE hThread6=CreateThread(NULL,0,FunctionOfThread6,NULL,0,NULL);

	while(count>0)
	{

		EnterCriticalSection( &g_cs );/**/
		printf("main thread is running\n");
		LeaveCriticalSection( &g_cs );/**/
		Sleep(1000);
	}
	//关闭线程句柄
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	printf("main thread is over\n");
	//删除临界区对象
	DeleteCriticalSection( &g_cs );

	return 0;
}

DWORD  WINAPI FunctionOfThread1( LPVOID lpParameter )/*线程一 */
{
	while(1)
	{
		EnterCriticalSection( &g_cs );/**/
		printf("thread1 - increase count: ");
		++count;/**/
		printf("%d",count);
		printf("\n");
		LeaveCriticalSection( &g_cs );/**/
		Sleep(1000);
	}
	return 0;
}


DWORD  WINAPI FunctionOfThread2( LPVOID lpParameter )
{
	while(1)
	{
		EnterCriticalSection( &g_cs );/**/
		printf("thread2 - decrease count: ");
		count = count - 2;/**/
		printf("%d",count);
		printf("\n");
		LeaveCriticalSection( &g_cs );/**/
		Sleep(1000);
	}
	return 0;
}

DWORD  WINAPI FunctionOfThread3( LPVOID lpParameter )/*线程一 */
{
	while(1)
	{
		EnterCriticalSection( &g_cs );/**/
		printf("thread1 - increase count: ");
		++count;/**/
		printf("%d",count);
		printf("\n");
		LeaveCriticalSection( &g_cs );/**/
		Sleep(1000);
	}
	return 0;
}

DWORD  WINAPI FunctionOfThread4( LPVOID lpParameter )
{
	while(1)
	{
		EnterCriticalSection( &g_cs );/**/
		printf("thread2 - decrease count: ");
		count=count-2;/**/
		printf("%d",count);
		printf("\n");
		LeaveCriticalSection( &g_cs );/**/
		Sleep(1000);
	}
	return 0;
}

DWORD  WINAPI FunctionOfThread5( LPVOID lpParameter )/*线程一 */
{
	while(1)
	{
		EnterCriticalSection( &g_cs );/**/
		printf("thread2 - decrease count: ");
		count=count-2;/**/
		printf("%d",count);
		printf("\n");
		LeaveCriticalSection( &g_cs );/**/
		Sleep(1000);
	}
	return 0;
}

DWORD  WINAPI FunctionOfThread6( LPVOID lpParameter )/*线程一 */
{
	while(1)
	{
		EnterCriticalSection( &g_cs );/**/
		printf("thread1 - increase count: ");
		++count;/**/
		printf("%d",count);
		printf("\n");
		LeaveCriticalSection( &g_cs );/**/
		Sleep(1000);
	}
	return 0;
}
