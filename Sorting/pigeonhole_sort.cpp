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

    int minValue = arr[0];
    int maxValue = arr[0];

    for(int i = 1; i < n; i++)
    {
        if(arr[i] < minValue)
        {
            minValue = arr[i];
        }

        if(arr[i] > maxValue)
        {
            maxValue = arr[i];
        }
    }

    int range = maxValue - minValue + 1;
    int count[100] = {0};

    for(int i = 0; i < n; i++)
    {
        count[arr[i] - minValue]++;
    }

    int index = 0;

    for(int i = 0; i < range; i++)
    {
        while(count[i] > 0)
        {
            arr[index] = i + minValue;
            index++;
            count[i]--;
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