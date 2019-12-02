#include <Download.h>
int Socket_Create(void)
{
	struct sockaddr_in clientaddr;
	bzero(&clientaddr,sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(8000);
	clientaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	bind(sockfd,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
	printf("[2] NET INITIALIZER SUCCESS..\n");
	return sockfd;
}


