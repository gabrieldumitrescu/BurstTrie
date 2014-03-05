/* File BurstTrie.cpp
 * My C++ implementatio of a burst trie */

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <string>

#define ALPHABET_SIZE (('z'-'a'+1)+2) // letters a throuh z plus empty string plus "'" plus

/* Record class contains the target data
 * stored by the burst trie data structure */
class Record{
public:
  explicit Record(const std::string& s=""):data(s){}
  static int getIndex(const Record& r){
    int index;
    if(r.getData()[0]=='\0')
      index=0;
    else if(r.getData()[0]=='\'')
      index=1;
    else index= r.getData()[0]-'a'+2;
    if(index<0 || index >=ALPHABET_SIZE) {
      printf("Error: unknown character \"\%s\" in string.\n",r.getData().c_str());
      exit(1); // error unknown character in string
    }
    return index;
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
#define CONTAINER_LIMIT 10

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

  /* Split a record in two parts.The first letter
   * will be used to index into the children array of pointers
   * and the rest of the Record will be added to the corresponding
   * child.
   * If the record has a length of 0 it will be inserted under the 
   * first index (for the empty string).
   * If the length is 1 it will be inserted under that letter and the 
   * child container will add an empty string.
   * If under the index there's no container/node a new one
   * is created.
   */
  void splitRecord(const Record& rec){
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
  
  void addRecord(const Record& rec){
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
  
  bool findRecord(const Record& rec) const{
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

  ~Node(){
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
  bool findRecord(const Record& rec) const{
    return root->findRecord(rec);
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
  std::string fileName="eng_com.dic";
  std::ifstream dictFile(fileName.c_str(),std::ifstream::in);
  if(!dictFile.is_open()) {
    printf("Could not open input file %s", fileName.c_str());
    return 1;
  }

  int lineNo=0;
  std::string line;
  while(getline(dictFile,line)){
    lineNo++;
    //printf("Adding line no %d\n",lineNo);
    bt.addRecord(Record(line));
  }
  printf("Added %d lines\n",lineNo);
  dictFile.close();
  fileName="toSearch.dic";
  dictFile.open(fileName.c_str(),std::ifstream::in);
  int found=0;
  int notFound=0;
  while(getline(dictFile,line)){
    if(bt.findRecord(Record(line)))
      //printf("Found record %s\n",line.c_str());
      found++;
    else
      notFound++;
    //printf("Record %s not found\n",line.c_str());
  }
  printf("Found %d records not found %d records.\n",found,notFound);
  dictFile.close();
  return 0;
}
