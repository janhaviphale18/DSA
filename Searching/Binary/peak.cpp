#include <iostream>
using namespace std;

int main()
{
    int n, arr[100];

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int low = 0;
    int high = n - 1;
    int mid;

    while (low < high)
    {
        mid = low + (high - low) / 2;

        if (arr[mid] < arr[mid + 1])
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }

    cout << "Peak Element = " << arr[low] << endl;
    cout << "Position = " << low + 1;

    return 0;
}