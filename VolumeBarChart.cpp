#include "VolumeBarChart.h"
#include "Chart.h"
#include <iostream>
#include <iomanip>
#include <sstream>

std::vector<double> VolumeBarChart::getVolumes(std::map<std::string, std::vector<OrderBookEntry>> groupedEntries)
{
    std::vector<double> volumes;

    for (auto element : groupedEntries)
    {
        std::vector<OrderBookEntry> entries = element.second;
        double totalAmount = 0;
        for (OrderBookEntry &entry : entries)
        {
            totalAmount += entry.amount;
        }
        volumes.push_back(totalAmount);
    }

    return volumes;
}

std::map<std::string, vector<OrderBookEntry>> VolumeBarChart::groupByTimestampsMap(vector<OrderBookEntry> entries)
{
    std::map<std::string, vector<OrderBookEntry>> groupedEntries;

    // Iterate over the entries timestamps
    for (const auto &entry : entries)
    {
        groupedEntries[entry.timestamp].push_back(entry);
    }

    return groupedEntries;
}

std::vector<std::string> VolumeBarChart::getTimestamps(std::map<std::string, std::vector<OrderBookEntry>> groupedEntries)
{
    std::vector<std::string> timestamps;

    for (auto element : groupedEntries)
    {
        std::string timestamp = element.first;
        timestamp = timestamp.substr(11, 8);
        timestamps.push_back(timestamp);
    }
    return timestamps;
}

void VolumeBarChart::plotChart(std::vector<double> volumes, std::vector<std::string> timestamps)
{
    const int width = 190;
    const int height = 12;

    double maxValue = 0;

    for (const double &volume : volumes)
    {
        if (volume > maxValue)
        {
            maxValue = volume;
        }
    }

    // create the plot
    std::vector<std::string> plot(height, std::string(width, ' '));

    // get Y axis values
    std::vector<double> yAxisValues = Chart::generateYAxisValues(maxValue, 0.0, 10);

    // draw the axes
    plot = plotAxes(plot, width, timestamps, yAxisValues);

    // set the x position to the x position of the first candlestick
    int x = 13;

    for (int i = 0; i < volumes.size(); i++)
    {
        double volume = volumes[i];

        // iterate through each y value
        for (int y = 0; y < yAxisValues.size(); y++)
        {
            // assert that each line has the correct width
            plot[y].resize(width, ' ');

            double yValue = yAxisValues[y];
            // determine if bar should be drawn in this y position
            if (yValue <= volume)
            {
                plot[y][x] = '|';
            }
        }
        x += 10;
    }

    // print the graph
    for (std::string line : plot)
    {
        std::cout << line << std::endl;
    }
}

std::vector<std::string> VolumeBarChart::plotAxes(std::vector<std::string> plot, int width, const std::vector<std::string> &xAxisValues, const std::vector<double> &yAxisValues)
{
    // add Y Axis
    for (int i = 0; i < yAxisValues.size(); i++)
    {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << yAxisValues[i];
        plot[i] = stream.str();
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
