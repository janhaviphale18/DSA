#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int longestLength = 1;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    for (int index = 0; index < size; index++)
    {
        int currentValue = numbers[index];
        int currentLength = 1;

        while (true)
        {
            bool found = false;

            for (int search = 0; search < size; search++)
            {
                if (numbers[search] == currentValue + 1)
                {
                    found = true;
                    currentValue++;
                    currentLength++;
                    break;
                }
            }

            if (!found)
            {
                break;
            }
        }

        if (currentLength > longestLength)
        {
            longestLength = currentLength;
        }
    }

    cout << "Length of longest consecutive sequence: "
         << longestLength << endl;

    return 0;
}