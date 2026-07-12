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

    for (int first = 0; first < size - 3; first++)
    {
        for (int second = first + 1; second < size - 2; second++)
        {
            for (int third = second + 1; third < size - 1; third++)
            {
                for (int fourth = third + 1; fourth < size; fourth++)
                {
                    if (numbers[first] + numbers[second] +
                        numbers[third] + numbers[fourth] == 0)
                    {
                        if (!found)
                        {
                            cout << "Quadruplets are:" << endl;
                            found = true;
                        }

                        cout << numbers[first] << " "
                             << numbers[second] << " "
                             << numbers[third] << " "
                             << numbers[fourth] << endl;
                    }
                }
            }
        }
    }

    if (!found)
    {
        cout << "No quadruplets found." << endl;
    }

    return 0;
}