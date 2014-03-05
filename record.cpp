/* File Record.cpp
 * Record class implementation */

#include "record.h"

Record::Record(const std::string& s="\0"):data(s){}


int Record::getIndex(const Record& r){
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

size_t Record::length() const {return data.length();}

std::string Record::getData() const {return data;}

Record Record::subRecord(size_t start,size_t len) const{
    return Record(data.substr(start,len));
}
