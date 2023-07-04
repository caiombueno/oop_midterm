#include <vector>
#include <string>
#include "Candlestick.h"

class CandlestickChart
{
public:
    static const void plotCandlestickChart(const vector<Candlestick> &candlesticks);

private:
    static std::vector<double> generateYAxisValues(double maxValue, double minValue, int numberOfElements);
    static std::vector<Candlestick> cutDatesStrings(std::vector<Candlestick> candlesticks);
    static std::vector<string> plotAxes(std::vector<std::string> plot, int width, const std::vector<std::string> &xAxisValues, const std::vector<double> &yAxisValues);
    static int getClosestYIndex(std::vector<double> yAxisValues, double highest);
};