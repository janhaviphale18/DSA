#include <iostream>
using namespace std;

int main()
{
    int size1, size2, size3;
    int first[100], second[100], third[100];
    int i = 0, j = 0, k = 0;
    bool found = false;

    cout << "Enter size of first array: ";
    cin >> size1;

    cout << "Enter first sorted array: ";

    for (int index = 0; index < size1; index++)
    {
        cin >> first[index];
    }

    cout << "Enter size of second array: ";
    cin >> size2;

    cout << "Enter second sorted array: ";

    for (int index = 0; index < size2; index++)
    {
        cin >> second[index];
    }

    cout << "Enter size of third array: ";
    cin >> size3;

    cout << "Enter third sorted array: ";

    for (int index = 0; index < size3; index++)
    {
        cin >> third[index];
    }

    while (i < size1 && j < size2 && k < size3)
    {
        if (first[i] == second[j] && second[j] == third[k])
        {
            if (!found)
            {
                cout << "Common Elements:" << endl;
                found = true;
            }

            cout << first[i] << " ";

            i++;
            j++;
            k++;
        }
        else if (first[i] < second[j])
        {
            i++;
        }
        else if (second[j] < third[k])
        {
            j++;
        }
        else
        {
            k++;
        }
    }

    if (!found)
    {
        cout << "No common elements found." << endl;
    }

    return 0;
}