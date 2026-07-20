#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], key;
    int position = -1;

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

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (arr[mid] == key)
        {
            position = mid + 1;      
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

    if (position != -1)
    {
        cout << "First occurrence found at position " << position;
    }
    else
    {
        cout << "Element not found in the array.";
    }

    return 0;
}