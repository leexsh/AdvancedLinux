#include <Download.h>


int Connect_Webserver(int webfd,url_t * u)
{
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(u->port);
	inet_pton(AF_INET,u->ip,&serveraddr.sin_addr.s_addr);
	
	if((connect(webfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)))!=0)
	{
		perror("Connect_Wevserver Call Failed");
		return -1;
	}
	printf("[3] CONNECTION %s:%s WEBSERVER SUCCESS..\n",u->domain,u->ip);
	return 0;
}
