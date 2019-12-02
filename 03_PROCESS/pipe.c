#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define	MSG	"ikoanmc8i9021nmco1icnjhc1i2ocn21c"

int main(void)
{
		/*先创建管道后,创建子进程*/
		pid_t pid;
		int fds[2];
		pipe(fds);
		pid = fork();
		if(pid > 0){
				//父写子读
				close(fds[0]);
				printf("Parent pid %d Write Msg KernelBuf..\n",getpid());
				write(fds[1],MSG,strlen(MSG));
				while(1);

		}else if(pid == 0){
				close(fds[1]);
				char buf[1024];
				bzero(buf,sizeof(buf));
				int len = read(fds[0],buf,sizeof(buf));
				printf("Child pid %d Read Msg:\n%s\n",getpid(),buf);
				while(1);
		}else{
		}
		return 0;
}
