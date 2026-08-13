#include<iostream>
using namespace std;

const int RUN = 4;

void insertionSort(int arr[], int left, int right)
{
    for(int i = left + 1; i <= right; i++)
    {
        int temp = arr[i];
        int j = i - 1;

        while(j >= left && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = temp;
    }
}

void merge(int arr[], int left, int mid, int right)
{
    int temp[100];

    int i = left;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= right)
    {
        if(arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }

        k++;
    }

    while(i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while(j <= right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for(int i = 0; i < k; i++)
    {
        arr[left + i] = temp[i];
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

    for(int i = 0; i < n; i = i + RUN)
    {
        int right = i + RUN - 1;

        if(right >= n)
        {
            right = n - 1;
        }

        insertionSort(arr, i, right);
    }

    for(int size = RUN; size < n; size = size * 2)
    {
        for(int left = 0; left < n; left = left + 2 * size)
        {
            int mid = left + size - 1;
            int right = left + 2 * size - 1;

            if(mid >= n)
            {
                continue;
            }

            if(right >= n)
            {
                right = n - 1;
            }

            merge(arr, left, mid, right);
        }
    }

    cout << "\nSorted Array: ";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}