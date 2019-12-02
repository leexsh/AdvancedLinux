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
		int i=0;
		date_t * tmp;
		/*创建映射文件,拓展空文件,拓展为数据结构大小*/
		int fd = open("mmapfile",O_RDWR|O_CREAT,0664);
		ftruncate(fd,sizeof(date_t));  //拓展成结构体大小
		tmp = mmap(NULL,sizeof(date_t),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		close(fd);
		/*循环写入用户信息*/
		while(1)
		{
				tmp->id = i;
				sprintf(tmp->name,"Colin %d",i);
				if(i%2==0)
						tmp->sex="male";
				else
						tmp->sex="female";

				i++;
				sleep(1);
		}

		munmap(tmp,sizeof(date_t));
		return 0;
}
