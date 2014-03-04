CXX=g++
CXXFLAGS=-g -Wall

APP=BurstTrie
SRC=BurstTrie.cpp

all:$(APP)

$(APP):$(SRC)
	$(CXX) $(CXXFLAGS) -o $(APP) $(SRC)

clean:
	rm -f $(APP)
