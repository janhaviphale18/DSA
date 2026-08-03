#include <iostream>
using namespace std;

bool isPossible(int arr[], int n, int trips, long long time)
{
    long long totalTrips = 0;

    for (int i = 0; i < n; i++)
    {
        totalTrips += time / arr[i];

        if (totalTrips >= trips)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    int n, trips;
    int arr[100];

    cout << "Enter number of buses: ";
    cin >> n;

    cout << "Enter time taken by each bus: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter total trips: ";
    cin >> trips;

    int minimum = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] < minimum)
        {
            minimum = arr[i];
        }
    }

    long long low = 1;
    long long high = (long long)minimum * trips;
    long long answer = high;

    while (low <= high)
    {
        long long mid = low + (high - low) / 2;

        if (isPossible(arr, n, trips, mid))
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << "Minimum Time = " << answer;

    return 0;
}