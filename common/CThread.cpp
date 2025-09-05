#include <pthread.h>
#include <functional>
#include <iostream>
#include "CThread.h"
#include <unistd.h>
#include <cassert>



CThread::CThread(threadFunc_t func, bool ifDetach)
		: m_ifDetach(ifDetach)
		, m_func(func)
{

}
void CThread::start()
{
	assert(m_func != nullptr);
	if(!m_ifDetach)
	{
		pthread_create(&m_pid, nullptr, m_func, nullptr);
		return;
	}

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&m_pid, &attr, m_func, nullptr);
}

