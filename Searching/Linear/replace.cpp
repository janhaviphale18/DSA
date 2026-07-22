#include <iostream>
using namespace std;

int main()
{
    int n, arr[100];
    int key, newValue;
    bool found = false;

    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the elements in the array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the element to be replaced: ";
    cin >> key;

    cout << "Enter the new element: ";
    cin >> newValue;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            arr[i] = newValue;
            found = true;
        }
    }

    if (found)
    {
        cout << "Updated array: ";
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }
    }
    else
    {
        cout << "Element not found.";
    }

    return 0;
}