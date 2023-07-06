#include <vector>
#include <map>
#include "OrderBookEntry.h"

class VolumeBarChart
{
public:
    // Get the volumes for the volume bar chart.
    static std::vector<double> getVolumes(std::map<std::string, std::vector<OrderBookEntry>> groupedEntries);
    // Get the timestamps for the volume bar chart.
    static std::vector<std::string> getTimestamps(std::map<std::string, std::vector<OrderBookEntry>> groupedEntries);
    // Plot the given volumes in a chart.
    static void plotChart(std::vector<double> volumes, std::vector<std::string> timestamps);
    // Group the entries by timestamp into a map.
    static std::map<std::string, vector<OrderBookEntry>> groupByTimestampsMap(vector<OrderBookEntry> entries);

private:
    // Draw the axes from chart.
    static std::vector<std::string> plotAxes(std::vector<std::string> plot, int width, const std::vector<std::string> &xAxisValues, const std::vector<double> &yAxisValues);
};