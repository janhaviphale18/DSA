#include <iostream>
using namespace std;

bool isPossible(int arr[], int n, int bouquets, int flowers, int days)
{
    int bouquetCount = 0;
    int flowerCount = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] <= days)
        {
            flowerCount++;

            if (flowerCount == flowers)
            {
                bouquetCount++;
                flowerCount = 0;

                if (bouquetCount >= bouquets)
                {
                    return true;
                }
            }
        }
        else
        {
            flowerCount = 0;
        }
    }

    return false;
}

int main()
{
    int n, bouquets, flowers;
    int arr[100];

    cout << "Enter number of flowers: ";
    cin >> n;

    cout << "Enter bloom days: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter number of bouquets: ";
    cin >> bouquets;

    cout << "Enter flowers per bouquet: ";
    cin >> flowers;

    if (bouquets * flowers > n)
    {
        cout << "-1";
        return 0;
    }

    int minimum = arr[0];
    int maximum = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] < minimum)
        {
            minimum = arr[i];
        }

        if (arr[i] > maximum)
        {
            maximum = arr[i];
        }
    }

    int low = minimum;
    int high = maximum;
    int answer = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (isPossible(arr, n, bouquets, flowers, mid))
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << "Minimum Days = " << answer;

    return 0;
}