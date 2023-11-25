#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>

class Nodeq {
public:
  //nodes of queue contain data and next pointer
    std::string data;
    Nodeq* next;
};

class Queue {
private:
    //front and rear of queue
    Nodeq* front;
    Nodeq* rear;
public:
    //constructor, sets front and rear to null
    Queue();
   
    /*Adds a new element to the back of the queue. Otherwise, it adds the new node to the end of the queue and updates the rear pointer to point to the new node
    */
	  void push(std::string data);

     /*removes the element at the front of the queue.
    */
    void pop();

    //displays data of each node in queue, only for testing
    void display();

    //if queue is empty return true, else return false
    bool empty();

  //returns data of front of queue 
    std::string getFront() const;	
};


#endif
