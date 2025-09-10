#include "EventloopThreadPool.h"
#include <cassert>



EventloopThreadPool::EventloopThreadPool(int threadNums, std::function<void(void)> func, bool ifDetach)
{
	assert(threadNums >= 0);
	m_threadNums = threadNums;
	for(int ii = 0; ii < threadNums; ii++)
	{
		m_threads.emplace_back(new EventloopThread(func, ifDetach));
	}
}
Eventloop *EventloopThreadPool::getLoop()
{
	if(m_threadNums == 0)
	{
		return nullptr;
	}
	Eventloop *ret = m_threads[m_nextLoop]->getLoop();
	m_nextLoop = (m_nextLoop + 1) % m_threadNums;	
	return ret;
	
}
void EventloopThreadPool::start()
{
	for(auto &one: m_threads)
	{
		one->startLoop();
	}
}


