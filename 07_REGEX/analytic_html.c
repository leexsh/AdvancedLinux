#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>




int main(void)
{
		//文件映射生成内容地址,方便匹配处理
		char url[4096];
		char title[1024];
		int fd;
		fd = open("world.html",O_RDONLY);
		int size = lseek(fd,0,SEEK_END);
		char * p = mmap(NULL,size,PROT_READ,MAP_PRIVATE,fd,0);
		regex_t reg;
		regmatch_t match[3];
		regcomp(&reg,"<a[^>]\\+\\?href=\"\\([^\"]\\+\\?\\.\\?html\\)\"[^>]\\+\\?>\\([^<]\\+\\?\\)</a>",0);
		while((regexec(&reg,p,3,match,0))==0)
		{
				snprintf(url,match[1].rm_eo - match[1].rm_so + 1,"%s",p+match[1].rm_so);	
				snprintf(title,match[2].rm_eo - match[2].rm_so + 1,"%s",p+match[2].rm_so);	
				p+=match[0].rm_eo;

				printf("url [%s]   title[%s]\n",url,title);
				bzero(url,sizeof(url));
				bzero(title,sizeof(title));
		}
		regfree(&reg);
		munmap(p,size);
		return 0;
}
