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

    cout << "Array elements are: ";

    for (int index = 0; index < size; index++)
    {
        cout << numbers[index] << " ";
    }

    cout << endl;

    return 0;
}