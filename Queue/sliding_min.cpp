#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int main()
{
    int n, k;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

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

        // Remove smaller elements from the rear
        while (!dq.empty() && arr[dq.back()] <= arr[i])
        {
            dq.pop_back();
        }

        dq.push_back(i);

        // Print maximum when window is complete
        if (i >= k - 1)
        {
            cout << arr[dq.front()] << " ";
        }
    }

    return 0;
}