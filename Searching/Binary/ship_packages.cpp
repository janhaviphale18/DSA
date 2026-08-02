#include <iostream>
using namespace std;

bool isPossible(int arr[], int n, int days, int capacity)
{
    int dayCount = 1;
    int currentWeight = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > capacity)
        {
            return false;
        }

        if (currentWeight + arr[i] <= capacity)
        {
            currentWeight += arr[i];
        }
        else
        {
            dayCount++;
            currentWeight = arr[i];

            if (dayCount > days)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    int n, days;
    int arr[100];

    cout << "Enter number of packages: ";
    cin >> n;

    cout << "Enter package weights: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter number of days: ";
    cin >> days;

    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    int low = 0;
    int high = sum;
    int answer = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (isPossible(arr, n, days, mid))
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << "Minimum Ship Capacity = " << answer;

    return 0;
}