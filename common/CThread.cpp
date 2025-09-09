#include "CThread.h"



CThread::CThread(threadFunc_t func, void *arg, bool ifDetach)
		: m_ifDetach(ifDetach)
		, m_func(func)
		, m_arg(arg)
{

}
void CThread::start()
{
	assert(m_func != nullptr);
	if(!m_ifDetach)
	{
		pthread_create(&m_pid, nullptr, m_func, m_arg);
		return;
	}

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&m_pid, &attr, m_func, m_arg);
}

