#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <signal.h>

int output_set(sigset_t pset)
{
		int i=1;
		for(i;i<32;i++)
		{
				if((sigismember(&pset,i))==1)
						putchar('1');
				else
						putchar('0');
		}
		putchar('\n');
}


int main(void )
{
		sigset_t set,oset,pset;
		sigemptyset(&set);
		sigaddset(&set,SIGINT);
		sigaddset(&set,SIGQUIT);
		sigaddset(&set,SIGKILL);
		sigprocmask(SIG_SETMASK,&set,NULL);

		while(1){
				sigpending(&pset);
				output_set(pset);
				sleep(1);
		}
		return 0;
}
