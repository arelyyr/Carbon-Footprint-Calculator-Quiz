#include <iostream>
#include <string>
#include <unordered_map>
#include "hashtable.h"

	//takes in value and returns appropriate hashcode for hash table
    int HashTable::hash(std::string key) {
		int hash_value = 0;
		
		for (char c : key){
			hash_value += static_cast<int>(c);
			
		}
		//compression to provide an index
		return hash_value % TABLE_SIZE;
		  
    }

  //gets recommendation for object passed into function
	std::string HashTable::getReccomendation(std::string object) {

    //calculate index of the object
		int index = hash(object);
      //set current node to the node found at that index
        Node* currNode = table[index];
       
        while (currNode != nullptr && currNode->object != object) {
            currNode = currNode->next; /*iterate through linked list
            when value not found and not null pointer */
        }
        if (currNode != nullptr) {
			//if currNode->rec == code and not nullptr, rec is found
            return currNode->rec;
        }
        //otherwise, rec did not exist in hash table
        else {
            return " ";
        } 
    }
    



	//constructor for hashtable, each index intially set to nullptr
    HashTable::HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }
    
		//destructor, deletes all nodes 
      HashTable::~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
			//iterate through linked lists, delete nodes
            Node* currNode = table[i];
            while (currNode != nullptr) {
                Node* temp = currNode;
                currNode = currNode->next;
                delete temp;
            }
            //initial nodes in table set to nullptr
            table[i] = nullptr;
        }
    }

	/*adds to hashtable given hash code. If the same hash code for a 
	 * different object, it is added to the linked list bucket of that 
	 * index in the table
	 */
    void HashTable::add(std::string obj, std::string rec) {
		//calculate where new node should be inserted.
        int index = hash(obj);
        Node* newNode = new Node(obj, rec);
       
		//if index empty in hashtable, set head to new node
        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        //if not empty, add to end of linked list, handles collision.
        else {
            Node* currNode = table[index];
            while (currNode->next != nullptr) {
                currNode = currNode->next;
            }
            currNode->next = newNode;
        }
    }
	
	
    
//call to getReccomendation 
std::string HashTable::recommend(std::string object) {
    
    return getReccomendation(object);
}







