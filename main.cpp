#include "Stock.h"
#include <cmath>
#include <iostream>
#include <vector>

#include <algorithm>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

template<typename Comparable>
void printVec(const vector<Comparable> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i != 0) {
            cout << ", ";
        }
        cout << v[i];
    }
    cout << endl;
}

// Helper function for heapSort
inline int leftChild(int i) {
    return 2 * i + 1;
}

// Helper function for heapSort
// i is the index of the value being percolated down
// n is the number of items in the heap
template <typename Comparable>
void percolateDown(vector<Comparable> &items, int i, int n, int child, Comparable tmp, int &numReads, int &numWrites) {
    for(tmp = items[i]; leftChild(i) < n; i = child) {
        numReads +=1;
        numWrites +=1;
        child = leftChild(i);
        // choose the child with the larger value
        if (child != n - 1 && items[child] < items[child + 1]) {
            numReads += 2;
            ++child;
        }
        // if the parent is less than the child, swap them
        if (tmp < items[child]) {
            numReads += 2;
            items[i] = items[child];
            numReads += 1;
            numWrites += 1;
        } else {
            // parent is >= both children. nothing more to do.
            break;
        }
    }
    items[i] = tmp;
    numReads += 1;
    numWrites += 1;
}

template <typename Comparable>
vector<Comparable> heapSort(vector<Comparable> items,int &numReads,int &numWrites) {
    int i = 0, j = 0, child = 0;
    Comparable temp = Comparable(), tmp = Comparable();
    // build the heap (with max value at root)
    for (i = items.size() / 2 - 1; i >= 0; --i) {
        percolateDown(items, i, items.size(), child, tmp, numReads, numWrites);
    }
    // keep deleting the max
    for (j = items.size() - 1; j > 0; --j) {
        // swap the maximum out
        temp = items[0];
        numReads += 1;
        numWrites += 1;
        items[0] = items[j];
        numReads += 1;
        numWrites += 1;
        items[j] = temp;
        numWrites += 1;
        numReads += 1;

        // make it into a heap again
        percolateDown(items, 0, j, child, tmp, numReads, numWrites);

    }
    return items;
}

template<typename Comparable>
void bubbleSort(vector<Comparable> vec, int &numReads, int &numWrites) {
    bool haveSwapped = true;
    int maxIndex = vec.size(), i;
    Comparable temp;
    while (haveSwapped) {
        haveSwapped = false;
        for (i = 0; i + 1 < maxIndex; ++i) {
            // Compare items at indices i and i+1 and swap if necessary
            if (vec[i] > vec[i+1]) {
                numReads += 2;
                temp = vec[i];
                numReads += 1;
                numWrites += 1;
                vec[i] = vec[i+1];
                numReads += 1;
                numWrites += 1;
                vec[i+1] = temp;
                numWrites += 1;
                numReads += 1;

                // Update haveSwapped
                haveSwapped = true;
            }
        }
        // Update maxIndex
        --maxIndex;
    }
}

template<typename Comparable>
void selectionSort(vector<Comparable> vec, int &numReads, int &numWrites) {
    int swapIndex, i, minIndex;
    Comparable temp;
    for (swapIndex = 0; swapIndex < vec.size(); ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        for (i = swapIndex + 1; i < vec.size(); ++i) {
            if (vec[i] < vec[minIndex]) {
                numReads += 2;
                minIndex = i;
            }
        }
        // Swap min value into swapIndex spot in vector
        temp = vec[swapIndex];
        numReads += 1;
        numWrites += 1;
        vec[swapIndex] = vec[minIndex];
        numReads += 1;
        numWrites += 1;
        vec[minIndex] = temp;
        numWrites += 1;
        numReads += 1;
    }
}

template<typename Comparable>
void insertionSort(vector<Comparable> vec) {
    int unsortedStartIndex, insertIndex;
    Comparable toBeInserted;
    for (unsortedStartIndex = 1; unsortedStartIndex < vec.size(); ++unsortedStartIndex) {
        toBeInserted = vec[unsortedStartIndex];
        // Loop to shift over the larger elements
        insertIndex = unsortedStartIndex - 1;
        while (insertIndex >= 0 && vec[insertIndex] > toBeInserted) {
            vec[insertIndex + 1] = vec[insertIndex];
            --insertIndex;
        }
        // Put toBeInserted back into vec
        vec[insertIndex + 1] = toBeInserted;
    }
}

