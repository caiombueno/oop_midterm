#include <vector>
#include <string>
#include "Candlestick.h"

class CandlestickChart
{
public:
    // Plot the given candlesticks in a chart.
    static const void plotChart(std::vector<Candlestick> candlesticks);

private:
    // Return a vector of values for the Y axis.
    static std::vector<double> generateYAxisValues(double maxValue, double minValue, int numberOfElements);
    // Cut irrelevant data from dates in candlesticks.
    static std::vector<Candlestick> cutDatesStrings(std::vector<Candlestick> candlesticks);
    // Draw the axes from chart.
    static std::vector<std::string> plotAxes(std::vector<std::string> plot, int width, const std::vector<std::string> &xAxisValues, const std::vector<double> &yAxisValues);
    // Get the index of the closest value of Y axis from 'value'.
    static int getClosestYIndex(std::vector<double> yAxisValues, double value);
};