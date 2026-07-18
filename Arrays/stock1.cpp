#include <iostream>
using namespace std;

int main()
{
    int size;
    int price[100];

    cout << "Enter number of days: ";
    cin >> size;

    cout << "Enter stock prices: ";

    for (int index = 0; index < size; index++)
    {
        cin >> price[index];
    }

    int minimumPrice = price[0];
    int minimumDay = 0;

    int maximumProfit = 0;
    int buyDay = 0;
    int sellDay = 0;

    for (int index = 1; index < size; index++)
    {
        int profit = price[index] - minimumPrice;

        if (profit > maximumProfit)
        {
            maximumProfit = profit;
            buyDay = minimumDay;
            sellDay = index;
        }

        if (price[index] < minimumPrice)
        {
            minimumPrice = price[index];
            minimumDay = index;
        }
    }

    if (maximumProfit > 0)
    {
        cout << "Maximum Profit: " << maximumProfit << endl;
        cout << "Buy on Day: " << buyDay + 1 << endl;
        cout << "Sell on Day: " << sellDay + 1 << endl;
    }
    else
    {
        cout << "Maximum Profit: 0" << endl;
        cout << "No profitable transaction possible." << endl;
    }

    return 0;
}