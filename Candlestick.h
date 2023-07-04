#pragma once
#include <string>
using namespace std;

class Candlestick
{
public:
    Candlestick(
        string _date,
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

    string date;
    double open;
    double high;
    double low;
    double close;

    void print();
};