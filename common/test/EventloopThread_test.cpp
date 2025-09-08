#include "EventloopThread.h"
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
	EventloopThread th(testfunc, true);
	Eventloop *loop = th.startLoop();
	printf("%p\n", loop);
	sleep(10);
	return 0;
}
