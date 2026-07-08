#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int suffix[100];

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    suffix[size - 1] = numbers[size - 1];

    for (int index = size - 2; index >= 0; index--)
    {
        suffix[index] = suffix[index + 1] + numbers[index];
    }

    cout << "Suffix Sum Array: ";

    for (int index = 0; index < size; index++)
    {
        cout << suffix[index] << " ";
    }

    cout << endl;

    return 0;
}