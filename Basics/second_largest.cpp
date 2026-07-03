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

    int largest = numbers[0];
    int secondLargest = numbers[0];

    for (int index = 1; index < size; index++)
    {
        if (numbers[index] > largest)
        {
            secondLargest = largest;
            largest = numbers[index];
        }
        else if (numbers[index] > secondLargest && numbers[index] != largest)
        {
            secondLargest = numbers[index];
        }
    }

    cout << "Second largest element: " << secondLargest << endl;

    return 0;
}