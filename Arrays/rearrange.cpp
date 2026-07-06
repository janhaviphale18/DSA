#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int result[100];
    int position = 0;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    for (int index = 0; index < size; index++)
    {
        if (numbers[index] < 0)
        {
            result[position] = numbers[index];
            position++;
        }
    }

    for (int index = 0; index < size; index++)
    {
        if (numbers[index] >= 0)
        {
            result[position] = numbers[index];
            position++;
        }
    }

    cout << "Rearranged array: ";

    for (int index = 0; index < size; index++)
    {
        cout << result[index] << " ";
    }

    cout << endl;

    return 0;
}