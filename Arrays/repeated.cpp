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

    for (int index = 0; index < size; index++)
    {
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
            cout << "Repeated Number: "
                 << numbers[index] << endl;
            return 0;
        }
    }

    cout << "No repeated number found." << endl;

    return 0;
}