#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], key;
    int position = -1;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the nearly sorted array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the element to search: ";
    cin >> key;

    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
        {
            position = mid + 1;
            break;
        }

        if (mid - 1 >= low && arr[mid - 1] == key)
        {
            position = mid;
            break;
        }

        if (mid + 1 <= high && arr[mid + 1] == key)
        {
            position = mid + 2;
            break;
        }

        if (key < arr[mid])
        {
            high = mid - 2;
        }
        else
        {
            low = mid + 2;
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