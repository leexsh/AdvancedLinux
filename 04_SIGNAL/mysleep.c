#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_job(int n)
{

}



unsigned int mysleep(unsigned int seconds)
{
		struct sigaction act,oact;
		act.sa_handler = sig_job;
		act.sa_flags = 0;
		sigemptyset(&act.sa_mask);
		sigaction(SIGALRM,&act,&oact);
		unsigned int reval;
		reval = alarm(seconds);
		pause();
		return reval;
}



int main(void)
{
		while(1)
		{
				mysleep(2);
				printf("sleep two seconds..\n");
		}
}
