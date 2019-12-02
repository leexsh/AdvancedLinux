#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int OPEN(const char *pathname, int flags)
{
	int fd;
	if((fd = open(pathname,flags))==-1)
		perror("open call failed");
	return fd;
}


int main(void)
{
	int fd;
	
	fd = OPEN("aaa",O_RDWR);
	return 0;
}
