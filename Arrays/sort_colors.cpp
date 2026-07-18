#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements (0, 1, 2): ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];

        if (numbers[index] < 0 || numbers[index] > 2)
        {
            cout << "Invalid input. Enter only 0, 1, and 2." << endl;
            return 0;
        }
    }

    int low = 0;
    int mid = 0;
    int high = size - 1;

    while (mid <= high)
    {
        if (numbers[mid] == 0)
        {
            int temp = numbers[low];
            numbers[low] = numbers[mid];
            numbers[mid] = temp;

            low++;
            mid++;
        }
        else if (numbers[mid] == 1)
        {
            mid++;
        }
        else
        {
            int temp = numbers[mid];
            numbers[mid] = numbers[high];
            numbers[high] = temp;

            high--;
        }
    }

    cout << "Sorted Array: ";

    for (int index = 0; index < size; index++)
    {
        cout << numbers[index] << " ";
    }

    cout << endl;

    return 0;
}