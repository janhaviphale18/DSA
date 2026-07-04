#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int position;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    cout << "Enter position to delete: ";
    cin >> position;

    if (position < 1 || position > size)
    {
        cout << "Invalid position!" << endl;
        return 0;
    }

    for (int index = position - 1; index < size - 1; index++)
    {
        numbers[index] = numbers[index + 1];
    }

    size--;

    cout << "Updated array: ";

    for (int index = 0; index < size; index++)
    {
        cout << numbers[index] << " ";
    }

    cout << endl;

    return 0;
}