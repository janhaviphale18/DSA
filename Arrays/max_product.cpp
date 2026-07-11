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

    int currentMaximum = numbers[0];
    int currentMinimum = numbers[0];
    int maximumProduct = numbers[0];

    for (int index = 1; index < size; index++)
    {
        if (numbers[index] < 0)
        {
            int temp = currentMaximum;
            currentMaximum = currentMinimum;
            currentMinimum = temp;
        }

        if (numbers[index] > currentMaximum * numbers[index])
        {
            currentMaximum = numbers[index];
        }
        else
        {
            currentMaximum = currentMaximum * numbers[index];
        }

        if (numbers[index] < currentMinimum * numbers[index])
        {
            currentMinimum = numbers[index];
        }
        else
        {
            currentMinimum = currentMinimum * numbers[index];
        }

        if (currentMaximum > maximumProduct)
        {
            maximumProduct = currentMaximum;
        }
    }

    cout << "Maximum Product: "
         << maximumProduct << endl;

    return 0;
}