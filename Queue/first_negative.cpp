#include <iostream>
#include <queue>
using namespace std;

void firstNegative(int arr[], int n, int k)
{
    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        // Store index of negative element
        if (arr[i] < 0)
        {
            q.push(i);
        }

        // Remove elements outside current window
        while (!q.empty() && q.front() <= i - k)
        {
            q.pop();
        }

        // Print result for complete window
        if (i >= k - 1)
        {
            if (q.empty())
            {
                cout << "0 ";
            }
            else
            {
                cout << arr[q.front()] << " ";
            }
        }
    }

    cout << endl;
}

int main()
{
    int arr[] = {12, -1, -7, 8, -15, 30, 16, 28};

    int n = 8;
    int k = 3;

    cout << "First Negative: ";

    firstNegative(arr, n, k);

    return 0;
}