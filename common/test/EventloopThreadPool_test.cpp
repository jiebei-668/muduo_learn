#include "EventloopThreadPool.h"
#include <unistd.h>
#include <stdio.h>

void testfunc()
{
	for(int ii = 0; ii < 5; ii++)
	{
		printf("%ld thread\n", pthread_self());
		sleep(1);
	}
	return;
}
int main(int argc, char* argv[])
{
	EventloopThreadPool pl(5, std::bind(testfunc), true);
	for(int ii = 0; ii < 14; ii++)
	{
		printf("%p\n", pl.getLoop());
	}
	pl.start();
	sleep(10);
	return 0;
}
