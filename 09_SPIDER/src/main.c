#include <Download.h>


int main(void)
{
		url_t tmp;
		url_t node;
		ssl_t * ssl = NULL;
		datefd = open("resdate.html",O_RDWR|O_CREAT,0775);
		char head[4096];
		char * url = "https://baike.baidu.com/item/%E5%88%98%E5%BE%B7%E5%8D%8E/114923?fr=aladdin";
		strcpy(tmp.url,url);
		//已处理和未处理的队列创建以及初始化
		queue_t * w = Queue_Create(100);
		queue_t * y = Queue_Create(10000);
		printf("待处理 [%s] 链接..\n",tmp.url);
		int webfd = Socket_Create();
		//第一次将种子url投放到未处理队列
		if(Notin(w,tmp.url) && Notin(y,tmp.url))
				Queue_En(w,tmp);
		//未处理队列循环(未处理队列不为空)
		while(w->size > 0){
				//对未处理队列进行出队
				Queue_De(w,&node);
				Analytic_Url(&node);
				Connect_Webserver(webfd,&node);
				Create_GetHead(head,&node);
				if(node.types)
						ssl = Create_Openssl(webfd);
				Download(webfd,head,&node,ssl);
				Queue_En(y,node);
				//html解析模块,传入两个队列,入队和去重
				Analytic_Html(&node,w,y);
		}
		close(datefd);
		return 0;
}
