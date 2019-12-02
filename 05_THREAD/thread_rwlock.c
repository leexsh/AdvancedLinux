#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t rwlock;
int Code;
#define	NUM 5000


void * thread_read(void * arg)
{
		while(1){
				pthread_rwlock_rdlock(&rwlock);
				printf("READ THREAD:0x%x Code:%d\n",(unsigned int)pthread_self(),Code);
				pthread_rwlock_unlock(&rwlock);
				usleep(50000);
		}
}


void * thread_write(void * arg)
{
		while(1){
				pthread_rwlock_wrlock(&rwlock);
				printf("WRITE THREAD:0x%x ++Code:%d\n",(unsigned int)pthread_self(),++Code);
				pthread_rwlock_unlock(&rwlock);
				usleep(50000);
		}
}


int main(void)
{
		int i;
		pthread_rwlock_init(&rwlock,NULL);
		pthread_t tid[8];
		for(i =0 ;i<3;i++)
		{
				pthread_create(&tid[i],NULL,thread_write,NULL);
		}
		for(i =3 ;i<8;i++)
		{
				pthread_create(&tid[i],NULL,thread_read,NULL);
		}
		while(1);
		/*保证线程使用完互斥锁,才可以释放*/
		pthread_rwlock_destroy(&rwlock);
}
