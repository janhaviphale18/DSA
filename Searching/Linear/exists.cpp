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

    cout << "Enter the element to search: ";
    cin >> key;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        cout << "Element is Present.";
    }
    else
    {
        cout << "Element is Not Present.";
    }

    return 0;
}