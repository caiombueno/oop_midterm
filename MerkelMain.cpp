#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "CandlestickDataProcessor.h"
#include "CandlestickChart.h"
#include "VolumeBarChart.h"

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 print candletick graph for some product,order type
    std::cout << "6: Print candletick graph for some product,order type " << std::endl;
    // 7 print volume bar graph for some product,order type
    std::cout << "7: Print volume bar graph for some product,order type " << std::endl;
    // 8 Print order type distribution for the current timeframe
    std::cout << "8: Print order type distribution for the current timeframe. " << std::endl;
    // 9 continue
    std::cout << "9: Continue " << std::endl;

    std::cout << "============== " << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const &p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                  p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    }
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
        }
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid);
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << " MerkelMain::enterBid Bad input " << std::endl;
        }
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry &sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
    }

    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-9" << std::endl;
    std::getline(std::cin, line);
    try
    {
        userOption = std::stoi(line);
    }
    catch (const std::exception &e)
    {
        //
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        std::string line;
        std::cout << "Type in a product and a order type. Ex: ETH/BTC,bid." << std::endl;
        std::getline(std::cin, line);
        vector<string> elements = CSVReader::tokenise(line, ',');
        std::string product = elements[0];
        OrderBookType order = OrderBookEntry::stringToOrderBookType(elements[1]);
        if (order == OrderBookType::unknown)
        {
            std::cout << "Error. Type another order book type." << std::endl;
        }
        else
        {
            plotCandlestickGraph(product, order);
        }
    }
    if (userOption == 7)
    {
        std::string line;
        std::cout << "Type in a product and a order type. Ex: ETH/BTC,bid." << std::endl;
        std::getline(std::cin, line);
        vector<string> elements = CSVReader::tokenise(line, ',');
        std::string product = elements[0];
        OrderBookType order = OrderBookEntry::stringToOrderBookType(elements[1]);
        if (order == OrderBookType::unknown)
        {
            std::cout << "Error. Type another order book type." << std::endl;
        }
        else
        {
            plotVolumeBarGraph(product, order);
        }
    }
    if (userOption == 8)
    {
        std::string product;
        std::cout << "Type in a product. Ex: ETH/BTC." << std::endl;
        std::getline(std::cin, product);
        orderBook.plotOrderTypeDistribution(product, currentTime);
    }
    if (userOption == 9)
    {
        gotoNextTimeframe();
    }
}

void MerkelMain::plotCandlestickGraph(std::string product, OrderBookType orderType)
{
    CandlestickDataProcessor dataProcessor = CandlestickDataProcessor();
    std::vector<OrderBookEntry> filteredEntries = orderBook.filterByProductAndType(product, orderType);
    vector<Candlestick> candlesticks = dataProcessor.getList(filteredEntries);

    vector<vector<Candlestick>> dividedCandlestickList = CandlestickDataProcessor::divideList(candlesticks, 16);
    int currentIndex = 0;
    char choice;

    do
    {
        CandlestickChart::plotChart(dividedCandlestickList[currentIndex]);
        currentIndex++;

        if (currentIndex >= dividedCandlestickList.size())
        {
            std::cout << "No more candlesticks." << std::endl;
            break;
        }

        std::cout << "Do you want to see the more candlesticks for your choice? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

void MerkelMain::plotVolumeBarGraph(std::string product, OrderBookType orderType)
{
    std::vector<OrderBookEntry> filteredEntries = orderBook.filterByProductAndType(product, orderType);
    std::map<std::string, vector<OrderBookEntry>> groupedEntries = VolumeBarChart::groupByTimestampsMap(filteredEntries);
    std::vector<double> volumes = VolumeBarChart::getVolumes(groupedEntries);
    std::vector<std::string> timestamps = VolumeBarChart::getTimestamps(groupedEntries);
    int startIndex = 0;
    int endIndex = 10;
    char choice;

    do
    {
        std::vector<double> newVolumes = {};
        std::vector<std::string> newTimestamps = {};
        for (int i = startIndex; i < endIndex; i++)
        {
            newVolumes.push_back(volumes[i]);
            newTimestamps.push_back(timestamps[i]);
        }
        VolumeBarChart::plotChart(newVolumes, newTimestamps);
        startIndex += 10;
        endIndex += 10;

        if (endIndex >= volumes.size())
        {
            std::cout << "No more volumes." << std::endl;
            break;
        }

        std::cout << "Do you want to see the more volumes for your choice? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}
