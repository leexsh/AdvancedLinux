#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/epoll.h>
#include <errno.h>

#define	EPOLL_MAX 200000


/*任务类型*/

typedef struct
{
		void * (*job)(void * );
		void * arg;
}task_t;



/*线程池类型*/
typedef struct
{
		int thread_max;//线程池最大线程数
		int thread_min;//线程池最小数
		int thread_alive;//存活线程数
		int thread_busy;//忙线程数
		//thread_alive - thread_busy = 闲线程数
		int thread_shutdown;//线程池开关   1:开启	0:关闭
		
		int thread_exit;//线程终止数,用于线程缩减

		pthread_t * tids;//线程id数组(消费者)
		pthread_t manager_id;//管理者线程

		task_t * queue_task; //任务队列(任务数组)
		int queue_max;//队列最大任务数
		int queue_size;//队列当前任务数
		int queue_front;//队列头索引
		int queue_rear;//队列尾索引

		pthread_cond_t not_full;//生产者条件变量
		pthread_cond_t not_empty;//消费者条件变量
		pthread_mutex_t lock;//互斥锁

}pool_t;



/* 线程池创建初始化 */
pool_t * thread_pool_create(int ,int ,int); //thread_max,thread_min,queue_max
/* 线程池销毁释放资源 */
int thread_pool_destroy(pool_t *);
/* 添加任务模块 */
int thread_add_task(pool_t *,task_t);
/* 消费者线程工作 */
void * thread_custom_job(void *); //管理者与消费者传递线程池指针参数
/* 管理者线程工作 */
void * thread_manager_job(void *);


void * user_job(void *); //用户任务实现接口


int if_thread_alive(pthread_t);



int thread_socket_init(void);
