#ifndef __EVENTLOOP__H__
#define __EVENTLOOP__H__
#include <vector>
#include <poll.h>
#include <unordered_map>
#include <sys/eventfd.h>
#include <unistd.h>
#include "stdio.h"
class Channel;
class Eventloop
{
private:
	std::vector<Channel *> m_activeChannels;
	int m_eventNums;
	const static int MAX_FD_NUMS = 1024;
	struct pollfd m_fds[MAX_FD_NUMS];
	std::unordered_map<int, Channel *> m_fdToChannel;
	int m_eventFd;
public:
	Eventloop();
	~Eventloop();
	void loop();
	void removeChannel(Channel *ch);
	void registerChannel(Channel *ch);
	void wakeUp();
};
#endif
