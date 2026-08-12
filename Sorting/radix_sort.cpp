#include<iostream>
using namespace std;

void countingSort(int arr[], int n, int place)
{
    int output[100];
    int count[10] = {0};

    for(int i = 0; i < n; i++)
    {
        int digit = (arr[i] / place) % 10;
        count[digit]++;
    }

    for(int i = 1; i < 10; i++)
    {
        count[i] = count[i] + count[i - 1];
    }

    for(int i = n - 1; i >= 0; i--)
    {
        int digit = (arr[i] / place) % 10;

        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for(int i = 0; i < n; i++)
    {
        arr[i] = output[i];
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

    int maxValue = arr[0];

    for(int i = 1; i < n; i++)
    {
        if(arr[i] > maxValue)
        {
            maxValue = arr[i];
        }
    }

    for(int place = 1; maxValue / place > 0; place = place * 10)
    {
        countingSort(arr, n, place);
    }

    cout << "\nSorted Array: ";

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}