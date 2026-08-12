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

    int gap = n;
    bool swapped = true;

    while(gap != 1 || swapped)
    {
        gap = gap * 10 / 13;

        if(gap < 1)
        {
            gap = 1;
        }

        swapped = false;

        for(int i = 0; i + gap < n; i++)
        {
            if(arr[i] > arr[i + gap])
            {
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;

                swapped = true;
            }
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