#include "EventloopThread.h"



EventloopThread::EventloopThread(std::function<void(void)> func, bool ifDetach)
	: m_loop(new Eventloop)
	, m_func(func)
	, m_thread(new CThread(threadFunc, this, ifDetach))
{
	printf("%p\n", this);	

}
Eventloop *EventloopThread::startLoop()
{
	m_thread->start();
	return m_loop.get();
}
Eventloop *EventloopThread::getLoop()
{
	return m_loop.get();
}

