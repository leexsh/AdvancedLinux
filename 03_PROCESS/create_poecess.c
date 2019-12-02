
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




int main(void)
{
		int a=30;
		pid_t pid;
		pid = fork();
		if(pid > 0)
		{
				//parent job
				printf("im parent pid:%d ...\n",getpid());
				printf("%d\n",a);
				sleep(2);
				printf("%d\n",a);
				

		}else if(pid == 0)
		{
				//child job
				printf("im child pid:%d ...\n",getpid());
				printf("%d\n",a);
				++a;
				printf("%d\n",a);
				while(1);
		}{
				perror("fork call failed");
		}
		while(1);
		return 0;
}
