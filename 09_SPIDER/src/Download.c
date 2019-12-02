#include <Download.h>



int Download(int webfd,char * head,url_t * u,ssl_t * ssl)
{
		char * pos;
		char buf[8192];
		char res[4096];
		int len;
		bzero(buf,sizeof(buf));
		bzero(res,sizeof(res));
		//request
		if(!ssl){
		send(webfd,head,strlen(head),0);
				printf("[5] SEND REQUEST HEAD SUCCESS...\n");
				//one recv response
				len = recv(webfd,buf,sizeof(buf),0);

				if((pos = strstr(buf,"\r\n\r\n"))==NULL)
				{
						printf("STRSTR NOT FOUND..\n");
						return -1;
				}

				snprintf(res,pos - buf + 4,"%s",buf);
				printf("[6] GET RESPONSE HEAD SUCCESS:\n%s\n",res);
				int statusCode = GetStatusCode(res);
				if(statusCode == 200){
						int fd = open(u->file,O_RDWR|O_CREAT,0775);
						write(fd,pos+4,len - (pos - buf + 4));
						while((len = recv(webfd,buf,sizeof(buf),0))>0)
						{
								write(fd,buf,len);
						}
						close(fd);
						printf("[7] DOWNLOAD SRC SUCCESS...\n");
				}else{
						printf("RESPONSE ERROR STATUS CODE:%d\n",statusCode);
						return -1;
				}
		}else{
				SSL_write(ssl->sslsocket,head,strlen(head));
				printf("[5] SSL SEND REQUEST HEAD SUCCESS...\n");
				//one recv response
				len = SSL_read(ssl->sslsocket,buf,sizeof(buf));

				if((pos = strstr(buf,"\r\n\r\n"))==NULL)
				{
						printf("STRSTR NOT FOUND..\n");
						return -1;
				}

				snprintf(res,pos - buf + 4,"%s",buf);
				printf("[6] SSL GET RESPONSE HEAD SUCCESS:\n%s\n",res);
				int statusCode = GetStatusCode(res);
				if(statusCode == 200){
						int fd = open(u->file,O_RDWR|O_CREAT,0775);
						write(fd,pos+4,len - (pos - buf + 4));
						while((len = SSL_read(ssl->sslsocket,buf,sizeof(buf)))>0)
						{
								write(fd,buf,len);
						}
						close(fd);
						free(ssl);
						ssl = NULL;
						printf("[7] SSL DOWNLOAD SRC SUCCESS...\n");
				}else{
						printf("SSL RESPONSE ERROR STATUS CODE:%d\n",statusCode);
						return -1;
				}
		}
		return 0;

}
