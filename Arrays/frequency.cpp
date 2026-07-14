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

    cout << "\nElement\tFrequency\n";

    for (int index = 0; index < size; index++)
    {
        bool alreadyCounted = false;

        for (int previous = 0; previous < index; previous++)
        {
            if (numbers[index] == numbers[previous])
            {
                alreadyCounted = true;
                break;
            }
        }

        if (alreadyCounted)
        {
            continue;
        }

        int count = 1;

        for (int next = index + 1; next < size; next++)
        {
            if (numbers[index] == numbers[next])
            {
                count++;
            }
        }

        cout << numbers[index] << "\t" << count << endl;
    }

    return 0;
}