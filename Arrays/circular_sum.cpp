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

    int totalSum = 0;

    for (int index = 0; index < size; index++)
    {
        totalSum += numbers[index];
    }

    int currentMaximum = numbers[0];
    int maximumSum = numbers[0];

    for (int index = 1; index < size; index++)
    {
        if (currentMaximum + numbers[index] > numbers[index])
        {
            currentMaximum = currentMaximum + numbers[index];
        }
        else
        {
            currentMaximum = numbers[index];
        }

        if (currentMaximum > maximumSum)
        {
            maximumSum = currentMaximum;
        }
    }

    int currentMinimum = numbers[0];
    int minimumSum = numbers[0];

    for (int index = 1; index < size; index++)
    {
        if (currentMinimum + numbers[index] < numbers[index])
        {
            currentMinimum = currentMinimum + numbers[index];
        }
        else
        {
            currentMinimum = numbers[index];
        }

        if (currentMinimum < minimumSum)
        {
            minimumSum = currentMinimum;
        }
    }

    if (maximumSum < 0)
    {
        cout << "Maximum Circular Sum: " << maximumSum << endl;
    }
    else
    {
        int circularSum = totalSum - minimumSum;

        if (circularSum > maximumSum)
        {
            cout << "Maximum Circular Sum: " << circularSum << endl;
        }
        else
        {
            cout << "Maximum Circular Sum: " << maximumSum << endl;
        }
    }

    return 0;
}