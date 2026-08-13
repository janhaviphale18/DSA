#include<iostream>
using namespace std;

void mergeArrays(int result[], int resultSize, int strand[], int strandSize)
{
    int temp[100];

    int i = 0;
    int j = 0;
    int k = 0;

    while(i < resultSize && j < strandSize)
    {
        if(result[i] <= strand[j])
        {
            temp[k] = result[i];
            i++;
        }
        else
        {
            temp[k] = strand[j];
            j++;
        }

        k++;
    }

    while(i < resultSize)
    {
        temp[k] = result[i];
        i++;
        k++;
    }

    while(j < strandSize)
    {
        temp[k] = strand[j];
        j++;
        k++;
    }

    for(int i = 0; i < k; i++)
    {
        result[i] = temp[i];
    }
}

int main()
{
    int n;
    int arr[100];
    int result[100];
    int resultSize = 0;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the elements: ";

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int remaining = n;

    while(remaining > 0)
    {
        int strand[100];
        int strandSize = 0;

        int newArr[100];
        int newSize = 0;

        int last = -1;

        for(int i = 0; i < n; i++)
        {
            if(arr[i] != -1)
            {
                if(strandSize == 0 || arr[i] >= last)
                {
                    strand[strandSize] = arr[i];
                    last = arr[i];
                    strandSize++;

                    arr[i] = -1;
                    remaining--;
                }
                else
                {
                    newArr[newSize] = arr[i];
                    newSize++;
                }
            }
        }

        for(int i = 0; i < newSize; i++)
        {
            arr[i] = newArr[i];
        }

        for(int i = newSize; i < n; i++)
        {
            arr[i] = -1;
        }

        mergeArrays(result, resultSize, strand, strandSize);

        resultSize = resultSize + strandSize;
    }

    cout << "\nSorted Array: ";

    for(int i = 0; i < resultSize; i++)
    {
        cout << result[i] << " ";
    }

    cout << endl;

    return 0;
}