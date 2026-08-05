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

    if (arr[low] <= arr[high])
    {
        cout << "Pivot Element = " << arr[high];
        cout << "\nPivot Index = " << high;
        return 0;
    }

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (mid < high && arr[mid] > arr[mid + 1])
        {
            cout << "Pivot Element = " << arr[mid];
            cout << "\nPivot Index = " << mid;
            return 0;
        }

        if (mid > low && arr[mid] < arr[mid - 1])
        {
            cout << "Pivot Element = " << arr[mid - 1];
            cout << "\nPivot Index = " << mid - 1;
            return 0;
        }

        if (arr[low] <= arr[mid])
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return 0;
}