
all: proctest

proctest: proctest.o
	g++ -g proctest.o -o proctest

proctest.o: proctest.cpp
	g++ -c proctest.cpp

clean:
	rm *o proctest
