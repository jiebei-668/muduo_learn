// 封装的使用Eventloop::loop()作为线程函数的线程类，并为直接封装pthread，而是使用已经过封装的CThread类
// 线程函数是Eventloop::loop(), 使用c++11 function类型 std::function<void(void)>
// 初始化参数只有一个 是否分离，默认分离
// 使用 Eventloop *startLoop() 开启线程函数，并返回m_loop成员
#pragma once
#include <pthread.h>
#include <functional>
#include <iostream>
#include <unistd.h>
#include <cassert>
#include <memory>
#include "Eventloop.h"
#include "CThread.h"


class EventloopThread
{
private:
	std::unique_ptr<Eventloop> m_loop;
	std::unique_ptr<CThread> m_thread;
	std::function<void(void)> m_func;
public:
	EventloopThread(bool ifDetach = false );
	// 调用m_thread的start并返回Eventloop *
	Eventloop *startLoop();
	Eventloop *getLoop();
	static void *threadFunc(void *arg)
	{
		EventloopThread *thread = static_cast<EventloopThread *>(arg);
		thread->m_loop->loop();
		return nullptr;
	}

};
