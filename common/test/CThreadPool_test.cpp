#include <pthread.h>
#include <functional>
#include <iostream>
#include <unistd.h>
#include <cassert>
#include "CThread.h"
#include "CThreadPool.h"



void *testfunc(void *p)
{
	for(int i = 0; i < 5; i++)
	{
		printf("%ld  aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n", pthread_self());
		sleep(1);
		
	}

}
int main()
{
	CThreadPool pool(5, testfunc, true);
	pool.start();
	sleep(10);
	printf("main exit...\n");
}
