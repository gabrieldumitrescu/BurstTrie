CXX=g++
CXXFLAGS=-g -Wall

APP=BurstTrie
SRC=BurstTrie.cpp record.cpp
OBJS=$(SRC:.cpp=.o)
HEADERS=record.h

all:$(APP)

$(APP):$(HEADERS) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@  $(OBJS)

BurstTrie.o:BurstTrie.cpp
record.o:record.h record.cpp

clean:
	rm -f $(APP) $(OBJS)
