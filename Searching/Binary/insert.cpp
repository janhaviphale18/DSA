#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], key;
    int answer;

    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the sorted elements in the array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the key: ";
    cin >> key;

    int low = 0;
    int high = n - 1;
    int mid;

    answer = n;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (arr[mid] >= key)
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << "Insert Position = " << answer + 1;

    return 0;
}