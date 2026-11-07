#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
using namespace std;

class SlidingMedian
{
    priority_queue<long long> maxHeap;

    priority_queue<long long,
                   vector<long long>,
                   greater<long long>> minHeap;

    unordered_map<long long, int> delayed;

    int smallSize;
    int largeSize;

    // Remove expired elements from Max Heap.
    void pruneMax()
    {
        while (!maxHeap.empty())
        {
            long long value = maxHeap.top();

            if (delayed[value] > 0)
            {
                delayed[value]--;
                maxHeap.pop();
            }
            else
            {
                break;
            }
        }
    }

    // Remove expired elements from Min Heap.
    void pruneMin()
    {
        while (!minHeap.empty())
        {
            long long value = minHeap.top();

            if (delayed[value] > 0)
            {
                delayed[value]--;
                minHeap.pop();
            }
            else
            {
                break;
            }
        }
    }

    // Maintain the balance between both heaps.
    void balance()
    {
        if (smallSize > largeSize + 1)
        {
            pruneMax();

            long long value = maxHeap.top();
            maxHeap.pop();

            minHeap.push(value);

            smallSize--;
            largeSize++;

            pruneMax();
        }
        else if (smallSize < largeSize)
        {
            pruneMin();

            long long value = minHeap.top();
            minHeap.pop();

            maxHeap.push(value);

            largeSize--;
            smallSize++;

            pruneMin();
        }
    }

public:

    SlidingMedian()
    {
        smallSize = 0;
        largeSize = 0;
    }

    // Insert a new element.
    void insert(long long value)
    {
        pruneMax();

        if (maxHeap.empty() || value <= maxHeap.top())
        {
            maxHeap.push(value);
            smallSize++;
        }
        else
        {
            minHeap.push(value);
            largeSize++;
        }

        balance();
    }

    // Remove an expired element.
    void remove(long long value)
    {
        delayed[value]++;

        pruneMax();

        if (!maxHeap.empty() && value <= maxHeap.top())
        {
            smallSize--;

            if (!maxHeap.empty() && value == maxHeap.top())
            {
                pruneMax();
            }
        }
        else
        {
            largeSize--;

            if (!minHeap.empty() && value == minHeap.top())
            {
                pruneMin();
            }
        }

        balance();
    }

    // Calculate the median.
    double getMedian()
    {
        pruneMax();
        pruneMin();

        if (smallSize > largeSize)
        {
            return maxHeap.top();
        }

        return ((double)maxHeap.top() +
                (double)minHeap.top()) / 2.0;
    }
};

int main()
{
    int n, k;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n < 1 || n > 1000)
    {
        cout << "Invalid array size!" << endl;
        return 0;
    }

    long long arr[1000];

    cout << "Enter array elements:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter window size: ";
    cin >> k;

    if (k < 1 || k > n)
    {
        cout << "Invalid window size!" << endl;
        return 0;
    }

    SlidingMedian sm;

    cout << "\nSliding Window Medians:\n";

    // Insert the first K elements.
    for (int i = 0; i < k; i++)
    {
        sm.insert(arr[i]);
    }

    cout << sm.getMedian();

    // Slide the window through the remaining elements.
    for (int i = k; i < n; i++)
    {
        // Remove the element leaving the window.
        sm.remove(arr[i - k]);

        // Insert the new element.
        sm.insert(arr[i]);

        // Display the median of the current window.
        cout << "  " << sm.getMedian();
    }

    cout << endl;

    return 0;
}