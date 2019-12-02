#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


#define	MSG "91u23djc1890ijcxni210jd"


int main(void)
{
		int fd;
		fd = open("Myfifo",O_RDWR);
		printf("Write MSG Success..\n");
		write(fd,MSG,strlen(MSG));
		close(fd);
		return 0;

}
