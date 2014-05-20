CXX=g++
CXXFLAGS=-std=c++0x -g -Wall -O3

APP=testapp
SRC=testapp.cpp BurstTrie.cpp record.cpp
OBJS=$(SRC:.cpp=.o)
HEADERS=record.h BurstTrie.h

all:$(APP)

$(APP):$(HEADERS) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@  $(OBJS)

testapp.o:record.h BurstTrie.h testapp.cpp
BurstTrie.o:BurstTrie.h BurstTrie.cpp
record.o:record.h record.cpp

clean:
	rm -f $(APP) $(OBJS)
