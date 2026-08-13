#include<iostream>
using namespace std;

void stoogeSort(int arr[], int low, int high)
{
    if(arr[low] > arr[high])
    {
        int temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
    }

    if(high - low + 1 > 2)
    {
        int third = (high - low + 1) / 3;

        stoogeSort(arr, low, high - third);
        stoogeSort(arr, low + third, high);
        stoogeSort(arr, low, high - third);
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

    stoogeSort(arr, 0, n - 1);

    cout << "\nSorted Array: ";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}