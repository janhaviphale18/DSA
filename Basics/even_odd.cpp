#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int evenCount = 0;
    int oddCount = 0;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    for (int index = 0; index < size; index++)
    {
        if (numbers[index] % 2 == 0)
        {
            evenCount++;
        }
        else
        {
            oddCount++;
        }
    }

    cout << "Even elements: " << evenCount << endl;
    cout << "Odd elements: " << oddCount << endl;

    return 0;
}