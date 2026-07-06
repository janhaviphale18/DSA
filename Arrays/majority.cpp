#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int count;
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
        count = 0;

        for (int next = 0; next < size; next++)
        {
            if (numbers[index] == numbers[next])
            {
                count++;
            }
        }

        if (count > size / 2)
        {
            cout << "Majority element: " << numbers[index] << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "No majority element found." << endl;
    }

    return 0;
}