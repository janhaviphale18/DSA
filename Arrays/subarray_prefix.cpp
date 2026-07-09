#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int prefix[100];
    int sum;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    prefix[0] = numbers[0];

    for (int index = 1; index < size; index++)
    {
        prefix[index] = prefix[index - 1] + numbers[index];
    }

    cout << "\nSubarray Sums:\n";

    for (int start = 0; start < size; start++)
    {
        for (int end = start; end < size; end++)
        {
            if (start == 0)
            {
                sum = prefix[end];
            }
            else
            {
                sum = prefix[end] - prefix[start - 1];
            }

            cout << "Sum of subarray (" << start + 1
                 << ", " << end + 1
                 << ") = " << sum << endl;
        }
    }

    return 0;
}