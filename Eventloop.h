#pragma once
#include <vector>
#include <functional>
#include <poll.h>
#include <unordered_map>
#include <sys/eventfd.h>
#include <unistd.h>
#include <mutex>
#include "stdio.h"
class Channel;
class Eventloop
{
private:
	// thread_local Eventloop *m_loopOfThread = nullptr;
	pthread_t m_pid = 0;
	std::vector<Channel *> m_activeChannels;
	std::vector<std::function<void(void)>> m_pendingFunctors;
	int m_eventNums;
	const static int MAX_FD_NUMS = 1024;
	struct pollfd m_fds[MAX_FD_NUMS];
	std::unordered_map<int, Channel *> m_fdToChannel;
	int m_eventFd;
	std::mutex m_mutex;
public:
	Eventloop();
	~Eventloop();
	void loop();
	void removeChannel(Channel *ch);
	void registerChannel(Channel *ch);
	void wakeUp();
	void runInLoop(std::function<void(void)> f);
	bool isInLoopThread();
	void setPid(pthread_t pid);
};
