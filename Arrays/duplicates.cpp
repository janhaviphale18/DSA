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

    for (int index = 0; index < size; index++)
    {
        bool alreadyPrinted = false;

        for (int previous = 0; previous < index; previous++)
        {
            if (numbers[index] == numbers[previous])
            {
                alreadyPrinted = true;
                break;
            }
        }

        if (alreadyPrinted)
        {
            continue;
        }

        int count = 0;

        for (int search = 0; search < size; search++)
        {
            if (numbers[index] == numbers[search])
            {
                count++;
            }
        }

        if (count > 1)
        {
            if (!found)
            {
                cout << "Duplicate Elements:" << endl;
                found = true;
            }

            cout << numbers[index] << endl;
        }
    }

    if (!found)
    {
        cout << "No duplicate elements found." << endl;
    }

    return 0;
}