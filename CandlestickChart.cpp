#include "CandlestickChart.h"
#include <iostream>

std::vector<double> CandlestickChart::generateYAxisValues(double maxValue, double minValue, int numberOfElements)
{
    std::vector<double> result(numberOfElements);
    double step = (maxValue - minValue) / (numberOfElements - 1);

    for (int i = 0; i < numberOfElements; i++)
    {
        result[i] = maxValue - (i * step);
    }

    return result;
}

std::vector<Candlestick> CandlestickChart::cutDatesStrings(std::vector<Candlestick> candlesticks)
{
    for (int i = 0; i < candlesticks.size(); i++)
    {
        candlesticks[i].date = candlesticks[i].date.substr(11, 8);
    }
    return candlesticks;
}

std::vector<std::string> CandlestickChart::plotAxes(std::vector<std::string> plot, int width, const std::vector<std::string> &xAxisValues, const std::vector<double> &yAxisValues)
{
    // add Y Axis
    for (int i = 0; i < yAxisValues.size(); i++)
    {
        plot[i] = std::to_string(yAxisValues[i]) + " |";
    }
    // add divider
    for (int x = 0; x < width; x++)
    {
        plot[10][x] = '-';
    }

    // add X Axis
    plot[11] = "DATE  | ";
    for (const std::string &element : xAxisValues)
    {
        plot[11] += "  " + element;
    }

    return plot;
}

int CandlestickChart::getClosestYIndex(std::vector<double> yAxisValues, double value)
{
    double minDifference = std::abs(yAxisValues[0] - value);
    int closestIndex = 0;

    for (int i = 1; i < yAxisValues.size(); i++)
    {
        double difference = std::abs(yAxisValues[i] - value);
        if (difference < minDifference)
        {
            minDifference = difference;
            closestIndex = i;
        }
    }
    return closestIndex;
}

const void CandlestickChart::plotChart(std::vector<Candlestick> candlesticks)
{
    candlesticks = cutDatesStrings(candlesticks);
    const int width = 190;
    const int height = 12;

    double maxValue = candlesticks[0].high;
    double minValue = candlesticks[0].low;

    // Find the maximum and minimum values in the candlestick data
    for (const Candlestick &candlestick : candlesticks)
    {
        if (candlestick.high > maxValue)
        {
            maxValue = candlestick.high;
        }
        if (candlestick.low < minValue)
        {
            minValue = candlestick.low;
        }
    }
    // create the plot
    std::vector<std::string> plot(height, std::string(width, ' '));

    // get Y axis values
    std::vector<double> yAxisValues = generateYAxisValues(maxValue, minValue, 10);

    // get X axis values
    std::vector<std::string> xAxisValues;
    for (const Candlestick &candlestick : candlesticks)
    {
        xAxisValues.push_back(candlestick.date);
    }

    // draw the axes
    plot = plotAxes(plot, width, xAxisValues, yAxisValues);

    // set the x position to the x position of the first candlestick
    int x = 13;
    // plot candlestick data
    for (int i = 0; i < candlesticks.size(); i++)
    {
        bool bodyDrawn = false;
        // get candlestick data
        double high = candlesticks[i].high;
        double low = candlesticks[i].low;
        double open = candlesticks[i].open;
        double close = candlesticks[i].close;

        const char wickSymbol = '|';

        double highest;
        double lowest;
        char bodySymbol;

        // determine which price is the highest and lowest, and representative symbol for the body of the candlestick
        if (open > close)
        {
            highest = open;
            lowest = close;
            bodySymbol = 'v';
        }
        else
        {
            highest = close;
            lowest = open;
            bodySymbol = '^';
        }

        // iterate through each y value
        for (int y = 0; y < yAxisValues.size(); y++)
        {
            // assert that each line has the correct width
            plot[y].resize(width, ' ');

            double yValue = yAxisValues[y];
            // determine if wick should be drawn in this y position
            if (yValue <= high and yValue >= low)
            {
                plot[y][x] = wickSymbol;
            }
            // determine if body should be drawn in this y position
            if (yValue <= highest and yValue >= lowest)
            {
                plot[y][x] = bodySymbol;
                bodyDrawn = true;
            }
        }
        // if no body was drawn for the candlestick, draw body at the index of the closest y value from 'highest'
        if (!bodyDrawn)
        {
            int closestIndex = getClosestYIndex(yAxisValues, highest);
            plot[closestIndex][x] = bodySymbol;
        }
        // jump to next candlestick x position
        x += 10;
    }
    // print the graph
    for (std::string line : plot)
    {
        std::cout << line << std::endl;
    }
}