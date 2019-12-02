#include <Download.h>


int Analytic_Html(url_t * u,queue_t * wque, queue_t * yque)
{
		int fd = open(u->file,O_RDONLY);
		int size = lseek(fd,0,SEEK_END);
		char * string = mmap(NULL,size,PROT_READ,MAP_PRIVATE,fd,0);
		char * jstr = string;
		regex_t treg;
		regex_t dreg;
		regex_t areg;
		regmatch_t tmatch[2];
		regmatch_t dmatch[2];
		regmatch_t amatch[2];
		char title[1024];
		char desc[8192];
		char url[4096];
		url_t node;
		bzero(title,sizeof(title));
		bzero(desc,sizeof(desc));
		bzero(url,sizeof(url));

		regcomp(&treg,"<h1 >\\([^<]\\+\\?\\)</h1>",0);
		regcomp(&dreg,"<meta name=\"description\" content=\"\\([^\"]\\+\\?\\)\">",0);
		regcomp(&areg,"<a[^>]\\+\\?href=\"\\(/item/[^\"]\\+\\?\\)\"[^>]\\+\\?>[^<]\\+\\?</a>",0);

		if((regexec(&treg,string,2,tmatch,0))==0)
		{
				snprintf(title,tmatch[1].rm_eo - tmatch[1].rm_so + 1,"%s",string + tmatch[1].rm_so);
				printf("ANALYTIC HTML SUCCESS:\n");
				printf("H1:%s\n",title);
		}
		if((regexec(&dreg,string,2,dmatch,0))==0)
		{
				snprintf(desc,dmatch[1].rm_eo - dmatch[1].rm_so + 1,"%s",string + dmatch[1].rm_so);
				printf("DISCRIPTION:%s\n",desc);
		}
		while((regexec(&areg,string,2,amatch,0))==0)
		{
				snprintf(url,amatch[1].rm_eo - amatch[1].rm_so + 24,"https://baike.baidu.com%s",string + amatch[1].rm_so);
				//printf("%s\n",url);
				if(Notin(wque,url) && Notin(yque,url))
				{
						strcpy(node.url,url);
						Queue_En(wque,node);
				}
				bzero(url,sizeof(url));
				string+=amatch[0].rm_eo;
				printf("wque front:%d rear:%d size:%d\n",wque->front,wque->rear,wque->size);
		}
		Save(title,desc,u->url);
		regfree(&treg);
		regfree(&dreg);
		regfree(&areg);
		munmap(jstr,size);
		close(fd);
		unlink(u->file);
		return 0;

}

