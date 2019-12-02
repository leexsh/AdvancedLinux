#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main(void)
{
		pid_t pid;
		pid = fork();
		if(pid > 0)
		{
				printf("parent 组ID %d 进程ID %d 会话%d \n",getpgrp(),getpid(),getsid(getpid()));
				while(1);

		}
		else if(pid == 0)
		{
				printf("child 组ID %d 进程ID %d 会话%d \n",getpgrp(),getpid(),getsid(getpid()));
				sleep(5);
				setsid();
				printf("child new 组ID %d 进程ID %d 会话%d \n",getpgrp(),getpid(),getsid(getpid()));
				while(1);
		}
		else
				perror("fork call failed..");
		return 0;
}
