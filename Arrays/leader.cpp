#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    bool isLeader;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    cout << "Leader elements: ";

    for (int index = 0; index < size; index++)
    {
        isLeader = true;

        for (int next = index + 1; next < size; next++)
        {
            if (numbers[next] > numbers[index])
            {
                isLeader = false;
                break;
            }
        }

        if (isLeader)
        {
            cout << numbers[index] << " ";
        }
    }

    cout << endl;

    return 0;
}