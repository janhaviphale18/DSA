#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Enter the number of coins: ";
    cin >> n;

    int low = 0;
    int high = n;
    int answer = 0;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        long long coins = 1LL * mid * (mid + 1) / 2;

        if (coins <= n)
        {
            answer = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << "Maximum Complete Rows = " << answer;

    return 0;
}