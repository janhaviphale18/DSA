#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], key;
    int first = -1, last = -1;

    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the sorted elements in the array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the key to be searched: ";
    cin >> key;

    int low = 0;
    int high = n - 1;
    int mid;

    // Find First Occurrence
    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (arr[mid] == key)
        {
            first = mid;
            high = mid - 1;
        }
        else if (key < arr[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    low = 0;
    high = n - 1;

    // Find Last Occurrence
    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (arr[mid] == key)
        {
            last = mid;
            low = mid + 1;
        }
        else if (key < arr[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    if (first != -1)
    {
        cout << "Total occurrences = " << last - first + 1;
    }
    else
    {
        cout << "Element not found.";
    }

    return 0;
}