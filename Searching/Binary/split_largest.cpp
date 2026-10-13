
#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], k;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter non-negative array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter number of subarrays: ";
    cin >> k;

    if (k < 1 || k > n)
    {
        cout << "Invalid number of subarrays.";
        return 0;
    }

    long long low = 0;
    long long high = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > low)
        {
            low = arr[i];
        }

        high += arr[i];
    }

    long long answer = high;

    while (low <= high)
    {
        long long mid = low + (high - low) / 2;

        int subarrays = 1;
        long long sum = 0;

        for (int i = 0; i < n; i++)
        {
            if (sum + arr[i] > mid)
            {
                subarrays++;
                sum = arr[i];
            }
            else
            {
                sum += arr[i];
            }
        }

        if (subarrays <= k)
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << "Minimum Largest Subarray Sum = " << answer;

    return 0;
}
