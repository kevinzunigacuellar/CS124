//
// Created by kevin on 11/8/2021.
//

#ifndef P4_STOCK_H
#define P4_STOCK_H


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <assert.h>

using std::string;
using std::vector;
using std::ifstream;
using std::ostream;
using std::setw;
using std::left;
using std::right;


class Stock {
private:
    double open, close, high, low;
    int volume, id;
    string symbol, date;
public:
    //Constructors:
    Stock(){
        id = open = close = high = low = volume = 0;
        symbol = "SYMB";
        date = "2014-01-01";
    }
    Stock(int id, string symbol, string date, double open, double high, double low, double close, int volume){
        this->id = id;
        this->symbol = symbol;
        this->date = date;
        this->open = open;
        this->high = high;
        this->low = low;
        this->close = close;
        this->volume = volume;
    }

    //Getters
    int getId(){
        return id;
    }

    string getSymbol(){
        return symbol;
    }

    string getDate(){
        return date;
    }

    double getOpen(){
        return open;
    }

    double getHigh(){
        return high;
    }

    double getLow(){
        return low;
    }

    double getClose(){
        return close;
    }

    int getVolume(){
        return volume;
    }

    // Setters
    void setId(int id){
        this->id = id;
    }

    void setSymbol(string symbol){
        this->symbol = symbol;
    }

    void setDate(string date){
        this->date = date;
    }

    void setOpen(double open){
        this->open = open;
    }

    void setHigh(double high){
        this->high = high;
    }
    void setLow(double low){
        this->low = low;
    }
    void setClose(double close){
        this->close = close;
    }

    void setVolume(int volume){
        this->volume = volume;
    }

    // overloaded operators
    friend ostream& operator << (ostream& outs, Stock stock) {
        outs << left << setw(8) << stock.id;
        outs << setw(4) << stock.symbol << right;
        outs << setw(12) << stock.date;
        outs << setw(10) << stock.open;
        outs << setw(10) << stock.high;
        outs << setw(10) << stock.low;
        outs << setw(10) << stock.close;
        outs << setw(10) << stock.volume;

        return outs;
    }

    friend bool operator == (const Stock &lhs, const Stock &rhs){
        return lhs.id == rhs.id;
    }


    friend bool operator < (const Stock &lhs, const Stock &rhs) {
        return lhs.id < rhs.id;
    }

    friend bool operator > (const Stock &lhs, const Stock &rhs){
        return lhs.id > rhs.id;
    }

    friend bool operator <= (const Stock &lhs, const Stock &rhs){
        return lhs.id <= rhs.id;
    }

    friend bool operator >= (const Stock &lhs, const Stock &rhs){
        return lhs.id >= rhs.id;
    }
};

void getDataFromCsv(string filename, vector<Stock> &Stocks) {
    // Set up fIn and read header
    ifstream fIn;
    fIn.open(filename);
    string headers;
    if (fIn) {
        getline(fIn, headers);
    }

    //define variables
    string symbol, date;
    int id, volume;
    float open,high,low,close;
    char comma;

    while (fIn && fIn.peek() != EOF) {

        //Read id
        fIn >> id;
        fIn >> comma;

        //Read symbol
        getline(fIn, symbol, ',');

        //Read date
        getline(fIn, date, ',');

        //Read open
        fIn >> open;
        fIn >> comma;

        //Read high
        fIn >> high;
        fIn >> comma;

        //Read low
        fIn >> low;
        fIn >> comma;

        //Read close
        fIn >> close;
        fIn >> comma;

        //Read volume
        fIn >> volume;

        // Create a Stock object and add to vector
        Stocks.push_back(Stock(id,symbol, date, open, high, low, close, volume));
    }
}

int getTradingFeeForMaxVolume(vector<Stock> &stocks){
    // initialize maximum volume
    int maxVolume = 1;

    // find maximum volume
    for (int i = 0; i < stocks.size() ; ++i) {
        if (stocks[i].getVolume() > maxVolume) {
            maxVolume = stocks[i].getVolume();
        }
    }
    // calculate the fee
    int tradingFee = maxVolume*0.01;
    return tradingFee;

}
// Testing
void stockTests(){
    // 1.1 testing demo :: Getter
    Stock testStockGetters = Stock(1, "TEST", "2021-09-13", 100.52, 101.89, 99.56, 101.02, 1210021);
    assert(testStockGetters.getId() == 1);
    assert(testStockGetters.getSymbol() == "TEST");
    assert(testStockGetters.getOpen() == 100.52);
    assert(testStockGetters.getHigh() == 101.89);
    assert(testStockGetters.getLow() == 99.56);
    assert(testStockGetters.getClose() == 101.02);
    assert(testStockGetters.getVolume() == 1210021);


    // 1.2 testing demo :: Setter
    Stock testStockSetters = Stock();
    testStockSetters.setId(10);
    assert (testStockSetters.getId() == 10);
    testStockSetters.setSymbol("TSLA");
    assert (testStockSetters.getSymbol() == "TSLA");
    testStockSetters.setDate("2021-09-14");
    assert (testStockSetters.getDate() == "2021-09-14");
    testStockSetters.setOpen(202.02);
    assert (testStockSetters.getOpen() == 202.02);
    testStockSetters.setHigh(204.69);
    assert (testStockSetters.getHigh() == 204.69);
    testStockSetters.setLow(201.43);
    assert (testStockSetters.getLow() == 201.43);
    testStockSetters.setClose(202.33);
    assert (testStockSetters.getClose() == 202.33);
    testStockSetters.setVolume(222333);
    assert (testStockSetters.getVolume() == 222333);

}

#endif //P4_STOCK_H
