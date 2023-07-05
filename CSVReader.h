#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>
using namespace std;

class CSVReader
{
public:
    CSVReader();

    static std::vector<OrderBookEntry> readCSV(std::string csvFile);
    static std::vector<std::string> tokenise(std::string csvLine, char separator);

    static OrderBookEntry stringsToOBE(std::string price,
                                       std::string amount,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType OrderBookType);

    // Read all entries and select the ones that match the given product and orderBookType
    static vector<OrderBookEntry> filterByProductAndType(string product, OrderBookType orderBookType);

private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};