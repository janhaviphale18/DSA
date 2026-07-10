#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int prefix[100];
    bool found = false;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    prefix[0] = numbers[0];

    for (int index = 1; index < size; index++)
    {
        prefix[index] = prefix[index - 1] + numbers[index];
    }

    int totalSum = prefix[size - 1];

    for (int index = 0; index < size; index++)
    {
        int leftSum;
        int rightSum;

        if (index == 0)
        {
            leftSum = 0;
        }
        else
        {
            leftSum = prefix[index - 1];
        }

        rightSum = totalSum - prefix[index];

        if (leftSum == rightSum)
        {
            cout << "Equilibrium Index: " << index + 1 << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "No Equilibrium Index found." << endl;
    }

    return 0;
}