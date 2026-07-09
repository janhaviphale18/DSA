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

    int currentSum = 0;
    int maximumSum = numbers[0];

    for (int index = 0; index < size; index++)
    {
        currentSum = currentSum + numbers[index];

        if (currentSum > maximumSum)
        {
            maximumSum = currentSum;
        }

        if (currentSum < 0)
        {
            currentSum = 0;
        }
    }

    cout << "Maximum Subarray Sum: " << maximumSum << endl;

    return 0;
}