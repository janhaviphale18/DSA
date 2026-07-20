#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], key;
    bool found = false;

    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the elements in the array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the key to be searched: ";
    cin >> key;

    cout << "Element found at position(s): ";

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            cout << i + 1 << " ";
            found = true;
        }
    }

    if (!found)
    {
        cout << "Element not found.";
    }

    return 0;
}