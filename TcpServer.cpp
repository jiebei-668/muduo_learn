#include "TcpServer.h"
#include "Acceptor.h"
#include "Eventloop.h"
#include "TcpConnection.h"
#include <cassert>
TcpServer::TcpServer(Eventloop *loop, const char *ip, const int port)
	: m_loop(loop)
	, m_acceptor(nullptr)
	, m_pool(new EventloopThreadPool(THREAD_NUMS, true))
	
{
	m_acceptor.reset(new Acceptor(loop, ip, port));
	m_acceptor->setNewConnectionCallback(std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}
TcpServer::~TcpServer()
{
	for( auto& p: m_connectionMap)
	{
		m_connectionMap.erase(p.first);
		p.first->~TcpConnection();
	}
}
void TcpServer::init()
{
	assert(m_acceptor != nullptr);
	assert(m_connectionCallback != nullptr);
	assert(m_messageCallback != nullptr);
	assert(m_closeCallback != nullptr);
	assert(m_errorCallback != nullptr);
	m_acceptor->listen();
	m_pool->start();
}
void TcpServer::newConnection(int fd, struct sockaddr *client, socklen_t *len)
{
	assert(m_connectionCallback != nullptr);
//	m_connectionCallback(fd);
	printf("Acceptor::newConenctionCb===========\n");
	Eventloop *oneLoop = getLoop();
	TcpConnection *tcpConnection = new TcpConnection(oneLoop, fd);
	m_connectionMap[tcpConnection] = tcpConnection;

	tcpConnection->setConnectionCallback(m_connectionCallback);
	tcpConnection->setCloseCallback(std::bind(&TcpServer::handleTcpConnectionClose, this,  std::placeholders::_1));
	tcpConnection->setMessageCallback(m_messageCallback);
	tcpConnection->setErrorCallback(m_errorCallback);
	oneLoop->runInLoop(std::bind(&TcpConnection::init, 	tcpConnection));
	// tcpConnection->init();
}
void TcpServer::handleTcpConnectionClose(TcpConnection *p)
{
	m_connectionMap.erase(p);
	m_closeCallback(p);
	p->~TcpConnection();
}
