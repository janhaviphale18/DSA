#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    bool found;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    cout << "\nPrevious Greater Elements:\n";

    for (int index = 0; index < size; index++)
    {
        found = false;

        for (int previous = index - 1; previous >= 0; previous--)
        {
            if (numbers[previous] > numbers[index])
            {
                cout << numbers[index] << " -> " << numbers[previous] << endl;
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << numbers[index] << " -> -1" << endl;
        }
    }

    return 0;
}