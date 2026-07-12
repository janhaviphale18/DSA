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

    int maximumReach = 0;

    for (int index = 0; index < size; index++)
    {
        if (index > maximumReach)
        {
            cout << "No" << endl;
            return 0;
        }

        if (index + numbers[index] > maximumReach)
        {
            maximumReach = index + numbers[index];
        }

        if (maximumReach >= size - 1)
        {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}