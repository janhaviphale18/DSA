#include<iostream>
using namespace std;

void swapElements(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void heapify(int arr[], int start, int root, int size)
{
    int largest = root;
    int left = 2 * (root - start) + start + 1;
    int right = left + 1;

    if(left < size && arr[left] > arr[largest])
    {
        largest = left;
    }

    if(right < size && arr[right] > arr[largest])
    {
        largest = right;
    }

    if(largest != root)
    {
        swapElements(arr[root], arr[largest]);

        heapify(arr, start, largest, size);
    }
}

void smoothSort(int arr[], int n)
{
    for(int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, 0, i, n);
    }

    for(int i = n - 1; i > 0; i--)
    {
        swapElements(arr[0], arr[i]);

        heapify(arr, 0, 0, i);
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

    smoothSort(arr, n);

    cout << "\nSorted Array: ";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}