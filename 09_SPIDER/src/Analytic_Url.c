#include <Download.h>



int Analytic_Url(url_t * u)
{
		int i=0;
		int j=0;
		int start;
		char * arr[]={"http://","https://",NULL};
		int filesize=0;
		/* init url_t */
		bzero(u->domain,sizeof(u->domain));
		bzero(u->path,sizeof(u->path));
		bzero(u->ip,sizeof(u->ip));
		bzero(u->file,sizeof(u->file));
		/* get types */
		if(strncmp(u->url,arr[0],strlen(arr[0]))==0)
		{
				u->types = 0;
				u->port = 80;
				start = strlen(arr[0]);
		}else
		{
				u->types = 1;
				u->port = 443;
				start = strlen(arr[1]);

		}
		/* get domain */
		for(i=start;u->url[i]!='/' && u->url[i]!='\0';i++)
		{
				u->domain[j]=u->url[i];
				j++;
		}
		j=0;
		/* get filename */
		for(i=strlen(u->url);u->url[i]!='/';i--,filesize++);
		for(i=strlen(u->url)-filesize + 1;u->url[i]!='\0';i++)
		{
				u->file[j] = u->url[i];
				j++;
		}
		j=0;
		/* get path */
		for(i=start + strlen(u->domain);i<strlen(u->url) - filesize + 1;i++)	
		{
				u->path[j] = u->url[i];
				j++;
		}

		/* get ip */
		//通过dns服务,解析出公网ip地址
		struct hostent * ent = NULL;
		ent = gethostbyname(u->domain);
		//inet_ntop
		if(ent){
				inet_ntop(AF_INET,ent->h_addr_list[0],u->ip,sizeof(u->ip));
				printf("[1] DOWNLOAD APP ANALYTIC SUCCESS:\nURL:%s\nDOMAIN:%s\nFILENAME:%s\nPATH:%s\nIP:%s\nTYPES:%d\nPORT:%d\n",u->url,u->domain,u->file,u->path,u->ip,u->types,u->port);
		}
		return 0;
}
