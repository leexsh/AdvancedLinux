#include <thread_pool.h>


void * thread_custom_job(void * arg)
{
		pthread_detach(pthread_self());
		task_t task;
		pool_t * p = (pool_t *)arg;
		while(p->thread_shutdown)
		{
				pthread_mutex_lock(&p->lock);
				while(p->queue_size == 0){
						pthread_cond_wait(&p->not_empty,&p->lock);
				}
				if(p->thread_exit > 0 || p->thread_shutdown == 0)
				{
						--p->thread_exit;
						--p->thread_alive;
						pthread_mutex_unlock(&p->lock);
						pthread_exit(NULL);
				}
				task.job = p->queue_task[p->queue_rear].job;
				task.arg = p->queue_task[p->queue_rear].arg;
				--p->queue_size;
				printf("--size %d\n",p->queue_size);
				p->queue_rear = (p->queue_rear + 1)  % p->queue_max;
				++p->thread_busy;
				pthread_cond_signal(&p->not_full);
				pthread_mutex_unlock(&p->lock);
				task.job(task.arg);
				pthread_mutex_lock(&p->lock);
				--p->thread_busy;
				pthread_mutex_unlock(&p->lock);
		}
		pthread_exit(NULL);
}
