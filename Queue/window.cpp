#include <iostream>
#include <deque>
using namespace std;

void findMaximum(int arr[], int n, int k)
{
    deque<int> dq;

    for (int i = 0; i < n; i++)
    {
        // Remove elements outside the current window
        while (!dq.empty() && dq.front() <= i - k)
        {
            dq.pop_front();
        }

        // Remove smaller elements from the rear
        while (!dq.empty() && arr[dq.back()] <= arr[i])
        {
            dq.pop_back();
        }

        dq.push_back(i);

        // Start printing after the first complete window
        if (i >= k - 1)
        {
            cout << arr[dq.front()] << " ";
        }
    }

    cout << endl;
}

int main()
{
    int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};

    int n = 8;
    int k = 3;

    cout << "Window Maximum: ";

    findMaximum(arr, n, k);

    return 0;
}