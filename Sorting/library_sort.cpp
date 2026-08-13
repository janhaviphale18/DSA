#include<iostream>
using namespace std;

void librarySort(int arr[], int n)
{
    int sorted[200];
    int size = 0;

    for(int i = 0; i < n; i++)
    {
        int position = 0;

        while(position < size && sorted[position] < arr[i])
        {
            position++;
        }

        for(int j = size; j > position; j--)
        {
            sorted[j] = sorted[j - 1];
        }

        sorted[position] = arr[i];
        size++;
    }

    for(int i = 0; i < n; i++)
    {
        arr[i] = sorted[i];
    }
}

int main()
{
    int n;
    int arr[100];

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the elements: ";

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    librarySort(arr, n);

    cout << "\nSorted Array: ";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}