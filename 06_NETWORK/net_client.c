#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main(void)
{
		//初始化
		struct sockaddr_in serveraddr;
		bzero(&serveraddr,sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons(8000);
		//通过inet_pton 对字符串IP进行转换, 转换为大端32位IP地址
		inet_pton(AF_INET,"192.168.11.162",&serveraddr.sin_addr.s_addr);


		int sockfd = socket(AF_INET,SOCK_STREAM,0);
		connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
		/*客户端 获取输入 数据请求 读取响应 展示结果*/
		char buf[1500];
		int len;
		while((fgets(buf,sizeof(buf),stdin))!=NULL)
		{
				write(sockfd,buf,strlen(buf));
				bzero(buf,sizeof(buf));
				len = read(sockfd,buf,sizeof(buf));
				printf("转换结果:%s\n",buf);
				bzero(buf,sizeof(buf));
		}
		return 0;

}
