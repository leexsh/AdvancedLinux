#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>


int main(void)
{
		//初始化
		struct sockaddr_in addr,caddr;
		bzero(&addr,sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(8000);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);


		int sockfd = socket(AF_INET,SOCK_STREAM,0);
		int clientfd;
		bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
		listen(sockfd,128);
		socklen_t size = sizeof(caddr);
		//serverfd 用于建立链接 , clientfd用户与客户端进行数据交互
		if((clientfd = accept(sockfd,(struct sockaddr *)&caddr,&size))>0)
		{
				//accept是阻塞函数,等待建立链接如果连接成功则返回大于0的 new socket.
				printf("Accept connection Success..\n");
		}
		char buf[1500];
		int len,j;
		//服务端数据读取处理响应
		while((len = read(clientfd,buf,sizeof(buf)))>0)
		{
				j=0;
				while(len > j)
				{
						//处理循环
						buf[j] = toupper(buf[j]);
						j++;
				}
				write(clientfd,buf,len);
				bzero(buf,sizeof(buf));
		}
		return 0;

}
