#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void * thread_job(void * arg)
{
		while(1)
				sleep(1);
}


int main(void)
{
		pthread_t tid;
		int err;
		int flags = 0;
		while(1)
		{
				if((err = pthread_create(&tid,NULL,thread_job,NULL))>0)
				{
						printf("thread create error:%s\n",strerror(err));
						exit(0);
				}
				printf("flags=%d\n",++flags);
		}
		return 0;
}
