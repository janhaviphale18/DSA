#include <iostream>
using namespace std;

int main()
{
    int n, arr[100];

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the rotated sorted array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int low = 0;
    int high = n - 1;
    int answer = 0;

    while (low <= high)
    {
        if (arr[low] <= arr[high])
        {
            answer = low;
            break;
        }

        int mid = low + (high - low) / 2;

        if (arr[mid] >= arr[low])
        {
            low = mid + 1;
        }
        else
        {
            answer = mid;
            high = mid - 1;
        }
    }

    cout << "Number of rotations = " << answer;

    return 0;
}