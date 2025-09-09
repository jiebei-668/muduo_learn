#include <pthread.h>
#include <functional>
#include <iostream>
#include "../CThread.h"
#include <unistd.h>
#include <cassert>



void *testfunc(void *p)
{
	printf("thread %ld\n", pthread_self());
	for(int i = 0; i < 5; i++)
	{
		printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
		sleep(1);
		
	}
	return nullptr;

}
int main()
{
	CThread t1(testfunc, nullptr, true);	
	t1.start();
	sleep(10);
	printf("main exit...\n");
}
