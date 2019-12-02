#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <arpa/inet.h>


void * thread_job(void * arg)
{
		pthread_detach(pthread_self());

		char buf[1500];
		int len,j;
		int clientfd = *(int*)arg;
		while((len = read(clientfd,buf,sizeof(buf)))>0)
		{
				j=0;
				while(len > j)
				{
						buf[j] = toupper(buf[j]);
						j++;
				}
				write(clientfd,buf,len);
				bzero(buf,sizeof(buf));
		}
		close(*(int*)arg);
		pthread_exit(NULL);
}



int main(void)
{
		//网络初始化
		struct sockaddr_in serveraddr,clientaddr;
		bzero(&serveraddr,sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons(8000);
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
		int clientfd;
		pthread_t tid;
		int serverfd = socket(AF_INET,SOCK_STREAM,0);
		bind(serverfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
		listen(serverfd,128);
		//主控线程ACCEPT
		while(1)
		{
				socklen_t size = sizeof(clientaddr);
				clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,&size);
				pthread_create(&tid,NULL,thread_job,(void*)&clientfd);
		}
		close(serverfd);
		return 0;

}
