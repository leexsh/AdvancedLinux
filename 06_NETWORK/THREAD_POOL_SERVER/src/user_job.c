/*用户实现任务接口*/
#include <thread_pool.h>


void * user_job(void * arg)
{
		int clientfd = *(int *)arg;
		int j;
		char buf[1500];
		bzero(buf,sizeof(buf));
		int len = read(clientfd,buf,sizeof(buf));
		while(len > j)
		{
				j=0;
				buf[j]=toupper(buf[j]);
				j++;
		}
		write(clientfd,buf,len);	
		//如果len==0(客户端异常) user_job返回clientfd;
		return NULL;
}
