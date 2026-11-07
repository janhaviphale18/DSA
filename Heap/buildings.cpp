#include <iostream>
using namespace std;

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

    int getSize()
    {
        return size;
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
        {
            heapifyDown(0);
        }

        return minimum;
    }
};

int main()
{
    int n, bricks, ladders;

    int heights[1000];

    cout << "Enter number of buildings (1-1000): ";
    cin >> n;

    if (n < 1 || n > 1000)
    {
        cout << "Invalid number of buildings!";
        return 0;
    }

    cout << "Enter building heights: ";

    for (int i = 0; i < n; i++)
    {
        cin >> heights[i];

        if (heights[i] < 0)
        {
            cout << "Building heights cannot be negative!";
            return 0;
        }
    }

    cout << "Enter available bricks: ";
    cin >> bricks;

    if (bricks < 0)
    {
        cout << "Bricks cannot be negative!";
        return 0;
    }

    cout << "Enter available ladders: ";
    cin >> ladders;

    if (ladders < 0)
    {
        cout << "Ladders cannot be negative!";
        return 0;
    }

    MinHeap minHeap;

    long long remainingBricks = bricks;
    int furthest = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int difference = heights[i + 1] - heights[i];

        // No resource is required for a downward
        // or equal-height movement.
        if (difference <= 0)
        {
            furthest = i + 1;
            continue;
        }

        // Store the upward climb in the Min Heap.
        minHeap.insert(difference);

        // Use a ladder for the largest climbs.
        if (minHeap.getSize() > ladders)
        {
            remainingBricks -= minHeap.extractMin();
        }

        // Check whether enough bricks remain.
        if (remainingBricks < 0)
        {
            break;
        }

        furthest = i + 1;
    }

    cout << "\nFurthest building index: "
         << furthest << endl;

    cout << "Building height: "
         << heights[furthest] << endl;

    return 0;
}
