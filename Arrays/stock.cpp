#include <iostream>
using namespace std;

int main()
{
    int size;
    int price[100];
    int profit = 0;

    cout << "Enter number of days: ";
    cin >> size;

    cout << "Enter stock prices: ";

    for (int index = 0; index < size; index++)
    {
        cin >> price[index];
    }

    for (int index = 1; index < size; index++)
    {
        if (price[index] > price[index - 1])
        {
            profit = profit + (price[index] - price[index - 1]);
        }
    }

    cout << "Maximum Profit: " << profit << endl;

    return 0;
}