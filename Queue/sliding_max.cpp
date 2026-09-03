#include <iostream>
#include <deque>
using namespace std;

int main()
{
    int n, k;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter window size: ";
    cin >> k;

    if (k <= 0 || k > n)
    {
        cout << "Invalid window size";
        return 0;
    }

    deque<int> dq;

    cout << "Sliding Window Maximum: ";

    for (int i = 0; i < n; i++)
    {
        // Remove elements outside the current window
        while (!dq.empty() && dq.front() <= i - k)
        {
            dq.pop_front();
        }

        // Remove elements smaller than current element
        while (!dq.empty() && arr[dq.back()] <= arr[i])
        {
            dq.pop_back();
        }

        dq.push_back(i);

        // Window is complete
        if (i >= k - 1)
        {
            cout << arr[dq.front()] << " ";
        }
    }

    return 0;
}