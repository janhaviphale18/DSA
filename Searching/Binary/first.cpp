#include <iostream>
using namespace std;

int main()
{
    int n, arr[100];
    int answer = -1;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the binary array elements (0s followed by 1s): ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int low = 0;
    int high = 1;

    while (high < n && arr[high] == 0)
    {
        low = high;
        high = high * 2;

        if (high >= n)
        {
            high = n - 1;
        }
    }

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == 1)
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    if (answer != -1)
    {
        cout << "First 1 is at position " << answer + 1;
    }
    else
    {
        cout << "1 is not present in the array.";
    }

    return 0;
}