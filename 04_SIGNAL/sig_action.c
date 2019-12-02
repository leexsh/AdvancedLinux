#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <signal.h>

void sig_work(int n)
{
		int flags=0;
		while(flags<3)
		{
				printf("flags = %d\n",++flags);
				sleep(1);
		}
}


int main(void )
{
		struct sigaction act,oact;
		act.sa_handler = sig_work;
		act.sa_flags = 0;
		sigemptyset(&act.sa_mask);

		sigaction(SIGINT,&act,&oact);

		while(1);

		return 0;
}
