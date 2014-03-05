/* File BurstTrie.h
 * BurstTrie class header */

#ifndef _BURST_TRIE_H_
#define _BURST_TRIE_H_

#include "record.h"
#include <list>

/* maximum number of records that will be stored in one container
 * When the size exceeds this value the container is burst 
 */
#define CONTAINER_LIMIT 100

/* The Node class does all the work of the burst trie
 * It acts as a node by default but can also be a container
 * in which case it stores the records in a member list.
 * When it is only a node in the trie it stores an array of pointers
 * to the next node/container.The array has the same size as the size of 
 * the alphabet used and is indexed by the character at the corresponding 
 * position in the stored record as the depth of the node */
class Node{
public:
  /* By default create as a Node*/
  explicit Node(bool container=false);

  ~Node();

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
  void splitRecord(const Record& rec);
  
  void addRecord(const Record& rec);

  /* When a specific condition is met for example the container size 
     exceeds a given value the container is transformed into a node 
     and the records contained are copied into it's children minus the 
     first character which is stored in the current node as the index
     into the children array */
  void burstContainer();
  
  bool findRecord(const Record& rec) const;

private:
  bool isContainer;
  Node** children;
  std::list<Record> *records;
  
};

class BurstTrie{
public:
  BurstTrie();

  void addRecord(const Record& rec);

  bool findRecord(const Record& rec) const;

  ~BurstTrie();

private:
  Node* root;
};

#endif // _BURST_TRIE_H_
