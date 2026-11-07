#include <iostream>
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
        {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest])
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
        {
            heapifyDown(0);
        }

        return maximum;
    }
};

int main()
{
    int n, weight;

    cout << "Enter number of stones (1-1000): ";
    cin >> n;

    if (n < 1 || n > 1000)
    {
        cout << "Invalid number of stones!";
        return 0;
    }

    MaxHeap maxHeap;

    cout << "Enter the weights of stones: ";

    for (int i = 0; i < n; i++)
    {
        cin >> weight;

        if (weight <= 0)
        {
            cout << "Stone weight must be positive!";
            return 0;
        }

        maxHeap.insert(weight);
    }

    int smashCount = 1;

    // Continue until at most one stone remains.
    while (maxHeap.getSize() > 1)
    {
        int first = maxHeap.extractMax();
        int second = maxHeap.extractMax();

        cout << "\nSmash " << smashCount << ": "
             << first << " and " << second;

        if (first == second)
        {
            cout << " -> Both stones destroyed";
        }
        else
        {
            int remaining = first - second;

            cout << " -> Remaining stone: " << remaining;

            maxHeap.insert(remaining);
        }

        smashCount++;
    }

    int result = 0;

    if (maxHeap.getSize() == 1)
    {
        result = maxHeap.extractMax();
    }

    cout << "\n\nFinal remaining stone weight: "
         << result << endl;

    return 0;
}
