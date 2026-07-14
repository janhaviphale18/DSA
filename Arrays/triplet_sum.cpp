#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int target;
    bool found = false;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    cout << "Enter target sum: ";
    cin >> target;

    for (int first = 0; first < size - 2; first++)
    {
        for (int second = first + 1; second < size - 1; second++)
        {
            for (int third = second + 1; third < size; third++)
            {
                if (numbers[first] + numbers[second] + numbers[third] == target)
                {
                    cout << "Triplet Found:" << endl;
                    cout << numbers[first] << " "
                         << numbers[second] << " "
                         << numbers[third] << endl;

                    found = true;
                    break;
                }
            }

            if (found)
            {
                break;
            }
        }

        if (found)
        {
            break;
        }
    }

    if (!found)
    {
        cout << "No triplet found." << endl;
    }

    return 0;
}