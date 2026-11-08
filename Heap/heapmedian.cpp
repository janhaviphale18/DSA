
#include <iostream>
#include <iomanip>
using namespace std;

const int MAX = 1000;

class MaxHeap
{
private:
    int heap[MAX];
    int size;

    void heapifyUp(int i)
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;

            if (heap[i] > heap[parent])
            {
                swap(heap[i], heap[parent]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }

    void heapifyDown(int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left] > heap[largest])
        {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest])
        {
            largest = right;
        }

        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap()
    {
        size = 0;
    }

    bool insert(int value)
    {
        if (size == MAX)
        {
            return false;
        }

        heap[size] = value;
        heapifyUp(size);
        size++;

        return true;
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

    int getMax()
    {
        return heap[0];
    }

    int getSize()
    {
        return size;
    }
};

class MinHeap
{
private:
    int heap[MAX];
    int size;

    void heapifyUp(int i)
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;

            if (heap[i] < heap[parent])
            {
                swap(heap[i], heap[parent]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }

    void heapifyDown(int i)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left] < heap[smallest])
        {
            smallest = left;
        }

        if (right < size && heap[right] < heap[smallest])
        {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap()
    {
        size = 0;
    }

    bool insert(int value)
    {
        if (size == MAX)
        {
            return false;
        }

        heap[size] = value;
        heapifyUp(size);
        size++;

        return true;
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

    int getMin()
    {
        return heap[0];
    }

    int getSize()
    {
        return size;
    }
};

class RunningMedian
{
private:
    MaxHeap smaller;
    MinHeap larger;

public:
    void insert(int value)
    {
        // Insert into the appropriate heap
        if (smaller.getSize() == 0 ||
            value <= smaller.getMax())
        {
            smaller.insert(value);
        }
        else
        {
            larger.insert(value);
        }

        // Balance the sizes of both heaps
        if (smaller.getSize() > larger.getSize() + 1)
        {
            larger.insert(smaller.extractMax());
        }
        else if (larger.getSize() > smaller.getSize() + 1)
        {
            smaller.insert(larger.extractMin());
        }

        // Maintain ordering between both heaps
        if (smaller.getSize() > 0 &&
            larger.getSize() > 0 &&
            smaller.getMax() > larger.getMin())
        {
            int left = smaller.extractMax();
            int right = larger.extractMin();

            smaller.insert(right);
            larger.insert(left);
        }
    }

    double getMedian()
    {
        int leftSize = smaller.getSize();
        int rightSize = larger.getSize();

        if (leftSize > rightSize)
        {
            return smaller.getMax();
        }

        if (rightSize > leftSize)
        {
            return larger.getMin();
        }

        // Convert to double before addition to avoid integer overflow
        return ((double)smaller.getMax() +
                (double)larger.getMin()) / 2.0;
    }
};

int main()
{
    RunningMedian median;

    int n, value;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n < 1 || n > MAX * 2)
    {
        cout << "Invalid number of elements.\n";
        return 1;
    }

    cout << "\nEnter the elements one by one:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Element " << i + 1 << ": ";
        cin >> value;

        median.insert(value);

        cout << "Running Median: "
             << fixed << setprecision(2)
             << median.getMedian() << endl;
    }

    return 0;
}
