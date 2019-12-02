#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int copy(char * srcname,char * destname)
{
		int destfd,srcfd;
		int len;
		char buf[8192];
		bzero(buf,sizeof(buf));
		srcfd = open(srcname,O_RDONLY);
		destfd = open(destname,O_WRONLY|O_CREAT,0664);
		while((len = read(srcfd,buf,sizeof(buf)))>0)
		{
				write(destfd,buf,len);
		}
		return 0;

}


int main(int argc , char ** argv)
{
		if(argc < 3)
		{
				printf("Please Enter srcfile and desfile..\n");
				exit(0);
		}
		copy(argv[1],argv[2]);
		return 0;
}
