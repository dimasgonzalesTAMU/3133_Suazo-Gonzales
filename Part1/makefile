# makefile

all: dataserver client

reqchannel.o: reqchannel.h reqchannel.cpp
	g++ -std=c++0x -c -g reqchannel.cpp reqchannel.h

dataserver: dataserver.cpp reqchannel.o
	g++ -std=c++0x -o dataserver dataserver.cpp reqchannel.o -lpthread

client: client.cpp reqchannel.o
	g++ -std=c++0x -o client client.cpp reqchannel.o
