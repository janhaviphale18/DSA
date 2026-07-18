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

    int maximumLength = 0;

    for (int peak = 1; peak < size - 1; peak++)
    {
        if (numbers[peak] > numbers[peak - 1] &&
            numbers[peak] > numbers[peak + 1])
        {
            int left = peak;
            int right = peak;

            while (left > 0 &&
                   numbers[left] > numbers[left - 1])
            {
                left--;
            }

            while (right < size - 1 &&
                   numbers[right] > numbers[right + 1])
            {
                right++;
            }

            int length = right - left + 1;

            if (length > maximumLength)
            {
                maximumLength = length;
            }
        }
    }

    cout << "Length of Longest Mountain: "
         << maximumLength << endl;

    return 0;
}