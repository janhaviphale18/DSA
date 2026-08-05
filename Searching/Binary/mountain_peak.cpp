#include <iostream>
using namespace std;

int main()
{
    int n, arr[100];

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int low = 0;
    int high = n - 1;

    while (low < high)
    {
        int mid = low + (high - low) / 2;

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
    cout << "Peak Index = " << low;

    return 0;
}