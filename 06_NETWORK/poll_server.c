#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <poll.h>

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
		char buf[1500];
		struct pollfd clientarr[4096];
		for(int i=1;i<4096;i++){
				clientarr[i].fd =-1;
				clientarr[i].events =POLLIN;
		}
		clientarr[0].fd = serverfd;
		clientarr[0].events = POLLIN;

		printf("Poll Server Listening....\n");
		while(1)
		{
				ready = poll(clientarr,4096,-1);
				printf("Ready Code Success..\n");
				while(ready)
				{
						//判断serverfd就绪?
						if(clientarr[0].revents == POLLIN)
						{
								socklen_t size = sizeof(clientaddr);
								clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,&size);
								//天剑新的socket到socket数组
								for(int i=1;i<4095;i++)
										if(clientarr[i].fd == -1){
												clientarr[i].fd = clientfd;
												break;
										}
						}else{
								//判断查找clientfd就绪?
								for(int i=1;i<4095;i++)
								{
										if(clientarr[i].fd != -1)
												if(clientarr[i].revents == POLLIN)
												{
														len = read(clientarr[i].fd,buf,sizeof(buf));
														j=0;
														while(len > j)
														{
																buf[j] = toupper(buf[j]);
																j++;
														}
														write(clientarr[i].fd,buf,len);
														bzero(buf,sizeof(buf));
														//客户端异常检测
														if(len == 0){
																close(clientarr[i].fd);
																clientarr[i].fd=-1;
														}
														break;
												}
								}
						}
						--ready;
				}

		}

		return 0;

}
