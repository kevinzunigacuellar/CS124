#include "Stock.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "SplayTree.h"
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <random>


using namespace std;
int main() {
    /* Project 1: */

    // create a vector
    vector<Stock> stocks;

    // read data
    getDataFromCsv("../sp500-jan-2014.csv", stocks);

    // test: check getter and setters
    stockTests();

    // test: check size of vector
    assert(stocks.size() == 10143);

    // test : check calculation function
    assert(getTradingFeeForMaxVolume(stocks) == 3300059);

    /* Project 3: */

    /*
     * First BST:
     * Insert a sorted array from 1 to 100 into a binary tree and export the depths
     */

    BinarySearchTree<int> Bst;
    for (int i = 1; i <= 100; ++i) {
        Bst.add(i);
    };

    ofstream  f_out;
    f_out.open("FirstBST.csv");
    f_out << "depth" << "," << "value" << endl;
    for (int i = 1; i <= 100; ++i){
        int depth = 0;
        Bst.find(i,depth);
        f_out << depth << "," << i << endl;
    }
    f_out.close();

    /*
     * Second BST:
     * Insert an unsorted array from 1 to 100 into a binary tree and export the depths
     */

    // declare vector
    vector<int> arr;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    BinarySearchTree<int> SecondBST;

    // create an array
    for (int i = 1; i <= 100; i++) {
        arr.push_back(i);
    }
    // shuffle array items
    // https://www.cplusplus.com/reference/algorithm/shuffle/
    std::shuffle(arr.begin(), arr.end(),std::default_random_engine(seed));

    // push values to BST
    for (int i = 0; i < arr.size(); ++i){
        SecondBST.add(arr[i]);
    }

    // open a new file
    ofstream  file_out;
    file_out.open("SecondBST.csv");
    file_out << "depth" << "," << "value" << endl;
    // find values and push depth, value
    for (int i = 0; i < arr.size() ; ++i){
        int depth = 0;
        SecondBST.find(arr[i],depth);
        file_out << depth << "," << arr[i] << endl;
    }
    file_out.close();

    /*
     * Third BST:
     * Insert a vector<Stock> into a binary tree and export the depth and value.
     */

    BinarySearchTree<Stock> StockBST;
    for (int i = 0; i < stocks.size(); ++i) {
        StockBST.add(stocks[i]);
    };

    ofstream  file;
    file.open("StockBST.csv");
    file << "value" << "," << "depth" << endl;
    for (int i = 0; i < stocks.size(); ++i){
        int depth = 0;
        StockBST.find(stocks[i],depth);
        file << stocks[i].getId() << "," << depth << endl;
    }
    file.close();

    /*
     * First AVL Tree:
     * Insert a sorted array from 1 to 100 into an AVL tree and export the depths
     */

    AVLTree<int> FirstAVL;

    for (int i = 1; i <= 100; ++i) {
        FirstAVL.add(i);
    };

    ofstream  f_out_FirstAVL;
    f_out_FirstAVL.open("FirstAVL.csv");
    f_out_FirstAVL << "value" << "," << "depth" << endl;
    for (int i = 1; i <= 100; ++i){
        int depth = 0;
        FirstAVL.find(i,depth);
        f_out_FirstAVL << i << "," << depth << endl;
    }
    f_out_FirstAVL.close();

    /*
     * Second AVL:
     * Insert an unsorted array from 1 to 100 into an AVL Tree and export the depths
     */

    // declare variables
    vector<int> arr_AVL;
    unsigned seed_AVL = std::chrono::system_clock::now().time_since_epoch().count();
    AVLTree<int> SecondAVL;

    // create an array [1,..., 100]
    for (int i = 1; i <= 100; i++) {
        arr_AVL.push_back(i);
    }
    /* shuffle array items
       https://www.cplusplus.com/reference/algorithm/shuffle/
       [ 5,...,22]
    */
    std::shuffle(arr_AVL.begin(), arr_AVL.end(),std::default_random_engine(seed_AVL));

    // push values to AVL Tree
    for (int i = 0; i < arr_AVL.size(); ++i){
        SecondAVL.add(arr_AVL[i]);
    }

    // open a new file
    ofstream  f_out_SecondAVL;
    f_out_SecondAVL.open("SecondAVL.csv");
    f_out_SecondAVL << "value" << "," << "depth" << endl;
    // find values and push depth, value
    for (int i = 0; i < arr_AVL.size() ; ++i){
        int depth = 0;
        SecondAVL.find(arr_AVL[i],depth);
        f_out_SecondAVL << arr_AVL[i] << "," << depth << endl;
    }
    f_out_SecondAVL.close();

    /*
     * Third AVL:
     * Insert a vector<Stock> into an AVL Tree and export the depth and value.
     */

    AVLTree<Stock> StockAVL;
    for (int i = 0; i < stocks.size(); ++i) {
        StockAVL.add(stocks[i]);
    };

    ofstream  f_out_StockAVL;
    f_out_StockAVL.open("StockAVL.csv");
    f_out_StockAVL << "value" << "," << "depth" << endl;
    for (int i = 0; i < stocks.size(); ++i){
        int depth = 0;
        StockAVL.find(stocks[i],depth);
        f_out_StockAVL << stocks[i].getId() << "," << depth << endl;
    }
    f_out_StockAVL.close();

    /*
     * First Splay Tree:
     * Insert a sorted array from 1 to 100 into a splay tree and export the value and depths.
     */

    SplayTree<int> FirstSplay;

    for (int i = 1; i <= 100; ++i) {
        FirstSplay.add(i);
    };

    ofstream  f_out_FirstSplay;
    f_out_FirstSplay.open("FirstSplay.csv");
    f_out_FirstSplay << "value" << "," << "depth" << endl;
    for (int i = 1; i <= 100; ++i){
        int depth = 0;
        FirstSplay.find(i,depth);
        f_out_FirstSplay << i << "," << depth << endl;
    }
    f_out_FirstSplay.close();

    /*
     * Second Splay:
     * Insert an unsorted array from 1 to 100 into a Splay Tree and export the depths
     */

    // declare variables
    vector<int> arr_Splay;
    unsigned seed_Splay = std::chrono::system_clock::now().time_since_epoch().count();
    SplayTree<int> SecondSplay;

    // create an array [1,..., 100]
    for (int i = 1; i <= 100; i++) {
        arr_Splay.push_back(i);
    }
    /* shuffle array items
       https://www.cplusplus.com/reference/algorithm/shuffle/
    */
    std::shuffle(arr_Splay.begin(), arr_Splay.end(),std::default_random_engine(seed_Splay));

    // push values to AVL Tree
    for (int i = 0; i < arr_Splay.size(); ++i){
        SecondSplay.add(arr_Splay[i]);
    }

    // open a new file
    ofstream  f_out_SecondSplay;
    f_out_SecondSplay.open("SecondSplay.csv");
    f_out_SecondSplay << "value" << "," << "depth" << endl;
    // find values and push depth, value
    for (int i = 0; i < arr_Splay.size() ; ++i){
        int depth = 0;
        SecondSplay.find(arr_Splay[i],depth);
        f_out_SecondSplay << arr_Splay[i] << "," << depth << endl;
    }
    f_out_SecondSplay.close();

    /*
     * Third Splay - Part 1:
     * Insert a vector<Stock> into a Splay Tree and find each node in the order that were added.
     */

    SplayTree<Stock> StockSplay_1;
    for (int i = 0; i < stocks.size(); ++i) {
        StockSplay_1.add(stocks[i]);
    };

    ofstream  f_out_StockSplay_1;
    f_out_StockSplay_1.open("StockSplay_1.csv");
    f_out_StockSplay_1 << "value" << "," << "depth" << endl;
    for (int i = 0; i < stocks.size(); ++i){
        int depth = 0;
        StockSplay_1.find(stocks[i],depth);
        f_out_StockSplay_1 << stocks[i].getId() << "," << depth << endl;
    }
    f_out_StockSplay_1.close();

    /*
     * Third Splay - Part 2:
     * Insert a vector<Stock> into a Splay Tree and find each node in random order.
     */

    SplayTree<Stock> StockSplay_2;

    // create an array [1,..., stocks.size()]
    vector<int> rand_arr_stock;
    for (int i = 0; i < stocks.size(); i++) {
        rand_arr_stock.push_back(i);
    }

    // shuffle array
    unsigned seed_Splay_2 = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(rand_arr_stock.begin(), rand_arr_stock.end(),std::default_random_engine(seed_Splay_2));


    // add stock vector into Splay
    for (int i = 0; i < stocks.size(); ++i) {
        StockSplay_2.add(stocks[i]);
    };

    // open file
    ofstream  f_out_StockSplay_2;
    f_out_StockSplay_2.open("StockSplay_2.csv");

    // labels
    f_out_StockSplay_2 << "value" << "," << "depth" << endl;

    // loop all elements ~10k
    for (int i = 0; i < rand_arr_stock.size(); ++i){
        // find 5 times
        for (int j = 0; j < 5; ++j) {
            int depth = 0;
            StockSplay_2.find(stocks[rand_arr_stock[i]],depth);
            // get random stock ID - depth
            f_out_StockSplay_2 << stocks[rand_arr_stock[i]].getId() << "," << depth << endl;
        }
    }
    f_out_StockSplay_2.close();

    return 0;
}
