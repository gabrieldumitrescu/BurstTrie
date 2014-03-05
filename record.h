/* File record.h 
 * The record class header */

#ifndef _RECORD_H_
#define _RECORD_H_

#include <string>
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE (('z'-'a'+1)+2) // letters a throuh z plus empty string plus "'" plus

/* Record class contains the target data
 * stored by the burst trie data structure */
class Record{
public:
  explicit Record(const std::string& s);

  static int getIndex(const Record& r);

  size_t length() const ;

  std::string getData() const ;

  Record subRecord(size_t start,size_t len=std::string::npos) const;
    
private:
  std::string data;
};

#endif // _RECORD_H_

