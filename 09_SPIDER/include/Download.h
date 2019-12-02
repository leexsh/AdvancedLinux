#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <regex.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <sys/mman.h>

int datefd;

typedef struct
{
		SSL * sslsocket; //可以进行安全认证的socket
		SSL_CTX * sslctx;//认证证书(上下文信息)

}ssl_t;


typedef struct
{
		char url[8192];
		int types;
		char domain[1024];
		char path[4096];
		char file[1024];
		char ip[16];
		int port;

}url_t;
//队列类型
typedef struct
{
		int front;
		int rear;
		int size;
		int max;
		url_t * urlarr;
}queue_t;



int Analytic_Url(url_t *);
int Socket_Create(void);
int Connect_Webserver(int,url_t *);
int Create_GetHead(char * , url_t *);
int Download(int ,char *,url_t *,ssl_t *);
int GetStatusCode(char *);
ssl_t * Create_Openssl(int );
int Analytic_Html(url_t * , queue_t * , queue_t *);

//队列访问接口
queue_t * Queue_Create(int);
int Queue_En(queue_t *,url_t);
int Queue_De(queue_t * , url_t *);
int Notin(queue_t * , const char *);
int Save(const char * ,const char * ,const char * );
