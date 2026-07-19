#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];

    cout << "Enter number of elements: ";
    cin >> size;

    if (size < 2)
    {
        cout << "Array must contain at least 2 elements." << endl;
        return 0;
    }

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];

        if (numbers[index] < 1 || numbers[index] >= size)
        {
            cout << "\nInvalid input!" << endl;
            cout << "For an array of size " << size
                 << ", every element must be between 1 and "
                 << size - 1 << "." << endl;
            return 0;
        }
    }

    // Phase 1: Find the meeting point
    int slow = numbers[0];
    int fast = numbers[0];

    do
    {
        slow = numbers[slow];
        fast = numbers[numbers[fast]];
    }
    while (slow != fast);

    // Phase 2: Find the entrance of the cycle
    slow = numbers[0];

    while (slow != fast)
    {
        slow = numbers[slow];
        fast = numbers[fast];
    }

    cout << "Duplicate Number: " << slow << endl;

    return 0;
}