#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>




void * thread_job(void*arg)
{
		while(1){
				sleep(1);
				printf("thread runing.....\n");
		}
}




int main(void)
{
		int detachstate;
		pthread_attr_t attr;
		pthread_t tid;

		pthread_attr_init(&attr);
		pthread_attr_getdetachstate(&attr,&detachstate);
		if(detachstate == PTHREAD_CREATE_DETACHED)	
				printf("THREAD DFL STATE DETACH..\n");
		else
				printf("THREAD DFL STATE JOINABLE..\n");
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
		pthread_create(&tid,&attr,thread_job,NULL);
		pthread_attr_destroy(&attr);
		int err;
		if((err = pthread_join(tid,NULL))>0)
		{
				printf("thread join error:%s\n",strerror(err));
				exit(0);
		}
		return 0;
}
