#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
		pid_t pid;
		int i=0;
		for(i=0;i<10;i++)
		{

				pid = fork();
				usleep(50000);
				if(pid == 0)
						break;
		}
		if(pid > 0){
				printf("parent pid:%d\n",getpid());
				while(1);
		}else if(pid == 0){
				printf("child pid:%d No:%d\n",getpid(),i);
				exit(0);
		}else{
				perror("fork call filed..");
		}
		return 0;
}
