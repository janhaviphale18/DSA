#include<iostream>
using namespace std;

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

    for(int gap = n / 2; gap > 0; gap = gap / 2)
    {
        for(int i = gap; i < n; i++)
        {
            int key = arr[i];
            int j = i;

            while(j >= gap && arr[j - gap] > key)
            {
                arr[j] = arr[j - gap];
                j = j - gap;
            }

            arr[j] = key;
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