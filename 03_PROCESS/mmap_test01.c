#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(void)
{
		int fd = open("testmap",O_RDWR);
		int size = lseek(fd,0,SEEK_END);
		mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		close(fd);
		munmap(,);
		return 0;
}
