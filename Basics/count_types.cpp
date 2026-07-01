#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];

    int positiveCount = 0;
    int negativeCount = 0;
    int zeroCount = 0;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    for (int index = 0; index < size; index++)
    {
        if (numbers[index] > 0)
        {
            positiveCount++;
        }
        else if (numbers[index] < 0)
        {
            negativeCount++;
        }
        else
        {
            zeroCount++;
        }
    }

    cout << "Positive: " << positiveCount << endl;
    cout << "Negative: " << negativeCount << endl;
    cout << "Zero: " << zeroCount << endl;

    return 0;
}