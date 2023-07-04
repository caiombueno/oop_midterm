#pragma once
#include <vector>
#include <string>
#include "Candlestick.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
using namespace std;

class CandlestickDataProcessor
{
public:
    // Get a list of Candlestick data based on data passed in constructor
    const vector<Candlestick> getList(string product, OrderBookType orderType);
    static vector<vector<Candlestick>> divideList(const std::vector<Candlestick> &inputVector, int numElements);

private:
    vector<vector<OrderBookEntry>> groupedEntries;
    string timestamp;
    const vector<OrderBookEntry> getPreviousTimestampEntries();
    const vector<OrderBookEntry> getCurrentTimestampEntries();
    const double getOpeningPrice();
    const double getClosingPrice();
    const double getHighestPrice();
    const double getLowestPrice();
    // The parameter must be a list of entries, where all entries have the same timestamp
    static const double computeMeanPrice(vector<OrderBookEntry> entries);
};