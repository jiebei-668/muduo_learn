#include "EventloopThread.h"



EventloopThread::EventloopThread(void *(*func)(void *), bool ifDetach)
	: m_loop(new Eventloop)
	, m_thread(new CThread(func, ifDetach))
{


}
Eventloop *EventloopThread::startLoop()
{
	m_thread->start();
	return m_loop.get();
}

