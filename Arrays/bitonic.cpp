#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int increasing[100];
    int decreasing[100];

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    increasing[0] = 1;

    for (int index = 1; index < size; index++)
    {
        if (numbers[index] > numbers[index - 1])
        {
            increasing[index] = increasing[index - 1] + 1;
        }
        else
        {
            increasing[index] = 1;
        }
    }

    decreasing[size - 1] = 1;

    for (int index = size - 2; index >= 0; index--)
    {
        if (numbers[index] > numbers[index + 1])
        {
            decreasing[index] = decreasing[index + 1] + 1;
        }
        else
        {
            decreasing[index] = 1;
        }
    }

    int maximumLength = 1;

    for (int index = 0; index < size; index++)
    {
        int currentLength =
            increasing[index] + decreasing[index] - 1;

        if (currentLength > maximumLength)
        {
            maximumLength = currentLength;
        }
    }

    cout << "Length of Longest Bitonic Subarray = "
         << maximumLength << endl;

    return 0;
}