/* File testApp.cpp
 * Test the BurstTrie class */

#include "record.h"
#include "BurstTrie.h"
#include <fstream>

bool openInFile(const std::string &filename, std::ifstream &file){
  file.open(filename.c_str(),std::ifstream::in);
  if(!file.is_open()) {
    printf("Could not open input file %s", filename.c_str());
    return false;
  }
  return true;
}

int main(int argc, char* argv[]){
  BurstTrie bt;
  std::string fileName="eng_com.dic";
  std::ifstream dictFile;
  if(openInFile(fileName,dictFile)){
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
    if(openInFile(fileName,dictFile)){
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
    }
  }
  return 0;
}
