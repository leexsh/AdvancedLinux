#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main(void)
{
		pid_t pid;
		pid = fork();
		if(pid > 0)
		{
				printf("parent pgid %d pid %d alive \n",getpgrp(),getpid());
				while(1);

		}
		else if(pid == 0)
		{
				printf("child pgid %d pid %d alive \n",getpgrp(),getpid());
				sleep(1);
				setpgid(getpid(),getpid());
				printf("child New pgid %d pid %d alive \n",getpgrp(),getpid());
				
		}
		else
				perror("fork call failed..");
		return 0;
}
