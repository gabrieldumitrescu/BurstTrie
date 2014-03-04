/* File BurstTrie.cpp
 * My C++ implementatio of a burst trie */

#include <stdio.h>
#include <list>
#include <string>

#define ALPHABET_SIZE (('z'-'a'+1)+1) // letters a throuh z plus space

class Record{
public:
  explicit Record(const std::string& s=""):data(s){}
private:
  std::string data;
};

class Node{
public:
  explicit Node(bool container=false)
    :isContainer(container){
    if(isContainer){
      records=new std::list<Record>;
      children=NULL;
    }
    else{
      records=NULL;
      children=new Node*[ALPHABET_SIZE];
    }
  }
  void addRecord(const Record& rec){
    records->push_back(rec);
  }
  ~Node(){
    if(isContainer) {
      records->clear();
      delete records;
    }
    else delete children;
  }
private:
  bool isContainer;
  Node** children;
  std::list<Record> *records;
  
};

class BurstTrie{
};

int main(int argc, char* argv[]){
}
