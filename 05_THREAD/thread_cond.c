#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


//使用条件变量完成线程协同配合交替工作
pthread_cond_t cd;
pthread_mutex_t lock;
int Code;
#define	NUM 5000


void * thread_job_1(void * arg)
{
		while(1){
				pthread_mutex_lock(&lock);
				while(counter % 2 != 0){ 
						pthread_cond_wait(&cd,&lock);
						//wait函数第一次调用,挂起并解锁
						//唤醒时调用,上锁
				}
				printf("偶数 THREAD A ++COUNTER:%d\n",++counter);
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&cd);
		}
}

void * thread_job_2(void * arg)
{

		while(1){
				pthread_mutex_lock(&lock);
				while(counter % 2 == 0){ 
						pthread_cond_wait(&cond,&lock); //挂起解锁，唤醒上锁
				}
				printf(" 基数 THREAD B ++COUNTER:%d\n",++counter);
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&cd);
		}
}


void * thread_job02(void * arg)



int main(void)
{
		pthread_t tid;
		pthread_mutex_init(&lock,NULL);
		pthread_cond_init(&cd,NULL);
		pthread_create(&tid,NULL,thread_job_1,NULL);
		pthread_create(&tid,NULL,thread_job_2,NULL);
		while(1);
		/*保证线程使用完互斥锁,才可以释放*/
		pthread_mutex_destroy(&lock);
		pthread_cond_destroy(&cd);
}
