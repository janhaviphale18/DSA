#include <iostream>
using namespace std;

int main()
{
    int size1, size2;
    int first[100], second[100], merged[200];

    cout << "Enter number of elements in first array: ";
    cin >> size1;

    cout << "Enter first array elements: ";
    for (int index = 0; index < size1; index++)
    {
        cin >> first[index];
    }

    cout << "Enter number of elements in second array: ";
    cin >> size2;

    cout << "Enter second array elements: ";
    for (int index = 0; index < size2; index++)
    {
        cin >> second[index];
    }

    for (int index = 0; index < size1; index++)
    {
        merged[index] = first[index];
    }

    for (int index = 0; index < size2; index++)
    {
        merged[size1 + index] = second[index];
    }

    cout << "Merged array: ";
    for (int index = 0; index < size1 + size2; index++)
    {
        cout << merged[index] << " ";
    }

    return 0;
}