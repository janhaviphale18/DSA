#include<iostream>
using namespace std;

void compareAndSwap(int arr[], int i, int j, bool ascending)
{
    if(ascending && arr[i] > arr[j])
    {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    if(!ascending && arr[i] < arr[j])
    {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void bitonicMerge(int arr[], int low, int count, bool ascending)
{
    if(count > 1)
    {
        int half = count / 2;

        for(int i = low; i < low + half; i++)
        {
            compareAndSwap(arr, i, i + half, ascending);
        }

        bitonicMerge(arr, low, half, ascending);
        bitonicMerge(arr, low + half, half, ascending);
    }
}

void bitonicSort(int arr[], int low, int count, bool ascending)
{
    if(count > 1)
    {
        int half = count / 2;

        bitonicSort(arr, low, half, true);
        bitonicSort(arr, low + half, half, false);

        bitonicMerge(arr, low, count, ascending);
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

    bitonicSort(arr, 0, n, true);

    cout << "\nSorted Array: ";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}