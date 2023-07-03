#include "CandlestickAnalysisToolkit.h"
#include "CSVReader.h"
#include <iostream>
#include <exception>

const vector<Candlestick> CandlestickAnalysisToolkit::getCandlestickList()
{
    vector<Candlestick> listOfCandlestick;
    groupedEntries.resize(10);
    for (const vector<OrderBookEntry> &timestampWindow : groupedEntries)
    {
        timestamp = timestampWindow[0].timestamp;
        double open = getOpeningPrice();
        double close = getClosingPrice();
        double high = getHighestPrice();
        double low = getLowestPrice();
        Candlestick candlestickInstance = Candlestick(timestamp, open, high, low, close);
        candlestickInstance.print();
        listOfCandlestick.push_back(candlestickInstance);
    }
    return listOfCandlestick;
}

const double CandlestickAnalysisToolkit::computeMeanPrice(vector<OrderBookEntry> entries)
{
    double totalValue = 0;
    double totalPrice = 0;
    // iterate throught all entries and add its value and price to the total sum of each one
    for (const OrderBookEntry &entry : entries)
    {
        totalValue += entry.amount * entry.price;
        totalPrice += entry.price;
    }
    // return mean price
    return totalValue / totalPrice;
}

const double CandlestickAnalysisToolkit::getOpeningPrice()
{
    vector<OrderBookEntry> previousTimestampEntries = getPreviousTimestampEntries();
    return computeMeanPrice(previousTimestampEntries);
}

const double CandlestickAnalysisToolkit::getClosingPrice()
{
    vector<OrderBookEntry> currentTimestampEntries = getCurrentTimestampEntries();
    return computeMeanPrice(currentTimestampEntries);
}

const double CandlestickAnalysisToolkit::getHighestPrice()
{
    vector<OrderBookEntry> currentTimestampEntries = getCurrentTimestampEntries();

    double highestPrice = 0;
    for (const OrderBookEntry &entry : currentTimestampEntries)
    {
        if (entry.price > highestPrice)
        {
            highestPrice = entry.price;
        }
    }
    return highestPrice;
}

const double CandlestickAnalysisToolkit::getLowestPrice()
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

const vector<OrderBookEntry> CandlestickAnalysisToolkit::getPreviousTimestampEntries()
{
    for (int i = 0; i < groupedEntries.size(); i++)
    {
        if (groupedEntries[i][0].timestamp == timestamp)
        {
            if (i == 0)
            {
                cout << "AnalysisToolkit::getPreviousTimestampEntries there are no previous timestamps entries";
                return vector<OrderBookEntry>();
            }
            else
            {
                return groupedEntries[--i];
            }
        }
    }
    cout << "AnalysisToolkit::getPreviousTimestampEntries could not find previous timestamp entries\n";
    throw exception();
}

const vector<OrderBookEntry> CandlestickAnalysisToolkit::getCurrentTimestampEntries()
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
