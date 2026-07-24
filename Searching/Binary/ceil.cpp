#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], key;
    int answer = -1;

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

    if (answer != -1)
    {
        cout << "Ceil = " << arr[answer] << endl;
        cout << "Position = " << answer + 1;
    }
    else
    {
        cout << "Ceil does not exist.";
    }

    return 0;
}