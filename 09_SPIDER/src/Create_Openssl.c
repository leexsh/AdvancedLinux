#include <Download.h>




ssl_t * Create_Openssl(int webfd)
{
		ssl_t * ssl = (ssl_t *)malloc(sizeof(ssl_t));
		//1.加载错误处理函数
		SSL_load_error_strings();
		//2.初始化openssl库函数
		SSL_library_init()	;
		//3.加载初始化加密散列函数
		OpenSSL_add_ssl_algorithms();	
		//4.生成安全证书(上下文信息) SSL_CTX
		ssl->sslctx = SSL_CTX_new(SSLv23_method());
		//5.生成加密链接 SSL
		ssl->sslsocket = SSL_new(ssl->sslctx);
		//6.通过原生webfd设置SSL
		SSL_set_fd(ssl->sslsocket,webfd);
		//7.通过SSL对服务器进行安全认证重连
		SSL_connect(ssl->sslsocket);
		return ssl;
}
