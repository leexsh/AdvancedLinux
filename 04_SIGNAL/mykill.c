#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>


#include <signal.h>


int main(int argc , char ** argv)
{
		if(argc < 3)
		{
				printf("Enter Pid and Signal number..\n");
				exit(0);
		}
		kill(atoi(argv[2]),atoi(argv[1]));
		return 0;
}
