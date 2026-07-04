#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int position;
    int newValue;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    cout << "Enter position to update: ";
    cin >> position;

    if (position < 1 || position > size)
    {
        cout << "Invalid position!" << endl;
        return 0;
    }

    cout << "Enter new value: ";
    cin >> newValue;

    numbers[position - 1] = newValue;

    cout << "Updated array: ";

    for (int index = 0; index < size; index++)
    {
        cout << numbers[index] << " ";
    }

    cout << endl;

    return 0;
}