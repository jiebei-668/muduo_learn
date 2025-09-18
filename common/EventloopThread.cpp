#include "EventloopThread.h"



EventloopThread::EventloopThread(bool ifDetach)
	: m_loop(new Eventloop)
	, m_thread(new CThread(threadFunc, this, ifDetach))
{

}
Eventloop *EventloopThread::startLoop()
{
	m_thread->start();
	m_loop->setPid(m_thread->getPid());
	// m_pid = m_thread->getPid();
	return m_loop.get();
}
Eventloop *EventloopThread::getLoop()
{
	return m_loop.get();
}

