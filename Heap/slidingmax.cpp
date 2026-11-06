#include <iostream>
#include <algorithm>
using namespace std;

struct Element
{
    int value;
    int index;
};

class MaxHeap
{
    Element heap[1000];
    int size;

    bool isGreater(Element a, Element b)
    {
        if (a.value != b.value)
            return a.value > b.value;

        return a.index > b.index;
    }

    void heapifyDown(int index)
    {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size &&
            isGreater(heap[left], heap[largest]))
        {
            largest = left;
        }

        if (right < size &&
            isGreater(heap[right], heap[largest]))
        {
            largest = right;
        }

        if (largest != index)
        {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap()
    {
        size = 0;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void insert(int value, int index)
    {
        if (size == 1000)
            return;

        Element element;
        element.value = value;
        element.index = index;

        int position = size;
        heap[size] = element;
        size++;

        while (position > 0)
        {
            int parent = (position - 1) / 2;

            if (!isGreater(heap[position], heap[parent]))
                break;

            swap(heap[position], heap[parent]);
            position = parent;
        }
    }

    Element getMaximum()
    {
        return heap[0];
    }

    void extractMax()
    {
        if (size == 0)
            return;

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);
    }
};

int main()
{
    int n, k;
    int arr[1000];

    cout << "Enter number of elements (1-1000): ";
    cin >> n;

    if (n < 1 || n > 1000)
    {
        cout << "Invalid number of elements!";
        return 0;
    }

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter window size K (1 to " << n << "): ";
    cin >> k;

    if (k < 1 || k > n)
    {
        cout << "Invalid window size!";
        return 0;
    }

    MaxHeap maxHeap;

    cout << "\nMaximum elements in each window:\n";

    for (int i = 0; i < n; i++)
    {
        // Insert current element with its index.
        maxHeap.insert(arr[i], i);

        // Remove elements outside the current window.
        while (!maxHeap.isEmpty() &&
               maxHeap.getMaximum().index <= i - k)
        {
            maxHeap.extractMax();
        }

        // Display maximum once the first window is complete.
        if (i >= k - 1)
        {
            cout << maxHeap.getMaximum().value << " ";
        }
    }

    cout << endl;

    return 0;
}
