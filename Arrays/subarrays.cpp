#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int maximumLength = 0;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter binary array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];

        if (numbers[index] != 0 && numbers[index] != 1)
        {
            cout << "Invalid input. Enter only 0 and 1." << endl;
            return 0;
        }
    }

    for (int start = 0; start < size; start++)
    {
        int zeroCount = 0;
        int oneCount = 0;

        for (int end = start; end < size; end++)
        {
            if (numbers[end] == 0)
            {
                zeroCount++;
            }
            else
            {
                oneCount++;
            }

            if (zeroCount == oneCount)
            {
                int length = end - start + 1;

                if (length > maximumLength)
                {
                    maximumLength = length;
                }
            }
        }
    }

    cout << "Length of Longest Subarray: "
         << maximumLength << endl;

    return 0;
}