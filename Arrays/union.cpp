#include <iostream>
using namespace std;

int main()
{
    int size1, size2;
    int first[100], second[100], result[200];
    int i = 0, j = 0, k = 0;

    cout << "Enter number of elements in first array: ";
    cin >> size1;

    cout << "Enter first sorted array: ";
    for (int index = 0; index < size1; index++)
    {
        cin >> first[index];
    }

    cout << "Enter number of elements in second array: ";
    cin >> size2;

    cout << "Enter second sorted array: ";
    for (int index = 0; index < size2; index++)
    {
        cin >> second[index];
    }

    while (i < size1 && j < size2)
    {
        if (first[i] < second[j])
        {
            if (k == 0 || result[k - 1] != first[i])
            {
                result[k] = first[i];
                k++;
            }
            i++;
        }
        else if (first[i] > second[j])
        {
            if (k == 0 || result[k - 1] != second[j])
            {
                result[k] = second[j];
                k++;
            }
            j++;
        }
        else
        {
            if (k == 0 || result[k - 1] != first[i])
            {
                result[k] = first[i];
                k++;
            }

            i++;
            j++;
        }
    }

    while (i < size1)
    {
        if (k == 0 || result[k - 1] != first[i])
        {
            result[k] = first[i];
            k++;
        }

        i++;
    }

    while (j < size2)
    {
        if (k == 0 || result[k - 1] != second[j])
        {
            result[k] = second[j];
            k++;
        }

        j++;
    }

    cout << "Union of arrays: ";

    for (int index = 0; index < k; index++)
    {
        cout << result[index] << " ";
    }

    cout << endl;

    return 0;
}