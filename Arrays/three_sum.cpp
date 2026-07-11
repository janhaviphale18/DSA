#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    bool found = false;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    for (int first = 0; first < size - 2; first++)
    {
        for (int second = first + 1; second < size - 1; second++)
        {
            for (int third = second + 1; third < size; third++)
            {
                if (numbers[first] + numbers[second] + numbers[third] == 0)
                {
                    if (!found)
                    {
                        cout << "Triplets are:" << endl;
                        found = true;
                    }

                    cout << numbers[first] << " "
                         << numbers[second] << " "
                         << numbers[third] << endl;
                }
            }
        }
    }

    if (!found)
    {
        cout << "No triplets found." << endl;
    }

    return 0;
}