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

    int index = 0;

    while (index < size)
    {
        if (numbers[index] > 0 &&
            numbers[index] <= size &&
            numbers[index] != numbers[numbers[index] - 1])
        {
            int temp = numbers[index];
            numbers[index] = numbers[temp - 1];
            numbers[temp - 1] = temp;
        }
        else
        {
            index++;
        }
    }

    int answer = size + 1;

    for (int index = 0; index < size; index++)
    {
        if (numbers[index] != index + 1)
        {
            answer = index + 1;
            break;
        }
    }

    cout << "First Missing Positive: " << answer << endl;

    return 0;
}