#include "EventloopThreadPool.h"
#include <unistd.h>
#include <stdio.h>

void *testfunc(void *a)
{
	for(int ii: {0, 1, 2, 3, 4})
	{
		printf("%ld    aaaaaaaaaaaaaaaaaaaaaa\n", pthread_self());
		sleep(1);
	}
	return nullptr;
}
int main(int argc, char* argv[])
{
	EventloopThreadPool pl(5, testfunc, true);
	for(int ii = 0; ii < 14; ii++)
	{
		printf("%p\n", pl.getLoop());
	}
	pl.start();
	sleep(10);
	return 0;
}
