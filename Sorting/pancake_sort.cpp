#include<iostream>
using namespace std;

void reverseArray(int arr[], int start, int end)
{
    while(start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

int findMaximum(int arr[], int n)
{
    int maxIndex = 0;

    for(int i = 1; i < n; i++)
    {
        if(arr[i] > arr[maxIndex])
        {
            maxIndex = i;
        }
    }

    return maxIndex;
}

void pancakeSort(int arr[], int n)
{
    for(int currentSize = n; currentSize > 1; currentSize--)
    {
        int maxIndex = findMaximum(arr, currentSize);

        if(maxIndex == currentSize - 1)
        {
            continue;
        }

        if(maxIndex != 0)
        {
            reverseArray(arr, 0, maxIndex);
        }

        reverseArray(arr, 0, currentSize - 1);
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

    pancakeSort(arr, n);

    cout << "\nSorted Array: ";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}