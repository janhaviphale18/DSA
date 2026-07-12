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

    if (size == 1)
    {
        cout << "Minimum Jumps: 0" << endl;
        return 0;
    }

    if (numbers[0] == 0)
    {
        cout << "Cannot reach the last index." << endl;
        return 0;
    }

    int maximumReach = numbers[0];
    int steps = numbers[0];
    int jumps = 1;

    for (int index = 1; index < size; index++)
    {
        if (index == size - 1)
        {
            cout << "Minimum Jumps: " << jumps << endl;
            return 0;
        }

        if (index + numbers[index] > maximumReach)
        {
            maximumReach = index + numbers[index];
        }

        steps--;

        if (steps == 0)
        {
            jumps++;

            if (index >= maximumReach)
            {
                cout << "Cannot reach the last index." << endl;
                return 0;
            }

            steps = maximumReach - index;
        }
    }

    cout << "Cannot reach the last index." << endl;

    return 0;
}