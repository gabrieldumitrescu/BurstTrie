/* File BurstTrie.cpp
 * My C++ implementatio of a burst trie */

#include "BurstTrie.h"

Node::Node(bool container)
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

void Node::splitRecord(const Record& rec){
    int index=0;
    Record toInsertChild=Record("\0");
    if(rec.length()>=1){
      index=Record::getIndex(rec.subRecord(0,1));
      if(rec.length()>1)
	toInsertChild=rec.subRecord(1);
    }
    if(children[index]==NULL) 
      children[index]=new Node(true); // create a new container under the index
    children[index]->addRecord(toInsertChild);
}
  
void Node::addRecord(const Record& rec){
    //printf("Adding record \"%s\"\n",rec.getData().c_str());
    if(isContainer){
      records->push_back(rec);
      if(records->size()>CONTAINER_LIMIT)
	burstContainer();
    }
    else{
      splitRecord(rec);
    }
}

void Node::burstContainer(){
    if(isContainer){
      children=new Node*[ALPHABET_SIZE];
      for (int i=0; i<ALPHABET_SIZE; ++i)
	children[i]=NULL;
      //printf("Records size is %u\n",records->size());
      while(!records->empty()){
	//printf("Splitting record %s\n",records->front().getData().c_str());
	splitRecord(records->front());
	records->pop_front();
      }
      delete records;
      records=NULL;
      isContainer=false;
    }
  }
  
bool Node::findRecord(const Record& rec) const{
    if(isContainer){
      for (std::list<Record>::iterator it=records->begin();it!=records->end(); ++it){
	if(rec.getData()==(*it).getData()){
	    records->erase(it);// remove from the current list position
	    records->push_front(rec);// push at the front 
	    return true;
	}
      }
      return false; 
    }
    else{
      int childIndex=0;
      Record toFindChild=Record("\0");
      if(rec.length()>=1){
	childIndex=Record::getIndex(rec.subRecord(0,1));
	if(rec.length()>1)
	  toFindChild=rec.subRecord(1);
      }
      if(children[childIndex]==NULL) return false;
      else return children[childIndex]->findRecord(toFindChild);
    }
}

Node::~Node(){
    if(isContainer) {
      records->clear();
      delete records;
    }
    else {
      for(int i=0; i<ALPHABET_SIZE; ++i){
	if(children[i]!=NULL)
	  delete children[i];
      }
      delete[] children;
    }
}

BurstTrie::BurstTrie(){
    root=new Node(true);
}

void BurstTrie::addRecord(const Record& rec){
    root->addRecord(rec);
}

bool BurstTrie::findRecord(const Record& rec) const{
    return root->findRecord(rec);
}

BurstTrie::~BurstTrie(){delete root;}
