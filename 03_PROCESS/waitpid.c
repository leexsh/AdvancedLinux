#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>



int main(void)
{
		pid_t pid;
		pid = fork();
		if(pid > 0)
		{
				printf("parent pid %d alive \n",getpid());

		}
		else if(pid == 0)
		{
				printf("child pid %d alive \n",getpid());
				sleep(5);
				exit(0);
		}
		else
				perror("fork call failed..");
		pid_t wpid;
		while((wpid = waitpid(-1,NULL,WNOHANG))!=-1)
		{
				if(wpid > 0){	
						printf("parent wait child Successful..\n");
				}else if(wpid == 0){
						printf("parent pid %d alive \n",getpid());
						sleep(1);
				}
		}
		return 0;
}
