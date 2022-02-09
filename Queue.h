//
// Created by kevin on 9/27/2021.
//

#ifndef PROJECT_1_QUEUE_H
#define PROJECT_1_QUEUE_H

#include "Node.h"
template <typename Object>
class Queue {

private:
    // Initialize front and back pointers
    Node<Object> *front;
    Node<Object> *back;
public:
    // Queue constructor
    Queue(){
        front = nullptr;
        back = nullptr;
    }
    // Queue destructor
    ~Queue(){
        // This method destroys the stack and clears the memory
        while(front != nullptr && back != nullptr){
            pop();
        }
        cout << "No memory leaks :)" << endl;
    }
    // push a new item into the Queue
    void push(Object item){
        // create a new node on heap memory
        Node<Object>* newNode = new Node<Object>(item);
        if (front == nullptr && back == nullptr){
            front = back = newNode;
        } else {
            back->setNext(newNode);
            back = newNode;
        }
    }
    // remove the first time from the Queue
    Object pop(){
        if (front == nullptr){
            return Object();
        }

        Node<Object>* temp = front;
        Object returnVal = front->getItem();
        front = front->getNext();
        delete temp;
        return returnVal;
    }
    // search the Queue for an item
    bool search(Object item){
        Node<Object>* curr = front;
        while (curr != nullptr){
            if (item == curr->getItem()){
                return true;
            }
            curr = curr->getNext();
        }
        return false;
    }
    // print the entire Queue
    void printQueue(){
        cout << "--Front--" << endl;
        Node<Object> *curr = front;
        while(curr != nullptr){
            cout << curr->getItem() << endl;
            curr = curr->getNext();
        }
        cout << "--Back--" << endl;
    }

};

#endif //PROJECT_1_QUEUE_H
