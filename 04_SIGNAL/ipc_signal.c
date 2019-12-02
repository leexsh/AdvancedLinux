#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>





void parent_sig(int n,siginfo_t * info, void * arg)
{
		/*1.打印输出信号携带数据*/
		printf("PARENT PID:%d CODE=%d\n",getpid(),info->si_int);
		/*2.重新计算数据*/
		union sigval val;
		val.sival_int = ++(info->si_int);
		/*3.信号回传数据*/
		usleep(500000);
		sigqueue(getpid()+1,SIGUSR1,val);

}


void child_sig(int n,siginfo_t * info, void * arg)
{
		/*1.打印输出信号携带数据*/
		printf("CHILD PID:%d CODE=%d\n",getpid(),info->si_int);
		/*2.重新计算数据*/
		union sigval val;
		val.sival_int = ++(info->si_int);
		/*3.信号回传数据*/
		usleep(500000);
		sigqueue(getppid(),SIGUSR2,val);

}



int main(void)
{
		/*1.父进程信号捕捉流程*/
		struct sigaction act,oact;
		act.sa_sigaction = parent_sig;
		sigemptyset(&act.sa_mask);
		act.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR2,&act,&oact);
		/*1.1父进程设置信号屏蔽字,继承给子进程,屏蔽SIGUSR1*/
		sigset_t set,oset;
		sigemptyset(&set);
		sigaddset(&set,SIGUSR1);
		sigprocmask(SIG_SETMASK,&set,&oset);
		/*2.父进程创建子进程*/
		pid_t pid;
		pid = fork();
		if(pid > 0){
				//父进程发送第一次信号并携带数据
				union sigval val;
				val.sival_int = 1;
				sigqueue(pid,SIGUSR1,val);
				while(1)
						sleep(1);
		}else if(pid == 0){
				/*3.子进程信号捕捉流程*/
				struct sigaction act,oact;
				act.sa_sigaction = child_sig;
				sigemptyset(&act.sa_mask);
				act.sa_flags = SA_SIGINFO;
				sigaction(SIGUSR1,&act,&oact);	
				/*4.子进程解除SIGUSR1信号的屏蔽*/
				sigset_t set;
				sigemptyset(&set);
				sigprocmask(SIG_SETMASK,&set,NULL);
				while(1)
						sleep(1);
		}else{
				perror("fork call failed");
				exit(0);
		}
}
