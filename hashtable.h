#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <unordered_map>
#include <iostream>
#include <string>
#include "queue.h"



class Node {
public:
	//each node contains, key(object), value(rec), and pointer to next.
    std::string object;
    std::string rec;
    Node* next;
    //constructor for node, key and value arguments and next pointer.
    Node(std::string object, std::string rec) : object(object), 
    rec(rec), next(nullptr) {}
};

class HashTable {
private:
	 //for 7 recommendations ideally spread evenly across the hashtbale
    static const int TABLE_SIZE = 7;
    Node* table[TABLE_SIZE];
    //computes hash code for object
    int hash(std::string key);
  //finds recocomendation based on objects hashcode
	std::string getReccomendation(std::string object);
    


public:
	//constructor for hashtable, each index intially set to nullptr
    HashTable();
     //destructor, deletes all nodes 
    ~HashTable();
    //adds to hashtable, seperate chaining 
     void add(std::string obj, std::string rec);
  //call to getReccomendation
	std::string recommend(std::string object);
};

#endif
