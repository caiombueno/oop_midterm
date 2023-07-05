#pragma once
#include <string>
#include <iostream>

// The candlestick model class used to represent a candlestick
class Candlestick
{
public:
    Candlestick(
        std::string _date,
        double _open,
        double _high,
        double _low,
        double _close)
    {
        date = _date;
        open = _open;
        high = _high;
        low = _low;
        close = _close;
    }

    std::string date;
    double open;
    double high;
    double low;
    double close;

    void print()
    {
        std::cout << "Candlestick(date: " << date << ", open: " << open << ", high: " << high << ", low: " << low << ", close: " << close << ")" << std::endl;
    }
};