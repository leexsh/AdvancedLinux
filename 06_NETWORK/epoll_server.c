#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

/*IO复用poll实现单进程服务器并发效果*/


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
		//准备工作

		int ready;
		int len;
		int j;
		int i;
		char buf[1500];
		struct epoll_event readyqueue[10000];
		//创建监听集合
		int epfd = epoll_create(10000);

		struct epoll_event tmp;
		tmp.events = EPOLLIN;
		tmp.data.fd = serverfd;
		//设置第一个监听项
		epoll_ctl(epfd,EPOLL_CTL_ADD,serverfd,&tmp);

		printf("EPoll Server Listening....\n");
		while(1)
		{
				ready =  epoll_wait(epfd,readyqueue,10000,-1);
				printf("Ready Code Success..\n");
				while(ready)
				{
						i=0;
						//判断serverfd就绪?
						if(readyqueue[i].data.fd == serverfd)
						{
								socklen_t size = sizeof(clientaddr);
								clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,&size);
								tmp.data.fd = clientfd;
								tmp.events = EPOLLIN;
								epoll_ctl(epfd,EPOLL_CTL_ADD,clientfd,&tmp);
						}else{
								//判断查找clientfd就绪?
								len = read(readyqueue[i].data.fd,buf,sizeof(buf));
								j=0;
								while(len > j)
								{
										buf[j] = toupper(buf[j]);
										j++;
								}
								write(readyqueue[i].data.fd,buf,len);
								bzero(buf,sizeof(buf));
								//客户端异常检测
								if(len == 0){
										close(readyqueue[i].data.fd);
										epoll_ctl(epfd,EPOLL_CTL_DEL,readyqueue[i].data.fd,NULL);
								}
						}
						--ready;
						i++;
				}

		}

		return 0;

}
