#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <sys/wait.h>





int BLOCK(const char * file,int prono);
int CREATE(const char * sfile,const char * dfile,int blocksize,int prono);
int COPY(const char * sfile,const char * dfile,int blocksize,int pos);




int BLOCK(const char * file,int prono)
{
		int fd;
		int size;
		fd = open(file,O_RDWR);
		size = lseek(fd,0,SEEK_END);

		if(size % prono == 0)

				return size / prono;
		else
				return size / prono + 1;

}

int CREATE(const char * sfile,const char * dfile,int blocksize,int prono)
{
		int i=0;
		pid_t pid;
		for(i;i<prono;i++)
		{
				pid = fork();
				if(pid == 0)
						break;
		}
		if(pid > 0)
		{
				printf("Parent Create Child Process Success...\n");
		}else if(pid == 0)
		{
				COPY(sfile,dfile,blocksize,i * blocksize);
				//子进程完成本质工作后,要在工作区内结束进程!!!
				exit(0);
		}else{
				perror("Fork Call Failed");
		}
		return 0;
}


int COPY(const char * sfile, const char * dfile, int blocksize, int pos)
{
		int sfd,dfd;
		char buf[blocksize];
		int len;
		bzero(buf,sizeof(buf));
		sfd = open(sfile,O_RDONLY);
		dfd = open(dfile,O_WRONLY|O_CREAT,0664);

		lseek(sfd,pos,SEEK_SET);
		lseek(dfd,pos,SEEK_SET);

		len = read(sfd,buf,sizeof(buf));
		write(dfd,buf,len);
		printf("copy child pid:%d copy_pos:%d blocksize:%d\n",getpid(),pos,blocksize);
		return 0;
}




int main(int argc , char ** argv)
{
		pid_t wpid;
		if(argc < 4)
		{
				printf("Please enter filename and pronumber..tryagain..\n");
				exit(0);
		}
		/*检验限制用户传参 源文件是否存在,是否非0, 进程数是否合法*/
		/*进程数参数可选*/
		int blocksize = BLOCK(argv[1],atoi(argv[3]));
		CREATE(argv[1],argv[2],blocksize,atoi(argv[3]));
		while((wpid = wait(NULL))>0)
				printf("Parent wait child pid:%d\n",wpid);
		return 0;
}
