#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>





void parent_sig(int n,siginfo_t * info, void * arg)
{
		/*1.打印输出信号携带数据*/
		/*2.重新计算数据*/
		/*3.信号回传数据*/

}


void child_sig(int n,siginfo_t * info, void * arg)
{
		/*1.打印输出信号携带数据*/
		/*2.重新计算数据*/
		/*3.信号回传数据*/

}



int main(void)
{
		/*1.父进程信号捕捉流程*/
		/*1.1父进程设置信号屏蔽字,继承给子进程,屏蔽SIGUSR1*/
		/*2.父进程创建子进程*/
				//父进程发送第一次信号并携带数据
				/*3.子进程信号捕捉流程*/
				/*4.子进程解除SIGUSR1信号的屏蔽*/
}
