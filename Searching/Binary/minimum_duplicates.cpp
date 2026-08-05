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

        if (arr[mid] > arr[high])
        {
            low = mid + 1;
        }
        else if (arr[mid] < arr[high])
        {
            high = mid;
        }
        else
        {
            high--;
        }
    }

    cout << "Minimum Element = " << arr[low];

    return 0;
}