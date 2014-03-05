/* File testApp.cpp
 * Test the BurstTrie class */

#include "record.h"
#include "BurstTrie.h"
#include <fstream>

int main(int argc, char* argv[]){
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
