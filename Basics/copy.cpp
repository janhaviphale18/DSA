#include <iostream>
using namespace std;

int main()
{
    int size;
    int first[100];
    int second[100];

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> first[index];
    }

    for (int index = 0; index < size; index++)
    {
        second[index] = first[index];
    }

    cout << "Copied array: ";
    for (int index = 0; index < size; index++)
    {
        cout << second[index] << " ";
    }

    return 0;
}