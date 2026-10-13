
#include <iostream>
using namespace std;

int main()
{
    int n, piles[100], h;

    cout << "Enter number of piles: ";
    cin >> n;

    cout << "Enter bananas in each pile: ";
    for (int i = 0; i < n; i++)
    {
        cin >> piles[i];
    }

    cout << "Enter available hours: ";
    cin >> h;

    int low = 1;
    int high = 0;

    for (int i = 0; i < n; i++)
    {
        if (piles[i] > high)
        {
            high = piles[i];
        }
    }

    int answer = high;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        long long hours = 0;

        for (int i = 0; i < n; i++)
        {
            hours += (piles[i] + (long long)mid - 1) / mid;
        }

        if (hours <= h)
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    if (h < n)
    {
        cout << "It is impossible to finish within the given hours.";
    }
    else
    {
        cout << "Minimum Eating Speed = " << answer;
    }

    return 0;
}
