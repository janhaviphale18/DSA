#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int k;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    cout << "Enter window size: ";
    cin >> k;

    if (k > size || k <= 0)
    {
        cout << "Invalid window size." << endl;
        return 0;
    }

    int currentSum = 0;

    for (int index = 0; index < k; index++)
    {
        currentSum += numbers[index];
    }

    int maximumSum = currentSum;
    int startIndex = 0;

    for (int index = k; index < size; index++)
    {
        currentSum = currentSum - numbers[index - k] + numbers[index];

        if (currentSum > maximumSum)
        {
            maximumSum = currentSum;
            startIndex = index - k + 1;
        }
    }

    double maximumAverage = (double)maximumSum / k;

    cout << "Maximum Average: " << maximumAverage << endl;

    cout << "Subarray: ";

    for (int index = startIndex; index < startIndex + k; index++)
    {
        cout << numbers[index] << " ";
    }

    cout << endl;

    return 0;
}