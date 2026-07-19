#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];

    cout << "Enter number of elements: ";
    cin >> size;

    if (size <= 0)
    {
        cout << "Array cannot be empty." << endl;
        return 0;
    }

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    int candidate1 = 0;
    int candidate2 = 1;
    int count1 = 0;
    int count2 = 0;

    for (int index = 0; index < size; index++)
    {
        if (numbers[index] == candidate1)
        {
            count1++;
        }
        else if (numbers[index] == candidate2)
        {
            count2++;
        }
        else if (count1 == 0)
        {
            candidate1 = numbers[index];
            count1 = 1;
        }
        else if (count2 == 0)
        {
            candidate2 = numbers[index];
            count2 = 1;
        }
        else
        {
            count1--;
            count2--;
        }
    }

    count1 = 0;
    count2 = 0;

    for (int index = 0; index < size; index++)
    {
        if (numbers[index] == candidate1)
        {
            count1++;
        }
        else if (numbers[index] == candidate2)
        {
            count2++;
        }
    }

    bool found = false;

    cout << "Majority Elements: ";

    if (count1 > size / 3)
    {
        cout << candidate1 << " ";
        found = true;
    }

    if (count2 > size / 3)
    {
        cout << candidate2 << " ";
        found = true;
    }

    if (!found)
    {
        cout << "No Majority Element";
    }

    cout << endl;

    return 0;
}