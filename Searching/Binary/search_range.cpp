
#include <iostream>
using namespace std;

int findFirst(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;
    int answer = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
        {
            answer = mid;
            high = mid - 1;
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return answer;
}

int findLast(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;
    int answer = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
        {
            answer = mid;
            low = mid + 1;
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return answer;
}

int main()
{
    int n, arr[100], key;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter sorted array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter element to search: ";
    cin >> key;

    int first = findFirst(arr, n, key);
    int last = findLast(arr, n, key);

    if (first == -1)
    {
        cout << "Positions = -1 -1";
    }
    else
    {
        cout << "First Position = " << first + 1 << endl;
        cout << "Last Position = " << last + 1;
    }

    return 0;
}
