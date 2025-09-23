#pragma once
#include "Acceptor.h"
#include "TcpConnection.h"
#include <unordered_map>
#include "Eventloop.h"
#include "stdio.h"
#include "CThread.h"
#include "CThreadPool.h"
#include "EventloopThreadPool.h"
#define THREAD_NUMS 5
// 注：使用方法 指定四个回调（对应TcpConnection中四个）后 调用init()
class TcpServer
{
private:
	// acceptor的loop
	Eventloop *m_loop;
	// 通信子线程的loop
	// Eventloop *m_loops[THREAD_NUMS];
	std::unique_ptr<EventloopThreadPool> m_pool;
	int next_loop = 0;
	std::unique_ptr<Acceptor> m_acceptor;
	// 用地址作为key，也用地址作为value
	std::unordered_map<TcpConnection *, TcpConnection *> m_connectionMap;
	// 注：使用TcpServer时必须指定 m_connectionCallback, m_messageCallback, m_closeCallback, m_errorCallback
	// 它们分别传递给TcpConnection类的对象使用
	// 分别对应连接建立调用的函数，有消息时调用的函数，对端socked关闭时调用的函数，错误处理的函数
	std::function<void(int)> m_connectionCallback;
	std::function<void(int, char *, int)> m_messageCallback;
	std::function<void(TcpConnection *)> m_closeCallback;
	std::function<void(TcpConnection *)> m_errorCallback;

public:
	TcpServer(Eventloop *loop, const char *ip, const int port);
	~TcpServer();
	// 获取通信子线程的loop，没有就返回m_loop
	Eventloop *getLoop()
	{
		if(THREAD_NUMS == 0)
		{
			return m_loop;
		}
		return m_pool->getLoop();
	}
	void setConnectionCallback(std::function<void(int)> cb)
	{
		m_connectionCallback = cb;
	}
	void setMessageCallback(std::function<void(int, char *, int)> cb)
	{
		m_messageCallback = cb;
	}
	void setCloseCallback(std::function<void(TcpConnection *)> cb)
	{
		m_closeCallback = cb;
	}
	void setErrorCallback(std::function<void(TcpConnection *)> cb)
	{
		m_errorCallback = cb;
	}
	void handleTcpConnectionClose(TcpConnection *p);
	// 该函数传递给Acceptor使用
	// 函数内负责初始化新的TcpConnection对象，执行Acceptor的newconnection回调，设置其四个回调并启动TcpConnection
	void newConnection(int fd, struct sockaddr *client, socklen_t *len);
	// 该函数主要用于启动Acceptor
	// 注意由于Acceptor的实现特点，init调用需要在设置好四个回调m_connectionMap, m_messageCallback, m_closeCallback, m_errorCallback后
	void init();
};
