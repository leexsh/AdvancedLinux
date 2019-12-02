#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>


int main()
{
		struct sockaddr_in serveraddr,clientaddr;
		bzero(&serveraddr,sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons (8000);
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

		int clientfd;
		int serverfd = socket(AF_INET,SOCK_STREAM,0);
		bind(serverfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
		listen(serverfd,128);
		int len;
		int j;
		int maxfd;
		int ready;
		int clientarr[1023];
		char buf[1500];
		for(int i=0;i<1023;i++)
		{
				clientarr[i] = -1;
		}
		fd_set oset,nset;
		FD_ZERO(&oset);
		FD_SET(serverfd,&oset);
		maxfd = serverfd;	

		printf("Select Server Listening..\n");
		while(1)
		{
				nset = oset;
				ready = select(maxfd + 1,&nset,NULL,NULL,NULL);
				printf("ready code seccess..\n");
				while(ready)
				{
						if(FD_ISSET(serverfd,&nset))
						{
								socklen_t size = sizeof(clientaddr);
								clientfd = accept(serverfd,(struct sockaddr*)&clientaddr,&size);
								FD_SET(clientfd,&oset);
								if(maxfd < clientfd)
								{
										maxfd = clientfd;
								}
								for(int i=0;i<1023;i++)
								{
										if(clientarr[i] == -1)
										{
												clientarr[i] = clientfd;
												break;
										}
								}
								FD_CLR(serverfd,&nset);
						}
						else
						{
								for(int i=0;i<1023;i++)
								{
										if(clientarr[i] != -1)
										{
												if(FD_ISSET(clientarr[i],&nset))
												{
														len = read(clientarr[i],buf,sizeof(buf));

														j = 0;
														while(len > j)
														{
																buf[j] = toupper(buf[j]);
																j++;
														}
														write(clientarr[i],buf,len);
														bzero(buf,sizeof(buf));
												}
												if(len == 0)
												{
														FD_CLR(clientarr[i],&oset);
														close(clientarr[i]);
														clientarr[i] = -1;
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
