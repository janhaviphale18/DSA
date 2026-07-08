#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int prefix[100];

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    prefix[0] = numbers[0];

    for (int index = 1; index < size; index++)
    {
        prefix[index] = prefix[index - 1] + numbers[index];
    }

    cout << "Prefix Sum Array: ";

    for (int index = 0; index < size; index++)
    {
        cout << prefix[index] << " ";
    }

    cout << endl;

    return 0;
}