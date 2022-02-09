//
// Created by kevin on 9/27/2021.
//

#ifndef PROJECT_1_STACK_H
#define PROJECT_1_STACK_H

#include <iostream>
#include "Node.h"

using std::cout, std::endl;

template <typename Object>

class Stack {

private:
    // Node Pointer
    Node<Object> *top;
public:
    // Create a new Stack
    Stack(){
        top = nullptr;
    }

    ~Stack(){
        // This method destroys the stack and clears the memory
        while(top != nullptr){
            pop();
        }
        cout << "No memory leaks :)" << endl;
    }

    // push method to add
    void push(Object item){
        // create a new node in heap memory
        Node<Object>* newNode = new Node<Object>(item, top);
        // update the top pointer to point to newNode
        top = newNode;

    }
    // pop method to remove
    Object pop(){
        // check if the stack is not empty
        if (top == nullptr){
            return Object();
        }
        // make a copy of the top of the stack
        Node<Object>* topCopy = top;
        // create a variable for the item that top points to
        Object returnVal = top->getItem();
        // update top point to the next node
        top = top->getNext();
        // delete the copy of top
        delete topCopy;
        // return the popped item
        return returnVal;
    }

    // Search the stack for a given value
    bool search(Object item){
        Node<Object>* curr = top;
        while (curr != nullptr){
            if (item == curr->getItem()){
                return true;
            }
            curr = curr->getNext();
        }
        return false;
    }

    // peek method to return item at the top
    Object peek(){
        if (top != nullptr){
            return top->getItem();
        }
        return Object();
    }

    // print the all the items in the Stack
    void printStack(){
        cout << "Top" << endl;
        Node<Object> *curr = top;
        while(curr != nullptr){
            cout << curr->getItem() << endl;
            curr = curr->getNext();
        }
        cout << "Bottom" << endl;
    }
};


#endif //PROJECT_1_STACK_H
