#pragma once
#include <pthread.h>
#include <functional>
#include <iostream>
#include <unistd.h>
#include <cassert>



class CThread
{
private:
	pthread_t m_pid;
	using threadFunc_t = void *(*)(void *);
	threadFunc_t m_func;
	void *m_arg = nullptr;
	bool m_ifDetach = false;
public:
	CThread(threadFunc_t func, void *arg, bool ifDetach = false );
	void start();

};
