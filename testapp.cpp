/* File testApp.cpp
 * Test the BurstTrie class */

#include "record.h"
#include "BurstTrie.h"
#include <fstream>
#include <unordered_map>

bool openInFile(const std::string &filename, std::ifstream &file){
  file.open(filename.c_str(),std::ifstream::in);
  if(!file.is_open()) {
    printf("Could not open input file %s", filename.c_str());
    return false;
  }
  return true;
}

void testBurstTrie(const std::string& dictFileName, const std::string &searchFileName){
  BurstTrie bt;
  std::ifstream dictFile;
  if(openInFile(dictFileName,dictFile)){
    int lineNo=0;
    std::string line;
    while(getline(dictFile,line)){
      lineNo++;
      //printf("Adding line no %d\n",lineNo);
      bt.addRecord(Record(line));
    }
    printf("Added %d lines\n",lineNo);
    dictFile.close();
    if(openInFile(searchFileName,dictFile)){
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
}

void testHashMap(const std::string& dictFileName, const std::string &searchFileName){
  std::unordered_map<std::string,std::string> map;
  std::ifstream dictFile;
  if(openInFile(dictFileName,dictFile)){
    int lineNo=0;
    std::string line;
    while(getline(dictFile,line)){
      lineNo++;
      //printf("Adding line no %d\n",lineNo);
      std::pair<std::string,std::string> record (line,line);
      map.insert(record);
    }
    printf("Added %d lines\n",lineNo);
    dictFile.close();
    if(openInFile(searchFileName,dictFile)){
      int found=0;
      int notFound=0;
      while(getline(dictFile,line)){
	if(map.find(line)==map.end())
	  //printf("Found record %s\n",line.c_str());
	  notFound++;
	else
	  found++;
	//printf("Record %s not found\n",line.c_str());
      }
      printf("Found %d records not found %d records.\n",found,notFound);
      dictFile.close();
    }
  }
}


int main(int argc, char* argv[]){
  std::string dictFileName="eng_com.dic";
  std::string srchFileName="toSearch.dic";
  //testBurstTrie(dictFileName,srchFileName);
  testHashMap(dictFileName,srchFileName);

  return 0;
}
