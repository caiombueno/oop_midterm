#include "CandlestickDataProcessor.h"
#include "CSVReader.h"
#include <iostream>
#include <exception>
#include <map>

const std::vector<Candlestick> CandlestickDataProcessor::getList(std::vector<OrderBookEntry> filteredEntries)
{
    groupedEntries = CandlestickDataProcessor::groupByTimestamps(filteredEntries);
    std::vector<Candlestick> candlesticks;
    for (const std::vector<OrderBookEntry> &timestampWindow : groupedEntries)
    {
        timestamp = timestampWindow[0].timestamp;
        double open = getOpeningPrice();
        double close = getClosingPrice();
        double high = getHighestPrice();
        double low = getLowestPrice();
        Candlestick candlestickInstance = Candlestick(timestamp, open, high, low, close);
        candlesticks.push_back(candlestickInstance);
    }
    return candlesticks;
}

const double CandlestickDataProcessor::computeMeanPrice(vector<OrderBookEntry> entries)
{
    double totalValue = 0;
    double totalAmount = 0;
    // iterate throught all entries and add its value and price to the total sum of each one
    for (const OrderBookEntry &entry : entries)
    {
        totalValue += entry.amount * entry.price;
        totalAmount += entry.amount;
    }
    // return mean price
    return totalValue / totalAmount;
}

vector<vector<Candlestick>> CandlestickDataProcessor::divideList(const std::vector<Candlestick> &inputVector, int numElements)
{
    std::vector<std::vector<Candlestick>> dividedVectors;

    int totalElements = inputVector.size();
    int numParts = (totalElements + numElements - 1) / numElements;

    for (int i = 0; i < numParts; ++i)
    {
        int startIndex = i * numElements;
        int endIndex = std::min(startIndex + numElements, totalElements);

        std::vector<Candlestick> part;
        part.reserve(endIndex - startIndex);

        for (int j = startIndex; j < endIndex; ++j)
        {
            part.push_back(inputVector[j]);
        }

        dividedVectors.push_back(part);
    }

    return dividedVectors;
}

const double CandlestickDataProcessor::getOpeningPrice()
{
    vector<OrderBookEntry> previousTimestampEntries = getPreviousTimestampEntries();
    if (previousTimestampEntries.empty())
    {
        return getLowestPrice();
    }
    return computeMeanPrice(previousTimestampEntries);
}

const double CandlestickDataProcessor::getClosingPrice()
{
    vector<OrderBookEntry> currentTimestampEntries = getCurrentTimestampEntries();
    return computeMeanPrice(currentTimestampEntries);
}

const double CandlestickDataProcessor::getHighestPrice()
{
    vector<OrderBookEntry> currentTimestampEntries = getCurrentTimestampEntries();

    double highestPrice = 0;
    for (const OrderBookEntry &entry : currentTimestampEntries)
    {
        // cout << entry.price << endl;
        if (entry.price > highestPrice)
        {
            highestPrice = entry.price;
        }
    }
    return highestPrice;
}

const double CandlestickDataProcessor::getLowestPrice()
{
    vector<OrderBookEntry> currentTimestampEntries = getCurrentTimestampEntries();

    double lowestPrice = getHighestPrice();
    for (const OrderBookEntry &entry : currentTimestampEntries)
    {
        if (entry.price < lowestPrice)
        {
            lowestPrice = entry.price;
        }
    }
    return lowestPrice;
}

const vector<OrderBookEntry> CandlestickDataProcessor::getPreviousTimestampEntries()
{
    for (int i = 0; i < groupedEntries.size(); i++)
    {
        if (groupedEntries[i][0].timestamp == timestamp)
        {
            if (i == 0)
            {
                // there are no previous timestamps entries
                return vector<OrderBookEntry>();
            }
            else
            {
                return groupedEntries[--i];
            }
        }
    }
    cout << "CandlestickDataProcessor::getPreviousTimestampEntries could not find previous timestamp entries\n";
    throw exception();
}

const vector<OrderBookEntry> CandlestickDataProcessor::getCurrentTimestampEntries()
{
    for (int i = 0; i < groupedEntries.size(); i++)
    {
        if (groupedEntries[i][0].timestamp == timestamp)
        {
            return groupedEntries[i];
        }
    }
    cout << "AnalysisToolkit::getCurrentTimestampEntries could not find current timestamp entries\n";
    throw exception();
}

vector<vector<OrderBookEntry>> CandlestickDataProcessor::groupByTimestamps(vector<OrderBookEntry> entries)
{
    map<string, vector<OrderBookEntry>> groupedEntries;

    // Iterate over the entries timestamps
    for (const auto &entry : entries)
    {
        groupedEntries[entry.timestamp].push_back(entry);
    }

    vector<vector<OrderBookEntry>> groupedEntriesList;

    // convert the grouped entries map to a list of vectors
    for (const auto &pair : groupedEntries)
    {
        groupedEntriesList.push_back(pair.second);
    }

    return groupedEntriesList;
}
