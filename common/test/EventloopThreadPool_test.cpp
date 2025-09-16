#include "EventloopThreadPool.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	EventloopThreadPool pl(5, true);
	for(int ii = 0; ii < 14; ii++)
	{
		printf("%p\n", pl.getLoop());
	}
	pl.start();
	for(int ii = 0; ii < 20; ii++)
	{
		auto one = pl.getLoop();
		// printf("address_loop=%p, ", one);
		one->wakeUp();
		sleep(1);
	}
	sleep(10);
	return 0;
}
