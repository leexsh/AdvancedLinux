#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main(void)
{
		pid_t pid;
		pid = fork();
		if(pid > 0)
		{
				printf("parent pid %d alive \n",getpid());
				while(1);

		}
		else if(pid == 0)
		{
				printf("child pid %d alive \n",getpid());
				while(1);
		}
		else
				perror("fork call failed..");
		return 0;
}
