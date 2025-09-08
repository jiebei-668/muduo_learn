#include "CThreadPool.h"

int CThreadPool::getThreadNums(){return m_threadNums;}
CThreadPool::CThreadPool(int num, void *(*func)(void *), bool ifDetach)
	:m_threadNums(num)
	,m_func(func)
{
	for(int ii = 0; ii < num; ii++)
	{
		m_threads.push_back( CThread(func, ifDetach) );
	}
}
void CThreadPool::start()
{
	for(auto one: m_threads)
	{
		one.start();
	}
}

