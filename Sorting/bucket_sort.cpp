#include<iostream>
using namespace std;

int main()
{
    int n;
    float arr[100];
    float bucket[10][100];
    int count[10] = {0};

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the elements between 0 and 1: ";

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for(int i = 0; i < n; i++)
    {
        int index = arr[i] * 10;

        if(index == 10)
        {
            index = 9;
        }

        bucket[index][count[index]] = arr[i];
        count[index]++;
    }

    for(int i = 0; i < 10; i++)
    {
        for(int j = 1; j < count[i]; j++)
        {
            float key = bucket[i][j];
            int k = j - 1;

            while(k >= 0 && bucket[i][k] > key)
            {
                bucket[i][k + 1] = bucket[i][k];
                k--;
            }

            bucket[i][k + 1] = key;
        }
    }

    int position = 0;

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < count[i]; j++)
        {
            arr[position] = bucket[i][j];
            position++;
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