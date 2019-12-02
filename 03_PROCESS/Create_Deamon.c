#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <time.h>
#include <string.h>


int Create_Deamon(void)
{
		pid_t pid;
		pid = fork();
		if(pid > 0){
				exit(0);
		}else if(pid == 0){
				setsid();
				close(STDIN_FILENO);
				close(STDOUT_FILENO);
				chdir("/tmp/");
				umask(2);
				//守护进程核心工作
				int fd = open("file.log",O_RDWR|O_CREAT,0664);
				time_t t;
				char timebuf[100];
				while(1)
				{
						t = time(NULL);
						ctime_r(&t,timebuf);
						write(fd,timebuf,strlen(timebuf));
						sleep(3);
						bzero(timebuf,sizeof(timebuf));
				}
				//守护退出处理
				close(fd);

		}else{
				//错误处理
		}
		return 0;
}


int main(void)
{
		Create_Deamon();
}
