#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], key;
    int position = -1;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the sorted array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the element to search: ";
    cin >> key;

    int low = 0;
    int high = 1;

    while (high < n && arr[high] < key)
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

        if (arr[mid] == key)
        {
            position = mid + 1;
            break;
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    if (position != -1)
    {
        cout << "Element found at position " << position;
    }
    else
    {
        cout << "Element not found.";
    }

    return 0;
}