#include "Stock.h"
#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;
int main() {

    // create a vector
    vector<Stock> stocks;

    // read data
    getDataFromCsv("../sp500-jan-2014.csv", stocks);

    // print data
    for (int i = 0; i < stocks.size(); ++i){
        cout << stocks[i] << endl;
    }

    // perform calculation
    cout << getTradingFeeForMaxVolume(stocks) << " " << stocks.size();

    // test: check getter and setters
    stockTests();

    // test: check size of vector
    assert(stocks.size() == 10143);

    // test : check calculation function
    assert(getTradingFeeForMaxVolume(stocks) ==3300059);

    return 0;
}
