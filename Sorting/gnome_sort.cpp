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

    int i = 1;

    while(i < n)
    {
        if(i == 0 || arr[i] >= arr[i - 1])
        {
            i++;
        }
        else
        {
            int temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;

            i--;
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