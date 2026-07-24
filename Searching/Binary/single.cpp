#include <iostream>
using namespace std;

int main()
{
    int n, arr[100];

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the sorted array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int low = 0;
    int high = n - 1;

    while (low < high)
    {
        int mid = low + (high - low) / 2;

        if (mid % 2 == 1)
        {
            mid--;
        }

        if (arr[mid] == arr[mid + 1])
        {
            low = mid + 2;
        }
        else
        {
            high = mid;
        }
    }

    cout << "Single Element = " << arr[low];

    return 0;
}