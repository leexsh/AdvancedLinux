#include <Download.h>


int GetStatusCode(char * res)
{
		int status=0;
		char stat[20];
		bzero(stat,sizeof(stat));
		regex_t reg;
		regmatch_t match[2];
		regcomp(&reg,"HTTP/1.1 \\([^\r\n]\\+\\?\\)\r\n",0);
		if((regexec(&reg,res,2,match,0))==0)
		{
				snprintf(stat,match[1].rm_eo - match[1].rm_so + 1,"%s",res+match[1].rm_so);
		}
		sscanf(stat,"%d ",&status);
		regfree(&reg);
		return status;
}
