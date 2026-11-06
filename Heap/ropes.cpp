#include <iostream>
using namespace std;

class MinHeap
{
    long long heap[1000];
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

    int getSize()
    {
        return size;
    }

    void insert(long long value)
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

    long long extractMin()
    {
        long long minimum = heap[0];

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
    int n;
    long long length;

    cout << "Enter number of ropes (1-1000): ";
    cin >> n;

    if (n < 1 || n > 1000)
    {
        cout << "Invalid number of ropes!";
        return 0;
    }

    MinHeap minHeap;

    cout << "Enter the lengths of the ropes: ";

    for (int i = 0; i < n; i++)
    {
        cin >> length;

        if (length <= 0)
        {
            cout << "Rope lengths must be positive!";
            return 0;
        }

        minHeap.insert(length);
    }

    long long totalCost = 0;

    // Continue until only one rope remains.
    while (minHeap.getSize() > 1)
    {
        // Extract the two shortest ropes.
        long long first = minHeap.extractMin();
        long long second = minHeap.extractMin();

        // Calculate the cost of connecting them.
        long long connectedLength = first + second;

        totalCost += connectedLength;

        cout << "\nConnecting " << first
             << " and " << second
             << " -> Cost: " << connectedLength;

        // Insert the newly formed rope.
        minHeap.insert(connectedLength);
    }

    cout << "\n\nMinimum total cost: "
         << totalCost << endl;

    return 0;
}
