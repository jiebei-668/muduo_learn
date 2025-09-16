#include <iostream>
#include <vector>
#include <poll.h>
#include <unordered_map>
#include "Channel.h"
#include "Eventloop.h"
#include <string.h>
Eventloop::Eventloop()
	: m_eventNums(0)
	, m_eventFd(eventfd(0, 0))
{
	memset(m_fds, 0, sizeof(struct pollfd)*MAX_FD_NUMS);
	m_fds[m_eventFd].fd = m_eventFd;
	m_fds[m_eventFd].events = POLLIN;
}
Eventloop::~Eventloop()
{
}
void Eventloop::removeChannel(Channel *ch)
{
	int fd = ch->getFd();
	m_fds[fd].fd = -1;
	m_fdToChannel.erase(fd);
}
void Eventloop::registerChannel(Channel *ch)
{
	int fd = ch->getFd();
	m_fds[fd].fd = fd;
	m_fds[fd].events = ch->getEvent();
	m_fdToChannel.insert({fd, ch});
}
void Eventloop::loop()
{
	while(true)
	{
		m_activeChannels.clear();
		m_eventNums = poll(m_fds, MAX_FD_NUMS, -1);
		for(int ii = 0; ii < MAX_FD_NUMS && m_eventNums > 0; ii++)
		{
			if(m_fds[ii].fd == -1 || m_fds[ii].revents == 0)
			{
				continue;
			}
			// 主要用于主线程接收新连接并将新连接分发给子线程，当子线程阻塞poll时需要唤醒他
			if(m_fds[ii].fd == m_eventFd)
			{
				printf("Eventloop addr=%p 被唤醒\n", this);
				char tmp[8];
				read(m_eventFd, tmp, 8); 
				continue;
			}
			m_fdToChannel[ii]->setRevents(m_fds[ii].revents);
			m_activeChannels.push_back(m_fdToChannel[ii]);
		}
		for(auto &one: m_activeChannels)
		{
			one->handleEvent();
		}
	}
}
void Eventloop::wakeUp()
{
	char tmp[8];
	write(m_eventFd, tmp, 8);
}
