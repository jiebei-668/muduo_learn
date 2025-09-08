#pragma once
#include "CThread.h"
#include <vector>

class CThreadPool
{
private:
	int m_threadNums;
	void *(*m_func)(void *);
	std::vector<CThread> m_threads;
public:
	int getThreadNums();
	CThreadPool(int num, void *(*func)(void *), bool ifDetach=true);
	void start();

};
