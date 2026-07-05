#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int temporary;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    temporary = numbers[size - 1];

    for (int index = size - 1; index > 0; index--)
    {
        numbers[index] = numbers[index - 1];
    }

    numbers[0] = temporary;

    cout << "Array after right rotation: ";

    for (int index = 0; index < size; index++)
    {
        cout << numbers[index] << " ";
    }

    cout << endl;

    return 0;
}