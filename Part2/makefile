
all: proctest

proctest: proctest.o
	g++ -std=c++11 -g -w proctest.o -o proctest

proctest.o: proctest.cpp
	g++ -std=c++11 -c -g -w proctest.cpp

clean:
	rm *o proctest
