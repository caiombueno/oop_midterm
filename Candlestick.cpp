#include "Candlestick.h"
#include <iostream>

void Candlestick::print()
{
    cout << "Candlestick(date: " << date << ", open: " << open << ", high: " << high << ", low: " << low << ", close: " << close << ")" << endl;
}
