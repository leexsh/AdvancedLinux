#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock;
int Code;
#define	NUM 5000


void * thread_job(void * arg)
{
		int tmp;
		for(int i=0;i<NUM;i++)
		{
				pthread_mutex_lock(&lock);
				tmp = Code;	
				printf("Thread tid : 0x%x\t ++Coide=%d\n",(unsigned int )pthread_self(),++tmp);
				Code = tmp;
				pthread_mutex_unlock(&lock);
		}
}



int main(void)
{
		pthread_t tid;
		pthread_mutex_init(&lock,NULL);
		pthread_create(&tid,NULL,thread_job,NULL);
		pthread_create(&tid,NULL,thread_job,NULL);
		while(1);
		/*保证线程使用完互斥锁,才可以释放*/
		pthread_mutex_destroy(&lock);
}
