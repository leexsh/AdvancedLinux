#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>






void * thread_01(void * arg)
{
		printf("thread 01 tid:0x%x returning..\n",(unsigned int)pthread_self());
		return (void*)1;
}
void * thread_02(void * arg)
{
		printf("thread 02 tid:0x%x exiting..\n",(unsigned int)pthread_self());
		pthread_exit((void*)2);
}
void * thread_03(void * arg)
{
		while(1){
				printf("thread 03 tid:0x%x runing...\n",(unsigned int)pthread_self());
				sleep(1);
		}
}




int main(void)
{
		pthread_t tid;
		void * reval;
		pthread_create(&tid,NULL,thread_01,NULL);
		pthread_join(tid,&reval);
		printf("thread 01 return number:%ld\n",(long int)reval);


		pthread_create(&tid,NULL,thread_02,NULL);
		pthread_join(tid,&reval);
		printf("thread 02 exit code:%ld\n",(long int)reval);


		pthread_create(&tid,NULL,thread_03,NULL);
		sleep(3);
		pthread_cancel(tid);
		pthread_join(tid,&reval);

		printf("thread 03 cancel code:%ld\n",(long int)reval);

		return 0;
}
