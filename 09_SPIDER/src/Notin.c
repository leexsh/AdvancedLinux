#include <Download.h>


int Notin(queue_t * q, const char * url)
{
		int i = q->rear;
		while( i % q->max != q->front)
		{
				if((strncmp(q->urlarr[i].url,url,strlen(url)))==0)

						return 0;

				i++;
		}
		return 1;
}
