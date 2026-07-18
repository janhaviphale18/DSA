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

    int pivot = -1;

    for (int index = size - 2; index >= 0; index--)
    {
        if (numbers[index] < numbers[index + 1])
        {
            pivot = index;
            break;
        }
    }

    if (pivot != -1)
    {
        for (int index = size - 1; index > pivot; index--)
        {
            if (numbers[index] > numbers[pivot])
            {
                int temp = numbers[index];
                numbers[index] = numbers[pivot];
                numbers[pivot] = temp;
                break;
            }
        }
    }

    int left = pivot + 1;
    int right = size - 1;

    while (left < right)
    {
        int temp = numbers[left];
        numbers[left] = numbers[right];
        numbers[right] = temp;

        left++;
        right--;
    }

    cout << "Next Permutation:\n";

    for (int index = 0; index < size; index++)
    {
        cout << numbers[index] << " ";
    }

    cout << endl;

    return 0;
}