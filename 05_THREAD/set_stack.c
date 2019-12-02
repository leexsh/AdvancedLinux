#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>




void * thread_job(void*arg)
{
		while(1){
				sleep(1);
		}
}




int main(void)
{
		pthread_attr_t attr;
		pthread_t tid;
		size_t stacksize = 0x100000;
		void* stackaddr;
		int flags = 0;
		int err;
		pthread_attr_init(&attr);
		pthread_attr_getstack(&attr,&stackaddr,&stacksize);
		printf("THREAD ATTR DFL ADDRESS:%p STACKSIZE:%d\n",stackaddr,stacksize);
		while(1){
				if((stackaddr = (void*)malloc(stacksize))==NULL)
				{
						perror("malloc error");
						exit(0);
				}
				pthread_attr_setstack(&attr,stackaddr,stacksize);
				if((err = pthread_create(&tid,&attr,thread_job,NULL))>0)
				{
						printf("pthread create error:%s\n",strerror(err));
						exit(0);
				}
				printf("flags:%d\n",++flags);
				pthread_attr_destroy(&attr);

		}
		return 0;
}
