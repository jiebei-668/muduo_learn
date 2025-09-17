// 封装pthread的CThread
// 使用类型 void *(*)(void *) 作为线程函数的类型
// 初始化需要指定线程函数，线程函数参数和是否分离（默认分离）
// 使用 start() 方法启动，即启动 pthread_create
#pragma once
#include <pthread.h>
#include <functional>
#include <iostream>
#include <unistd.h>
#include <cassert>



class CThread
{
private:
	pthread_t m_pid;
	using threadFunc_t = void *(*)(void *);
	threadFunc_t m_func;
	void *m_arg = nullptr;
	bool m_ifDetach = false;
public:
	CThread(threadFunc_t func, void *arg, bool ifDetach = false );
	void start();

};
