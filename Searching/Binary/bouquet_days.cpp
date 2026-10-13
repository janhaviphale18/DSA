
#include <iostream>
using namespace std;

int main()
{
    int n, bloom[100];
    int m, k;

    cout << "Enter number of flowers: ";
    cin >> n;

    cout << "Enter blooming days: ";
    for (int i = 0; i < n; i++)
    {
        cin >> bloom[i];
    }

    cout << "Enter number of bouquets: ";
    cin >> m;

    cout << "Enter flowers per bouquet: ";
    cin >> k;

    if (1LL * m * k > n)
    {
        cout << "It is impossible to make bouquets.";
        return 0;
    }

    int low = bloom[0];
    int high = bloom[0];

    for (int i = 1; i < n; i++)
    {
        if (bloom[i] < low)
        {
            low = bloom[i];
        }

        if (bloom[i] > high)
        {
            high = bloom[i];
        }
    }

    int answer = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int bouquets = 0;
        int flowers = 0;

        for (int i = 0; i < n; i++)
        {
            if (bloom[i] <= mid)
            {
                flowers++;

                if (flowers == k)
                {
                    bouquets++;
                    flowers = 0;
                }
            }
            else
            {
                flowers = 0;
            }
        }

        if (bouquets >= m)
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << "Minimum Days Required = " << answer;

    return 0;
}
