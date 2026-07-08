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

    cout << "\nSubarray Sums:\n";

    for (int start = 0; start < size; start++)
    {
        for (int end = start; end < size; end++)
        {
            int sum = 0;

            for (int index = start; index <= end; index++)
            {
                sum = sum + numbers[index];
            }

            cout << "Sum of subarray (" << start + 1 << ", " << end + 1 << ") = " << sum << endl;
        }
    }

    return 0;
}