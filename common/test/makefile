all: CThread_test
CThread_test: ../CThread.cpp ../CThread.h CThread_test.cpp
	g++ -g -o CThread_test CThread_test.cpp ../CThread.cpp -pthread

clean:
	rm -r CThread_test
