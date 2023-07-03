#include <vector>
#include <string>
#include "Candlestick.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
using namespace std;

class CandlestickAnalysisToolkit
{
public:
    CandlestickAnalysisToolkit(string product, OrderBookType orderType)
    {
        vector<OrderBookEntry> filteredEntries = CSVReader::filterByProductAndType(product, orderType);
        groupedEntries = CSVReader::groupByTimestamps(filteredEntries);
    }
    const vector<Candlestick> getCandlestickList();

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