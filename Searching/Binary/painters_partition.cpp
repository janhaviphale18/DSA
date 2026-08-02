#include <iostream>
using namespace std;

bool isPossible(int arr[], int n, int painters, int maxTime)
{
    int painterCount = 1;
    int boardSum = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > maxTime)
        {
            return false;
        }

        if (boardSum + arr[i] <= maxTime)
        {
            boardSum += arr[i];
        }
        else
        {
            painterCount++;
            boardSum = arr[i];

            if (painterCount > painters)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    int n, painters;
    int arr[100];

    cout << "Enter number of boards: ";
    cin >> n;

    cout << "Enter board lengths: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter number of painters: ";
    cin >> painters;

    if (painters > n)
    {
        cout << "Partition not possible.";
        return 0;
    }

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

        if (isPossible(arr, n, painters, mid))
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << "Minimum Time Required = " << answer;

    return 0;
}