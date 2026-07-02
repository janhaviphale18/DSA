#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    cout << "Reversed array: ";
    for (int index = size - 1; index >= 0; index--)
    {
        cout << numbers[index] << " ";
    }

    return 0;
}