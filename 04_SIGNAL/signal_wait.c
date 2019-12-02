#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#include <signal.h>
#include <sys/wait.h>


void sig_wait(int n)
{
		pid_t wpid;
		int status;
		while((wpid = waitpid(-1,&status,WNOHANG))!=-1)
		{
				//exit 算正常终止 ,如果是正常终止status中保存退出码
				//signal 其他进程发送信号结束, 异常终止 ,  status中保存结束进程的信号编号
				if(wpid > 0)
				{
					if(WIFEXITED(status))
						printf("Parent Wait child Pid [%d] Exit Code [%d\n]",wpid,status);
					if(WIFSIGNALED(status))
						printf("Parent Wait child Pid [%d] Signal No [%d\n]",wpid,status);
					
				}else
						break;
		}
}

int main(void)
{
		pid_t pid;
		int i=0;
		/*父进程设置信号捕捉*/
		struct sigaction act,oact;
		act.sa_handler = sig_wait;
		act.sa_flags = 0;
		sigemptyset(&act.sa_mask);
		sigaction(SIGCHLD,&act,&oact);

		for(i;i<10;i++)
		{
				pid = fork();
				if(pid == 0)
						break;
		}

		if(pid == 0)
		{
				if(i!=9){
						printf("Child pid [%d] exiting..\n",getpid());
						exit(i);
				}else{
						while(1);
				}
		}else if(pid == -1){
				perror("fork call failed");
				exit(0);
		}
		while(1)
		{
				printf("Parent Runing...................\n");
				sleep(1);
		}
		return 0;
}
