#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef struct
{
		int Code;
		pthread_mutex_t Lock;
}data_t;


int main(void)
{
		/*
		//定义互斥锁
		pthread_mutex_t lock;	
		//定义互斥锁属性
		//初始化互斥锁属性
		//修改锁属性,改为进程锁
		//使用锁属性初始化锁(进程互斥锁)
		//ENDING lock为进程互斥锁
		 */
		data_t * p;

		int fd = open("filemmap",O_RDWR|O_CREAT,0664);
		ftruncate(fd,sizeof(data_t));
		p = mmap(NULL,sizeof(data_t),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		close(fd);
		/*初始化锁和设置锁属性*/
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_setpshared(&attr,PTHREAD_PROCESS_SHARED);
		pthread_mutex_init(&p->Lock,&attr);

		pid_t pid;
		pid = fork();
		if(pid > 0){
				for(int i=0;i<5000;i++){
						pthread_mutex_lock(&p->Lock);
						printf("Parent pid:%d\t++Code=%d\n",getpid(),++p->Code)	;
						pthread_mutex_unlock(&p->Lock);
				}
		}else if(pid == 0){
				for(int i=0;i<5000;i++){
						pthread_mutex_lock(&p->Lock);
						printf("Child pid:%d\t++Code=%d\n",getpid(),++p->Code)	;
						pthread_mutex_unlock(&p->Lock);
				}
		}else{
				perror("Frok Call Failed..");
				exit(0);
		}

		while(1);
		pthread_mutexattr_destroy(&attr);
		pthread_mutex_destroy(&p->Lock);
		munmap(p,sizeof(data_t));
		//回收子进程PCB
		return 0;
}
