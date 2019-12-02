#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>

void sig_wait(int n)
{
		pid_t wpid;
		while((wpid = waitpid(-1,NULL,WNOHANG))>0)
		{
				//一个信号传递过来,尽可能回收多次
				printf("Parent Process Wait Success child pid [%d]\n",wpid);
		}
}

void * thread_job(void * arg)
{
		printf("wait thread tid:0x%x runing....\n",(unsigned int)pthread_self());
		sigset_t set;
		sigemptyset(&set);
		sigprocmask(SIG_SETMASK,&set,NULL);
		while(1)
				sleep(1);
}

int main(void)
{
		pid_t pid;
		pthread_t tid;
		struct sockaddr_in addr,caddr;
		bzero(&addr,sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(8000);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);


		int sockfd = socket(AF_INET,SOCK_STREAM,0);
		int clientfd;
		bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
		listen(sockfd,128);
		socklen_t size = sizeof(caddr);
		/*信号捕捉设定与信号屏蔽字设定*/
		sigset_t set,oset;
		struct sigaction act,oact;
		sigemptyset(&set);
		sigaddset(&set,SIGCHLD);
		sigprocmask(SIG_SETMASK,&set,&oset);
		act.sa_handler = sig_wait;
		act.sa_flags = 0;
		sigemptyset(&act.sa_mask);
		sigaction(SIGCHLD,&act,&oact);

		pthread_create(&tid,NULL,thread_job,NULL);
		while(1){
				if((clientfd = accept(sockfd,(struct sockaddr *)&caddr,&size))>0)
				{
						printf("Process Server Accept connection Success Create process..\n");
						pid = fork();
						if(pid == 0)
								break;
				}	
		}
		if(pid == 0)
		{
				//子进程除处理业务外要检测客户端异常,及时发现,终止自身进程,进入回收阶段
				//使用心跳保活方案检测客户端
				char buf[1500];
				int len,j;
				while((len = read(clientfd,buf,sizeof(buf)))>0)
				{
						j=0;
						while(len > j)
						{
								//处理循环
								buf[j] = toupper(buf[j]);
								j++;
						}
						write(clientfd,buf,len);
						bzero(buf,sizeof(buf));
				}
				if(len == 0){
						printf("处理进程[%d] Exiting..\n",getpid());
						close(clientfd);
						exit(0);
				}

		}
		return 0;

}
