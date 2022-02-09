//
// Created by kevin on 9/27/2021.
//

#ifndef PROJECT_1_NODE_H
#define PROJECT_1_NODE_H

// define a template name
template<typename Object>

class Node {
private:
    Object item;
    Node* next;

public:
    // Node constructor
    Node(Object newItem){
        item = newItem;
        next = nullptr;
    }
    // Node constructor
    Node(Object newItem, Node* nextNode){
        item = newItem;
        next = nextNode;
    }
    // Set a value for item inside the Node
    void setItem (Object newItem) {
        item = newItem;
    }
    // Get item
    Object getItem(){
        return item;
    }
    // Set the Node next pointer
    void setNext(Node* nextNode){
        next = nextNode;
    }
    // Get the next Node pointer
    Node* getNext(){
        return next;
    }

};

#endif //PROJECT_1_NODE_H
