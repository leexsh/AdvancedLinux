#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void												*thread_job(void * arg)
{
		while(1){
				printf("thread tid:0x%x runing...\n",(unsigned int)pthread_self());
						sleep(1);
		}
		//pthread_exit();
		//return 
}

int main(void)
{
		printf("Main thread tid:0x%x Create thread...\n",(unsigned int)pthread_self());
		pthread_t tid;
		pthread_create(&tid,NULL,thread_job,NULL);
		printf("Main create thread tid:0x%x\n",(unsigned int)tid);
		while(1)
				sleep(1);
		//pthread_exit()

}
