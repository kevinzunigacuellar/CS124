#include "Stock.h"
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include "Node.h"
#include "Stack.h"
#include "Queue.h"
using namespace std;
int main() {
    /* Project 1: */

    // create a vector
    vector<Stock> stocks;

    // read data
    getDataFromCsv("../sp500-jan-2014.csv", stocks);

    // print data
    for (int i = 0; i < 10; ++i){
        cout << stocks[i] << endl;
    }

    // test: check getter and setters
    stockTests();

    // test: check size of vector
    assert(stocks.size() == 10143);

    // test : check calculation function
    assert(getTradingFeeForMaxVolume(stocks) == 3300059);

    /* Project 2: */

    // Part 1 : Three Queues
    Queue<int> myIntQueue;
    Queue<string> myStringQueue;
    Queue<Stock> myStockQueue;

    // Int Queue
    myIntQueue.push(1);
    myIntQueue.push(2);
    myIntQueue.printQueue();
    myIntQueue.pop();
    myIntQueue.push(3);
    myIntQueue.printQueue();
    cout << "Is 2 in the Queue? "<< myIntQueue.search(2) << endl;

    // Stock Queue
    for (int i = 0; i < 5; ++i){
        myStockQueue.push(stocks[i]);
    }
    myStockQueue.printQueue();
    myStockQueue.pop();
    myStockQueue.printQueue();
    myStockQueue.push(stocks[9]);
    myStockQueue.printQueue();
    cout << "Is stock with id No. 4 in the queue? " <<myStockQueue.search(stocks[3]) << endl;

    // String Queue
    myStringQueue.push("Kevin");
    myStringQueue.push("Karla");
    myStringQueue.printQueue();
    myStringQueue.pop();
    myStringQueue.push("Lisa");
    myStringQueue.printQueue();
    cout << "Is Lisa in the Queue? " << myStringQueue.search("Lisa") << endl;

    // Part 2: One Stack and One Queue

    Stack<Stock> stockStack;
    Queue<Stock> stockQueue;

    for (int i = 0; i < 10; ++i){
        stockQueue.push(stocks[i]);
        stockQueue.printQueue();
    }
    for (int i = 0; i < 10; ++i){
        stockQueue.pop();
        stockQueue.printQueue();
    }

    for (int i = 0; i < 10; ++i){
        stockStack.push(stocks[i]);
        stockStack.printStack();
    }

    for (int i = 0; i < 10; ++i){
        stockStack.pop();
        stockStack.printStack();
    }

    return 0;
}
