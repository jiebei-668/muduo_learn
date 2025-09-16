#include "EventloopThread.h"



EventloopThread::EventloopThread(bool ifDetach)
	: m_loop(new Eventloop)
	, m_thread(new CThread(threadFunc, this, ifDetach))
{

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

