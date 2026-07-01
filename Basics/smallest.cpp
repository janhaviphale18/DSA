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

    int smallest = numbers[0];

    for (int index = 1; index < size; index++)
    {
        if (numbers[index] < smallest)
        {
            smallest = numbers[index];
        }
    }

    cout << "Smallest element: " << smallest << endl;

    return 0;
}