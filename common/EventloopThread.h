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
public:
	EventloopThread(void *(*func)(void *), bool ifDetach = false );
	// 调用m_thread的start并返回Eventloop *
	Eventloop *startLoop();
	Eventloop *getLoop();

};
