#include "queue.h"
//constructor, front and rear set to null
	Queue::Queue() {
        front = NULL;
        rear = NULL;
    }

  
    void Queue::push(std::string data) {
    Nodeq* newNode = new Nodeq(); // create a new node
    newNode->data = data; // set the data of the new node
    newNode->next = nullptr; // set the next pointer to null

    if (rear == nullptr) { // if the queue is empty
        front = newNode; // set the front and rear pointers to the new node
        rear = newNode;
    }
    else { // if the queue is not empty
        rear->next = newNode; // add the new node to the end of the queue
        rear = newNode; // update the rear pointer
    }
}

    void Queue::pop() {
    if (front == nullptr) { // if the queue is empty
        std::cout << "Queue is empty" << std::endl; // output an error message
        return;
    }
    Nodeq* temp = front; // save the current front node
    front = front->next; // update the front pointer to the next node
    if (front == nullptr) // if the queue is now empty
        rear = nullptr; // update the rear pointer to null
    delete (temp); // delete the saved front node
}

   void Queue::display() {
    if (front == nullptr) { // if the queue is empty
        std::cout << "Queue is empty" << std::endl; // output an error message
        return;
    }
    Nodeq* temp = front; // start at the front of the queue
    while (temp != nullptr) { // loop through each node in the queue
        std::cout << temp->data << " "; // output the data of the current node
        temp = temp->next; // move to the next node
    }
    std::cout << std::endl; // output a newline at the end
}
    
    bool Queue::empty() 
    {
		return front == nullptr; // returns true if the queue is empty, false otherwise
	}
	
	std::string Queue::getFront() const
	{
			return front->data; // returns the data of the front node
	}
	
