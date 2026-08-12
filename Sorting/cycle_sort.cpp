#include<iostream>
using namespace std;

int main()
{
    int n;
    int arr[100];

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter distinct elements: ";

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for(int cycleStart = 0; cycleStart < n - 1; cycleStart++)
    {
        int item = arr[cycleStart];
        int position = cycleStart;

        for(int i = cycleStart + 1; i < n; i++)
        {
            if(arr[i] < item)
            {
                position++;
            }
        }

        if(position == cycleStart)
        {
            continue;
        }

        while(item == arr[position])
        {
            position++;
        }

        int temp = item;
        item = arr[position];
        arr[position] = temp;

        while(position != cycleStart)
        {
            position = cycleStart;

            for(int i = cycleStart + 1; i < n; i++)
            {
                if(arr[i] < item)
                {
                    position++;
                }
            }

            while(item == arr[position])
            {
                position++;
            }

            temp = item;
            item = arr[position];
            arr[position] = temp;
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