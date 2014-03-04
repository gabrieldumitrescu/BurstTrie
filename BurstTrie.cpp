/* File BurstTrie.cpp
 * My C++ implementatio of a burst trie */

#include <stdio.h>
#include <list>
#include <string>

#define ALPHABET_SIZE (('z'-'a'+1)+1) // letters a throuh z plus space

/* Record class contains the target data
 * stored by the burst trie data structure */
class Record{
public:
  explicit Record(const std::string& s=""):data(s){}
  static int getIndex(const Record& r){
    if(r.getData()[0]=='\0')
      return 0;
    else return r.getData()[0]-'a'+1;
  }
  
  size_t length() const {return data.length();}
  std::string getData() const {return data;}

  Record subRecord(size_t start,size_t len=std::string::npos) const{
    return Record(data.substr(start,len));
  }
private:
  std::string data;
};

/* maximum number of records that will be stored in one container
 * When the size exceeds this value the container is burst 
 */
#define CONTAINER_LIMIT 100

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
    if(isContainer){
      records->push_back(rec);
      if(records->size()>CONTAINER_LIMIT)
	burstContainer();
    }
    else{
         // if we're at a node extract the first token of the record and add the rest of 
         // the record under the corresponding index
         // what if the string is empty -> add it under the blank
      switch(rec.length()){
      case 0:
	children[0]->addRecord(Record("\0"));
      break;
      case 1:
	children[Record::getIndex(rec.subRecord(0,1))]->addRecord(Record("\0"));
      break;
      default:
	children[Record::getIndex(rec.subRecord(0,1))]->addRecord(rec.subRecord(1));
      }
    }
  }

  /* When a specific condition is met for example the container size 
     exceeds a given value the container is transformed into a node 
     and the records contained are copied into it's children minus the 
     first character which is stored in the current node as the index
     into the children array */
  void burstContainer(){
    if(isContainer){
      children=new Node*[ALPHABET_SIZE];
      for (int i=0; i<ALPHABET_SIZE; ++i)
	children[i]=NULL;
      for(std::list<Record>::iterator it= records->begin(); it!=records->end(); ++it){
	int arrayIndex=Record::getIndex((*it).subRecord(0,1));
	children[arrayIndex]=new Node(true);
	children[arrayIndex]->addRecord((*it).subRecord(1));
      }
      records->clear();
      delete records;
      records=NULL;
      isContainer=false;
    }
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
public:
  BurstTrie(){
    root=new Node(true);
  }
  void addRecord(const Record& rec){
    root->addRecord(rec);
  }
  ~BurstTrie(){delete root;}
private:
  Node* root;
};

int main(int argc, char* argv[]){
  /*Record x("garbage");
  Record front("\0");
  printf("Alphabet size:%d\n",ALPHABET_SIZE);
  printf("Index of front:%d\n",Record::getIndex(front));
  printf("Size of \"\\0\" string is:%lu\n",std::string("\0").length());
  */
  BurstTrie bt;
  bt.addRecord(Record("garbage"));
}