template<typename Comparable>
void mergeSortRec(vector<Comparable> &vec, int startIndex, int endIndex,int &numReads,int &numWrites) {

    // Recursive base case
    if (endIndex == startIndex) {
        // We are down to a single item. Nothing to split or merge.
        return;
    }

    // Recursive calls
    int centerIndex = (startIndex + endIndex) / 2;
    mergeSortRec(vec, startIndex, centerIndex, numReads, numWrites);
    mergeSortRec(vec, centerIndex + 1, endIndex, numReads, numWrites);

    // Merge
    vector<Comparable> temp;
    int leftIndex = startIndex;
    int rightIndex = centerIndex + 1;
    while (leftIndex <= centerIndex && rightIndex <= endIndex) {
        if (vec[leftIndex] <= vec[rightIndex]) {
            numReads += 2;
            temp.push_back(vec[leftIndex]);
            numReads += 1;
            numWrites += 1;
            ++leftIndex;
        } else {
            temp.push_back(vec[rightIndex]);
            numReads += 1;
            numWrites += 1;
            ++rightIndex;
        }
    }
    // At this point in the code, one half has been fully copied into temp
    // and the other half has at least one item left to copy. We don't know which half,
    // so we loop through both
    while (leftIndex <= centerIndex) {
        temp.push_back(vec[leftIndex]);
        numReads += 1;
        numWrites += 1;
        ++leftIndex;
    }
    while (rightIndex <= endIndex) {
        temp.push_back(vec[rightIndex]);
        numReads += 1;
        numWrites += 1;
        ++rightIndex;
    }
    // At this point in the code, all of the items have been copied into temp in order
    // Copy everything from temp back into vec
    for (int i = 0; i < temp.size(); ++i) {
        vec[i + startIndex] = temp[i];
        numReads += 1;
        numWrites += 1;
    }
}

template<typename Comparable>
void mergeSort(vector<Comparable> vec,int &numReads,int &numWrites) {
    mergeSortRec(vec, 0, vec.size() - 1, numReads, numWrites);
}

template<typename Comparable>
void quickSortUnstableRec(vector<Comparable> &vec, int startIndex, int endIndex) {
    if (endIndex <= startIndex) {
        // There is only one element left. Nothing to do.
        return;
    }
    Comparable partition = vec[startIndex];
    Comparable temp;
    int i;
    int largerElementIndex = startIndex + 1;
    for (i = startIndex; i <= endIndex; ++i) {
        if (vec[i] < partition) {
            // Swap the element with the one at largerElementIndex to keep smaller elements grouped
            temp = vec[i];
            vec[i] = vec[largerElementIndex];
            vec[largerElementIndex] = temp;
            // Update largerElementIndex
            ++largerElementIndex;
        }
    }
    vec[startIndex] = vec[largerElementIndex - 1];
    vec[largerElementIndex - 1] = partition;

    // Recursive call for less-than-partition side
    quickSortUnstableRec(vec, startIndex, largerElementIndex - 2);
    // Recursive call for greater-than-or-equal-to-partition side
    quickSortUnstableRec(vec, largerElementIndex, endIndex);
}

template<typename Comparable>
void quickSortUnstable(vector<Comparable> vec) {
    quickSortUnstableRec(vec, 0, vec.size() - 1);
}

template<typename Comparable>
void quickSortStableRec(vector<Comparable> &vec) {
    // Recursive base case
    if (vec.size() <= 1) {
        // There is nothing to sort
        return;
    }
    // Choose a partition element
    Comparable partition = vec[0];
    vector<Comparable> smaller, equal, larger;
    // Loop through vec and populate smaller, equal, larger
    int i;
    for (i = 0; i < vec.size(); ++i) {
        if (vec[i] < partition) {
            smaller.push_back(vec[i]);
        } else if (vec[i] == partition) {
            equal.push_back(vec[i]);
        } else {
            larger.push_back(vec[i]);
        }
    }
    // Recursive calls
    quickSortStableRec(smaller);
    quickSortStableRec(larger);
    // Copy from the three vectors back into vec
    for (i = 0; i < vec.size(); ++i) {
        if (i < smaller.size()) {
            vec[i] = smaller[i];
        } else if (i < smaller.size() + equal.size()) {
            vec[i] = equal[i - smaller.size()];
        } else {
            vec[i] = larger[i - smaller.size() - equal.size()];
        }
    }
}

template<typename Comparable>
void quickSortStable(vector<Comparable> vec) {
    quickSortStableRec(vec);
}

