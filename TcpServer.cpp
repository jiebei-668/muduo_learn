#include "TcpServer.h"
#include "Acceptor.h"
#include "Eventloop.h"
#include "TcpConnection.h"
#include <cassert>
TcpServer::TcpServer(Eventloop *loop, Eventloop *loops[], const char *ip, const int port)
	: m_loop(loop)
	, m_acceptor(nullptr)
{
	for(int ii = 0; ii < THREAD_NUMS; ii++)
	{
		m_loops[ii] = loops[ii];
	}

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
}
void TcpServer::newConnection(int fd, struct sockaddr *client, socklen_t *len)
{
	assert(m_connectionCallback != nullptr);
//	m_connectionCallback(fd);
	printf("Acceptor::newConenctionCb===========\n");
	TcpConnection *tcpConnection = new TcpConnection(getLoop(), fd);
	m_connectionMap[tcpConnection] = tcpConnection;

	tcpConnection->setConnectionCallback(m_connectionCallback);
	tcpConnection->setCloseCallback(std::bind(&TcpServer::handleTcpConnectionClose, this,  std::placeholders::_1));
	tcpConnection->setMessageCallback(m_messageCallback);
	tcpConnection->setErrorCallback(m_errorCallback);
	tcpConnection->init();
}
void TcpServer::handleTcpConnectionClose(TcpConnection *p)
{
	m_connectionMap.erase(p);
	m_closeCallback(p);
	p->~TcpConnection();
}
