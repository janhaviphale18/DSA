#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int prefix[100];
    int suffix[100];
    int answer[100];

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    prefix[0] = 1;

    for (int index = 1; index < size; index++)
    {
        prefix[index] = prefix[index - 1] * numbers[index - 1];
    }

    suffix[size - 1] = 1;

    for (int index = size - 2; index >= 0; index--)
    {
        suffix[index] = suffix[index + 1] * numbers[index + 1];
    }

    for (int index = 0; index < size; index++)
    {
        answer[index] = prefix[index] * suffix[index];
    }

    cout << "Product Array: ";

    for (int index = 0; index < size; index++)
    {
        cout << answer[index] << " ";
    }

    cout << endl;

    return 0;
}