// Note: Not a template function
void radixSort(vector<int> vec, int numDigits) {
    int iteration, i, digit, bucket, item;
    vector<vector<int>> buckets(10);
    for (iteration = 0; iteration < numDigits; ++iteration) {
        // Copy everything from vec into buckets
        for (i = 0; i < vec.size(); ++i) {
            digit = (vec[i] / int(pow(10, iteration)) % 10);
            buckets[digit].push_back(vec[i]);
        }
        // Copy everything from buckets back into vec
        i = 0;
        for (bucket = 0; bucket < buckets.size(); ++bucket) {
            for (item = 0; item < buckets[bucket].size(); ++item) {
                vec[i] = buckets[bucket][item];
                ++i;
            }
            buckets[bucket].clear();
        }
    }
}
template<typename Comparable>
vector<Comparable> selectionSortReturnsVector(vector<Comparable> vec, int &numReads, int &numWrites) {
    int swapIndex, i, minIndex;
    Comparable temp;
    for (swapIndex = 0; swapIndex < vec.size(); ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        for (i = swapIndex + 1; i < vec.size(); ++i) {
            if (vec[i] < vec[minIndex]) {
                numReads += 2;
                minIndex = i;
            }
        }
        // Swap min value into swapIndex spot in vector
        temp = vec[swapIndex];
        numReads += 1;
        numWrites += 1;
        vec[swapIndex] = vec[minIndex];
        numReads += 1;
        numWrites += 1;
        vec[minIndex] = temp;
        numWrites += 1;
        numReads += 1;
    }
    return vec;
}


void bubbleSortByClosePrice(vector<Stock> vec, int &numReads, int &numWrites) {
    bool haveSwapped = true;
    int maxIndex = vec.size(), i;
    Stock temp;
    while (haveSwapped) {
        haveSwapped = false;
        for (i = 0; i + 1 < maxIndex; ++i) {
            // Compare items at indices i and i+1 and swap if necessary
            if (vec[i].getClose() > vec[i+1].getClose()) {
                numReads += 2;
                temp = vec[i];
                numReads += 1;
                numWrites += 1;
                vec[i] = vec[i+1];
                numReads += 1;
                numWrites += 1;
                vec[i+1] = temp;
                numWrites += 1;
                numReads += 1;

                // Update haveSwapped
                haveSwapped = true;
            }
        }

        // Update maxIndex
        --maxIndex;
    }
}


void twoSort(vector<Stock> vec, int &numReads, int &numWrites){
    vector<Stock> sortedVector = selectionSortReturnsVector(vec,numReads, numWrites);
    bubbleSortByClosePrice(sortedVector, numReads, numWrites);
}

vector<Stock> vectorResize(int num, vector<Stock> &stocks){
    vector<Stock> arr;
    int i;
    for(i=0; i < num; ++i){
        arr.push_back(stocks[i]);
    }

    return arr;
}


