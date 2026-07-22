#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], key;
    bool found = false;
    int position;

    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the elements in the array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the element to be deleted: ";
    cin >> key;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            position = i;
            found = true;
            break;
        }
    }

    if (found)
    {
        for (int i = position; i < n - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        n--;

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