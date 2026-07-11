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

    cout << "\nNext Smaller Elements:\n";

    for (int index = 0; index < size; index++)
    {
        found = false;

        for (int next = index + 1; next < size; next++)
        {
            if (numbers[next] < numbers[index])
            {
                cout << numbers[index] << " -> " << numbers[next] << endl;
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