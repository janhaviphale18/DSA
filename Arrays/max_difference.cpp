#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int maximumDifference;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    maximumDifference = numbers[1] - numbers[0];

    for (int first = 0; first < size - 1; first++)
    {
        for (int second = first + 1; second < size; second++)
        {
            int difference = numbers[second] - numbers[first];

            if (difference > maximumDifference)
            {
                maximumDifference = difference;
            }
        }
    }

    cout << "Maximum difference: " << maximumDifference << endl;

    return 0;
}