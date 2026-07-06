#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    bool consecutive = true;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    for (int index = 0; index < size - 1; index++)
    {
        if (numbers[index + 1] != numbers[index] + 1)
        {
            consecutive = false;
            break;
        }
    }

    if (consecutive)
    {
        cout << "Array contains consecutive elements." << endl;
    }
    else
    {
        cout << "Array does not contain consecutive elements." << endl;
    }

    return 0;
}