int main() {

    // create a vector
    vector<Stock> stocks;

    // read data
    getDataFromCsv("../sp500-jan-2014.csv", stocks);

    // test: check getter and setters
    stockTests();

    // test: check size of vector
    assert(stocks.size() == 10143);

    // randomize stock vector items
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(stocks.begin(), stocks.end(),std::default_random_engine(seed));

    // write to csv - bubble sort
    ofstream  f_out;
    f_out.open("bubbleSort.csv");
    f_out << "size" << "," << "reads" << "," << "writes" << endl;
    for(int i = 100; i <= 1000; i += 100){
        int numReads = 0, numWrites = 0;
        vector<Stock> stock_vector = vectorResize(i, stocks);
        bubbleSort(stock_vector, numReads, numWrites);
        f_out << stock_vector.size() << "," << numReads << "," << numWrites << endl;
    }
    f_out.close();

    // write to csv - selection sort
    f_out.open("selectionSort.csv");
    f_out << "size" << "," << "reads" << "," << "writes" << endl;
    for(int i = 100; i <= 1000; i += 100){
        int numReads = 0, numWrites = 0;
        vector<Stock> stock_vector = vectorResize(i, stocks);
        selectionSort(stock_vector, numReads, numWrites);
        f_out << stock_vector.size() << "," << numReads << "," << numWrites << endl;
    }
    f_out.close();

    // write to csv - merge sort
    f_out.open("mergeSort.csv");
    f_out << "size" << "," << "reads" << "," << "writes" << endl;
    for(int i = 100; i <= 1000; i += 100){
        int numReads = 0, numWrites = 0;
        vector<Stock> stock_vector = vectorResize(i, stocks);
        mergeSort(stock_vector, numReads, numWrites);
        f_out << stock_vector.size() << "," << numReads << "," << numWrites << endl;
    }
    f_out.close();

    // write to csv - heap sort
    f_out.open("heapSort.csv");
    f_out << "size" << "," << "reads" << "," << "writes" << endl;
    for(int i = 100; i <= 1000; i += 100){
        int numReads = 0, numWrites = 0;
        vector<Stock> stock_vector = vectorResize(i, stocks);
        heapSort(stock_vector, numReads, numWrites);
        f_out << stock_vector.size() << "," << numReads << "," << numWrites << endl;
    }
    f_out.close();

    // write to csv - two sort - selection and bubble sort
    f_out.open("twoSort.csv");
    f_out << "size" << "," << "reads" << "," << "writes" << endl;
    for(int i = 100; i <= 1000; i += 100){
        int numReads = 0, numWrites = 0;
        vector<Stock> stock_vector = vectorResize(i, stocks);
        twoSort(stock_vector, numReads, numWrites);
        f_out << stock_vector.size() << "," << numReads << "," << numWrites << endl;
    }
    f_out.close();

    /*
     * Extra credit:
     * Performing the same experiment, except double the size of the data set each time
     */


    f_out.open("bubbleSortExponentialGrowth.csv");
    f_out << "size" << "," << "reads" << "," << "writes" << endl;
    for(int i = 10; i < 6000; i *= 2){
        int numReads = 0, numWrites = 0;
        vector<Stock> stock_vector = vectorResize(i, stocks);
        bubbleSort(stock_vector, numReads, numWrites);
        f_out << stock_vector.size() << "," << numReads << "," << numWrites << endl;
    }
    f_out.close();

    // write to csv - selection sort
    f_out.open("selectionSortExponentialGrowth.csv");
    f_out << "size" << "," << "reads" << "," << "writes" << endl;
    for(int i = 10; i < 6000; i *= 2){
        int numReads = 0, numWrites = 0;
        vector<Stock> stock_vector = vectorResize(i, stocks);
        selectionSort(stock_vector, numReads, numWrites);
        f_out << stock_vector.size() << "," << numReads << "," << numWrites << endl;
    }
    f_out.close();

    // write to csv - merge sort
    f_out.open("mergeSortExponentialGrowth.csv");
    f_out << "size" << "," << "reads" << "," << "writes" << endl;
    for(int i = 10; i < 6000; i *= 2){
        int numReads = 0, numWrites = 0;
        vector<Stock> stock_vector = vectorResize(i, stocks);
        mergeSort(stock_vector, numReads, numWrites);
        f_out << stock_vector.size() << "," << numReads << "," << numWrites << endl;
    }
    f_out.close();

    // write to csv - heap sort
    f_out.open("heapSortExponentialGrowth.csv");
    f_out << "size" << "," << "reads" << "," << "writes" << endl;
    for(int i = 10; i < 6000; i *= 2){
        int numReads = 0, numWrites = 0;
        vector<Stock> stock_vector = vectorResize(i, stocks);
        heapSort(stock_vector, numReads, numWrites);
        f_out << stock_vector.size() << "," << numReads << "," << numWrites << endl;
    }
    f_out.close();

    // write to csv - two sort - selection and bubble sort
    f_out.open("twoSortExponentialGrowth.csv");
    f_out << "size" << "," << "reads" << "," << "writes" << endl;
    for(int i = 10; i < 6000; i *= 2){
        int numReads = 0, numWrites = 0;
        vector<Stock> stock_vector = vectorResize(i, stocks);
        twoSort(stock_vector, numReads, numWrites);
        f_out << stock_vector.size() << "," << numReads << "," << numWrites << endl;
    }
    f_out.close();


//    heapSort(numbers, numReads, numWrites);
//    bubbleSort(numbers, numReads, numWrites);
//    selectionSort(numbers, numReads, numWrites);
//    insertionSort(numbers);
//    mergeSort(numbers, numReads, numWrites);
//    quickSortStable(numbers);
//    quickSortUnstable(numbers);
//    radixSort(numbers, 2);
//    twoSort(stocks_100,numReads, numWrites);
//    cout << numReads << "," << numWrites << endl;
    return 0;
}
