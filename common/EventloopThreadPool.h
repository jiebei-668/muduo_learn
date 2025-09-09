#pragma once
#include <pthread.h>
#include <functional>
#include <iostream>
#include <unistd.h>
#include <cassert>
#include <memory>
#include "Eventloop.h"
#include "EventloopThread.h"
#include "CThread.h"


class EventloopThreadPool
{
private:
	int m_threadNums;
	std::vector<EventloopThread> m_threads;
	int m_nextLoop = 0;
public:
	EventloopThreadPool(int threadNums, void *(*func)(void *), bool ifDetach = false );
	Eventloop *getLoop();
	void start();


};
