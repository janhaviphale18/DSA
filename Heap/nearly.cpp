#include <iostream>
using namespace std;

class MinHeap
{
    int heap[101];
    int size;

    void heapifyDown(int index)
    {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] < heap[smallest])
        {
            smallest = left;
        }

        if (right < size && heap[right] < heap[smallest])
        {
            smallest = right;
        }

        if (smallest != index)
        {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap()
    {
        size = 0;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void insert(int value)
    {
        if (size == 101)
            return;

        int index = size;
        heap[size] = value;
        size++;

        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (heap[parent] <= heap[index])
                break;

            swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    int extractMin()
    {
        int minimum = heap[0];

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
        {
            heapifyDown(0);
        }

        return minimum;
    }
};

int main()
{
    int n, k;

    cout << "Enter number of elements (1-1000): ";
    cin >> n;

    if (n < 1 || n > 1000)
    {
        cout << "Invalid number of elements!";
        return 0;
    }

    int arr[1000];

    cout << "Enter the array elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter K (0 to " << n - 1 << "): ";
    cin >> k;

    if (k < 0 || k >= n)
    {
        cout << "Invalid value of K!";
        return 0;
    }

    MinHeap minHeap;

    int index = 0;

    // Insert the first K+1 elements.
    int initialSize = k + 1;

    for (int i = 0; i < initialSize; i++)
    {
        minHeap.insert(arr[i]);
    }

    // Extract the minimum and insert the next element.
    for (int i = initialSize; i < n; i++)
    {
        arr[index] = minHeap.extractMin();
        index++;

        minHeap.insert(arr[i]);
    }

    // Extract all remaining elements.
    while (!minHeap.isEmpty())
    {
        arr[index] = minHeap.extractMin();
        index++;
    }

    cout << "\nSorted array: ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}
