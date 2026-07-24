#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], key;
    int position = -1;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the rotated sorted array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the element to search: ";
    cin >> key;

    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (arr[mid] == key)
        {
            position = mid + 1;
            break;
        }

        if (arr[low] <= arr[mid])
        {
            if (key >= arr[low] && key < arr[mid])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        else
        {
            if (key > arr[mid] && key <= arr[high])
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
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