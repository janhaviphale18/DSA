#include<iostream>
using namespace std;

int main()
{
    int n;
    int arr[100];
    int count[100] = {0};

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the elements: ";

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int maxValue = arr[0];

    for(int i = 1; i < n; i++)
    {
        if(arr[i] > maxValue)
        {
            maxValue = arr[i];
        }
    }

    for(int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }

    cout << "\nSorted Array: ";

    for(int i = 0; i <= maxValue; i++)
    {
        while(count[i] > 0)
        {
            cout << i << " ";
            count[i]--;
        }
    }

    cout << endl;

    return 0;
}