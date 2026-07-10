#include <iostream>
using namespace std;

int main()
{
    int size1, size2;
    int first[100];
    int second[100];
    int merged[200];

    int i = 0;
    int j = 0;
    int k = 0;

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
        if (first[i] <= second[j])
        {
            merged[k] = first[i];
            i++;
        }
        else
        {
            merged[k] = second[j];
            j++;
        }

        k++;
    }

    while (i < size1)
    {
        merged[k] = first[i];
        i++;
        k++;
    }

    while (j < size2)
    {
        merged[k] = second[j];
        j++;
        k++;
    }

    cout << "Merged array: ";

    for (int index = 0; index < k; index++)
    {
        cout << merged[index] << " ";
    }

    cout << endl;

    return 0;
}