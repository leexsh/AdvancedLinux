#include <stdio.h>
#include <unistd.h>


//定时器定时,看看计算频率和次数



int main(void)
{
		unsigned int seconds;
		seconds = alarm(1);
		int code=0;
		while(1)
		{
				printf("++Code %d\t",++code);
		}
		return 0;
}
