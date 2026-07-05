#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int left;
    int right;
    int temporary;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    left = 0;
    right = size - 1;

    while (left < right)
    {
        temporary = numbers[left];
        numbers[left] = numbers[right];
        numbers[right] = temporary;

        left++;
        right--;
    }

    cout << "Reversed array: ";

    for (int index = 0; index < size; index++)
    {
        cout << numbers[index] << " ";
    }

    cout << endl;

    return 0;
}