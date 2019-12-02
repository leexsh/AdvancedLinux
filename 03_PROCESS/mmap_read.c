#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct
{
		int id;
		char name[20];
		char sex[20];
}date_t;

int main(void)
{
		date_t * tmp;
		int fd = open("mmapfile",O_RDWR);
		tmp = mmap(NULL,sizeof(date_t),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		close(fd);
		/*循环读取用户信息*/
		while(1)
		{
				printf("ID:%d\n",tmp->id);
				printf("用户名:%s\n",tmp->name);
				printf("性别:%s\n",tmp->sex);
				sleep(1);
		}

		munmap(tmp,sizeof(date_t));
		return 0;
}
