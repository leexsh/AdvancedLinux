#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>




int main(void)
{
		int fd;
		char buf[8192];
		bzero(buf,sizeof(buf));
		fd = open("Myfifo",O_RDONLY);
		sleep(10);
		int len = read(fd,buf,sizeof(buf));
		printf("Read Success:%s\n",buf);
		close(fd);
		return 0;

}
