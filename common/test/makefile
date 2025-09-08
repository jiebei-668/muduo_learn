all: CThread_test CThreadPool_test
CThread_test: ../CThread.cpp ../CThread.h CThread_test.cpp
	g++ -g -o CThread_test CThread_test.cpp ../CThread.cpp -pthread
CThreadPool_test: ../CThread.cpp ../CThread.h ../CThreadPool.h ../CThreadPool.cpp CThreadPool_test.cpp
	g++ -g -o CThreadPool_test CThreadPool_test.cpp ../CThread.cpp ../CThreadPool.cpp -I../ -pthread

clean:
	rm -r CThread_test CThreadPool_test
