#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/select.h>

/*IO复用select实现单进程服务器并发效果*/


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
		int maxfd;
		int ready;
		int len;
		int j;
		char buf[1500];
		int clientarr[1023];
		for(int i=0;i<1023;i++)
				clientarr[i]=-1;
		fd_set oset,nset;
		FD_ZERO(&oset);
		FD_SET(serverfd,&oset);
		maxfd = serverfd;
		printf("Select Server Listening....\n");
		while(1)
		{
				nset = oset;//分离传入传出
				ready = select(maxfd + 1,&nset,NULL,NULL,NULL);
				printf("Ready Code Success..\n");
				while(ready)
				{
						//判断serverfd就绪?
						if(FD_ISSET(serverfd,&nset))
						{
								socklen_t size = sizeof(clientaddr);
								clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,&size);
								//添加新的socket到监听集合
								FD_SET(clientfd,&oset);
								//重新计算最大文件描述符
								if(maxfd < clientfd)
										maxfd = clientfd;
								//天剑新的socket到socket数组
								for(int i=0;i<1023;i++)
										if(clientarr[i]==-1){
												clientarr[i]=clientfd;
												break;
										}
								//处理事件任务后,将就绪参照清空
								FD_CLR(serverfd,&nset);
						}else{
								//判断查找clientfd就绪?
								for(int i=0;i<1023;i++)
								{
										if(clientarr[i]!=-1)
												if(FD_ISSET(clientarr[i],&nset))
												{
														len = read(clientarr[i],buf,sizeof(buf));
														j=0;
														while(len > j)
														{
																buf[j] = toupper(buf[j]);
																j++;
														}
														write(clientarr[i],buf,len);
														bzero(buf,sizeof(buf));
														//客户端异常检测
														if(len == 0){
																FD_CLR(clientarr[i],&oset);
																close(clientarr[i]);
																clientarr[i]=-1;
														}
														break;
												}

										FD_CLR(clientarr[i],&nset);
								}
						}
						--ready;
				}

		}

		return 0;

}
