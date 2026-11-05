#include <iostream>
using namespace std;

class KthLargestStream
{
private:
    int heap[100];
    int heapSize;
    int k;

    // Restore Min Heap property upwards
    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (heap[index] >= heap[parent])
            {
                break;
            }

            swap(heap[index], heap[parent]);

            index = parent;
        }
    }

    // Restore Min Heap property downwards
    void heapifyDown(int index)
    {
        while (true)
        {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < heapSize &&
                heap[left] < heap[smallest])
            {
                smallest = left;
            }

            if (right < heapSize &&
                heap[right] < heap[smallest])
            {
                smallest = right;
            }

            if (smallest == index)
            {
                break;
            }

            swap(heap[index], heap[smallest]);

            index = smallest;
        }
    }

public:
    KthLargestStream(int value)
    {
        k = value;
        heapSize = 0;
    }

    // Process a new incoming element
    void addElement(int value)
    {
        if (heapSize < k)
        {
            heap[heapSize] = value;

            heapifyUp(heapSize);

            heapSize++;
        }
        else if (value > heap[0])
        {
            heap[0] = value;

            heapifyDown(0);
        }
        // Otherwise, the element is not among
        // the K largest elements.
    }

    // Display current Kth largest element
    void displayKthLargest()
    {
        if (heapSize < k)
        {
            cout << "Kth Largest Element: Not Available";
        }
        else
        {
            cout << "Kth Largest Element: " << heap[0];
        }

        cout << endl;
    }

    // Display current Min Heap
    void displayHeap()
    {
        cout << "Current Min Heap: ";

        if (heapSize == 0)
        {
            cout << "Empty";
        }

        for (int i = 0; i < heapSize; i++)
        {
            cout << heap[i] << " ";
        }

        cout << endl;
    }

    // Display heap size
    int getSize()
    {
        return heapSize;
    }
};

int main()
{
    int k, n, value;

    cout << "Enter the value of K: ";
    cin >> k;

    if (cin.fail() || k < 1 || k > 100)
    {
        cout << "Invalid value of K!" << endl;
        return 0;
    }

    cout << "Enter number of incoming elements (1-100): ";
    cin >> n;

    if (cin.fail() || n < 1 || n > 100)
    {
        cout << "Invalid number of elements!" << endl;
        return 0;
    }

    KthLargestStream stream(k);

    cout << "\nEnter incoming stream elements:" << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> value;

        if (cin.fail())
        {
            cout << "Invalid input!" << endl;
            return 0;
        }

        stream.addElement(value);

        cout << "\nAfter receiving " << value << ":" << endl;

        stream.displayHeap();
        stream.displayKthLargest();
    }

    cout << "\n--- Final Result ---" << endl;

    stream.displayHeap();
    stream.displayKthLargest();

    return 0;
}
