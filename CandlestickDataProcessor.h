#pragma once
#include <vector>
#include <string>
#include <map>
#include "Candlestick.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"

class CandlestickDataProcessor
{
public:
    // Get a list of Candlestick data
    const std::vector<Candlestick> getList(std::vector<OrderBookEntry> filteredEntries);
    // Divide the vector into smaller segments, so that the length of each doesn't exceed 'numElements' length.
    static std::vector<vector<Candlestick>> divideList(const std::vector<Candlestick> &inputVector, int numElements);
    // Group the entries by timestamp.
    static vector<vector<OrderBookEntry>> groupByTimestamps(vector<OrderBookEntry> entries);

private:
    // Store the entries grouped based on their timestamps.
    std::vector<std::vector<OrderBookEntry>> groupedEntries;
    // Store the current timestamp being used.
    string timestamp;
    // Retrieve the entries with a timestamp preceding the current one.
    const std::vector<OrderBookEntry> getPreviousTimestampEntries();
    // Retrive the entries with the current timestamp.
    const std::vector<OrderBookEntry> getCurrentTimestampEntries();
    // Get the open price for the candlestick.
    const double getOpeningPrice();
    // Get the close price for the candlestick.
    const double getClosingPrice();
    // Get the high price for the candlestick.
    const double getHighestPrice();
    // Get the low price for the candlestick.
    const double getLowestPrice();
    // Retrieve the mean price for the given entries.
    // All entries must have the same timestamp.
    static const double computeMeanPrice(std::vector<OrderBookEntry> entries);
};