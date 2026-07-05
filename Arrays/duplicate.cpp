#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int unique[100];
    int uniqueSize = 0;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter sorted array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    for (int index = 0; index < size - 1; index++)
    {
        if (numbers[index] != numbers[index + 1])
        {
            unique[uniqueSize] = numbers[index];
            uniqueSize++;
        }
    }

    unique[uniqueSize] = numbers[size - 1];
    uniqueSize++;

    cout << "Array after removing duplicates: ";

    for (int index = 0; index < uniqueSize; index++)
    {
        cout << unique[index] << " ";
    }

    cout << endl;

    return 0;
}