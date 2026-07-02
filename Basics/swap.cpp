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

    temporary = numbers[0];
    numbers[0] = numbers[size - 1];
    numbers[size - 1] = temporary;

    cout << "Updated array: ";
    for (int index = 0; index < size; index++)
    {
        cout << numbers[index] << " ";
    }

    return 0;
}