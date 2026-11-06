#include <iostream>
#include <iomanip>
using namespace std;

class MaxHeap
{
    int heap[1000];
    int size;

    void heapifyDown(int index)
    {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] > heap[largest])
            largest = left;

        if (right < size && heap[right] > heap[largest])
            largest = right;

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

    int getSize()
    {
        return size;
    }

    int getTop()
    {
        return heap[0];
    }

    void insert(int value)
    {
        if (size == 1000)
            return;

        int index = size;
        heap[size] = value;
        size++;

        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (heap[parent] >= heap[index])
                break;

            swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    int extractMax()
    {
        int maximum = heap[0];

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);

        return maximum;
    }
};

class MinHeap
{
    int heap[1000];
    int size;

    void heapifyDown(int index)
    {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

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

    int getSize()
    {
        return size;
    }

    int getTop()
    {
        return heap[0];
    }

    void insert(int value)
    {
        if (size == 1000)
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
            heapifyDown(0);

        return minimum;
    }
};

int main()
{
    int n, value;

    cout << "Enter number of stream elements (1-1000): ";
    cin >> n;

    if (n < 1 || n > 1000)
    {
        cout << "Invalid number of elements!";
        return 0;
    }

    MaxHeap lowerHalf;
    MinHeap upperHalf;

    cout << "\nEnter stream elements one by one:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Element " << i + 1 << ": ";
        cin >> value;

        // Insert into the appropriate heap.
        if (lowerHalf.isEmpty() ||
            value <= lowerHalf.getTop())
        {
            lowerHalf.insert(value);
        }
        else
        {
            upperHalf.insert(value);
        }

        // Balance the sizes of both heaps.
        if (lowerHalf.getSize() > upperHalf.getSize() + 1)
        {
            upperHalf.insert(lowerHalf.extractMax());
        }
        else if (upperHalf.getSize() > lowerHalf.getSize())
        {
            lowerHalf.insert(upperHalf.extractMin());
        }

        // Calculate and display the running median.
        double median;

        if (lowerHalf.getSize() == upperHalf.getSize())
        {
            median = ((long long)lowerHalf.getTop()
                     + upperHalf.getTop()) / 2.0;
        }
        else
        {
            median = lowerHalf.getTop();
        }

        cout << "Median after " << i + 1
             << " elements: "
             << fixed << setprecision(2)
             << median << endl;
    }

    return 0;
}
