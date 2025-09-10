all: CThread_test CThreadPool_test EventloopThread_test EventloopThreadPool_test
CThread_test: ../CThread.cpp ../CThread.h CThread_test.cpp
	g++ -g -o CThread_test CThread_test.cpp ../CThread.cpp -pthread
CThreadPool_test: ../CThread.cpp ../CThread.h ../CThreadPool.h ../CThreadPool.cpp CThreadPool_test.cpp
	g++ -g -o CThreadPool_test CThreadPool_test.cpp ../CThread.cpp ../CThreadPool.cpp -I../ -pthread

EventloopThread_test: ../CThread.cpp ../CThread.h ../EventloopThread.h ../EventloopThread.cpp EventloopThread_test.cpp ../../Eventloop.h ../../Eventloop.cpp ../../Channel.h ../../Channel.cpp
	g++ -g -o EventloopThread_test ../CThread.cpp ../EventloopThread.cpp EventloopThread_test.cpp ../../Eventloop.cpp ../../Channel.cpp -I../ -I../../ -pthread
EventloopThreadPool_test: ../CThread.cpp ../CThread.h ../EventloopThread.h ../EventloopThread.cpp ../EventloopThreadPool.h ../EventloopThreadPool.cpp EventloopThreadPool_test.cpp ../../Eventloop.h ../../Eventloop.cpp ../../Channel.h ../../Channel.cpp
	g++ -g -o EventloopThreadPool_test ../CThread.cpp ../EventloopThread.cpp ../EventloopThreadPool.cpp EventloopThreadPool_test.cpp ../../Eventloop.cpp ../../Channel.cpp -I../ -I../../ -pthread

clean:
	rm -r CThread_test CThreadPool_test EventloopThread_test EventloopThreadPool_test
