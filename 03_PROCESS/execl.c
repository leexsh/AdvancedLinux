#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main(void)
{
		//使用exec函数完成进行功能重载
		pid_t pid;
		pid = fork();
		if(pid > 0)
		{
				printf("parent pid:%d\n",getpid());
				while(1)
						sleep(1);
		}else if(pid == 0){

				printf("child pid:%d execl app..\n",getpid());
				execl("/usr/bin/firefox","firefox","www.baidu.com",NULL);
				printf("child pid:%d execl app..\n",getpid());
		}else{
				perror("exec call failed");
		}
		return 0;
}
