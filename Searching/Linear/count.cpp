#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], key;
    int count = 0;

    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the elements in the array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the key to be searched: ";
    cin >> key;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            count++;
        }
    }

    if (count > 0)
    {
        cout << "Element occurs " << count << " time(s).";
    }
    else
    {
        cout << "Element not found.";
    }

    return 0;
}