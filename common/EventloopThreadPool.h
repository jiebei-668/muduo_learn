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
	// 这个线程数目，不包含主线程（acceptor线程),只包含通信线程，可以为0 
	int m_threadNums;
	std::vector<std::unique_ptr<EventloopThread>> m_threads;
	int m_nextLoop = 0;
public:
	// EventloopThreadPool(int threadNums, void *(*func)(void *), bool ifDetach = false );
	EventloopThreadPool(int threadNums,  bool ifDetach = false );
	// 获取一个loop指针，搜索方法是循环
	Eventloop *getLoop();
	// 开启所有线程的函数
	void start();

};
