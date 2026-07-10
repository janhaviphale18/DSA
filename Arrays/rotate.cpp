#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int rotated[100];
    int positions;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    cout << "Enter number of positions to rotate: ";
    cin >> positions;

    positions = positions % size;

    for (int index = 0; index < size; index++)
    {
        int newIndex = (index + positions) % size;
        rotated[newIndex] = numbers[index];
    }

    for (int index = 0; index < size; index++)
    {
        numbers[index] = rotated[index];
    }

    cout << "Rotated array: ";

    for (int index = 0; index < size; index++)
    {
        cout << numbers[index] << " ";
    }

    cout << endl;

    return 0;
}