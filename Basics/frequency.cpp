#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int target;
    int count = 0;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    cout << "Enter element to find frequency: ";
    cin >> target;

    for (int index = 0; index < size; index++)
    {
        if (numbers[index] == target)
        {
            count++;
        }
    }

    cout << "Frequency of " << target << " is: " << count << endl;

    return 0;
}