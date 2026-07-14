#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int zeroCount = 0;
    int oneCount = 0;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter binary array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];

        if (numbers[index] == 0)
        {
            zeroCount++;
        }
        else
        {
            oneCount++;
        }
    }

    int index = 0;

    while (zeroCount > 0)
    {
        numbers[index] = 0;
        index++;
        zeroCount--;
    }

    while (oneCount > 0)
    {
        numbers[index] = 1;
        index++;
        oneCount--;
    }

    cout << "Sorted Binary Array: ";

    for (int index = 0; index < size; index++)
    {
        cout << numbers[index] << " ";
    }

    cout << endl;

    return 0;
}