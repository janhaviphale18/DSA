
#include <iostream>
using namespace std;

class KthLargest
{
private:
    int arr[100];
    int heap[100];
    int size;
    int heapSize;
    int k;

    // Maintain Min Heap property
    void heapifyDown(int n, int i)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left] < heap[smallest])
        {
            smallest = left;
        }

        if (right < n && heap[right] < heap[smallest])
        {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            heapifyDown(n, smallest);
        }
    }

    // Restore Min Heap property upwards
    void heapifyUp(int index)
    {
        int parent = (index - 1) / 2;

        while (index > 0 && heap[index] < heap[parent])
        {
            swap(heap[index], heap[parent]);

            index = parent;
            parent = (index - 1) / 2;
        }
    }

    // Build Min Heap from first K elements
    void buildMinHeap()
    {
        for (int i = heapSize / 2 - 1; i >= 0; i--)
        {
            heapifyDown(heapSize, i);
        }
    }

public:
    // Accept input
    bool input()
    {
        cout << "Enter number of elements (1-100): ";
        cin >> size;

        if (cin.fail() || size < 1 || size > 100)
        {
            cout << "Invalid array size!" << endl;
            return false;
        }

        cout << "Enter " << size << " elements:" << endl;

        for (int i = 0; i < size; i++)
        {
            cin >> arr[i];

            if (cin.fail())
            {
                cout << "Invalid element!" << endl;
                return false;
            }
        }

        cout << "Enter the value of K: ";
        cin >> k;

        if (cin.fail() || k < 1 || k > size)
        {
            cout << "Invalid value of K!" << endl;
            return false;
        }

        return true;
    }

    // Find Kth largest element
    void findKthLargest()
    {
        heapSize = k;

        // Copy first K elements into Min Heap
        for (int i = 0; i < k; i++)
        {
            heap[i] = arr[i];
        }

        buildMinHeap();

        cout << "\nInitial Min Heap: ";

        for (int i = 0; i < heapSize; i++)
        {
            cout << heap[i] << " ";
        }

        // Process remaining elements
        for (int i = k; i < size; i++)
        {
            if (arr[i] > heap[0])
            {
                heap[0] = arr[i];
                heapifyDown(heapSize, 0);
            }
        }

        cout << "\n\nFinal Min Heap: ";

        for (int i = 0; i < heapSize; i++)
        {
            cout << heap[i] << " ";
        }

        cout << "\n\nKth Largest Element: " << heap[0] << endl;
    }
};

int main()
{
    KthLargest obj;

    if (!obj.input())
    {
        return 0;
    }

    obj.findKthLargest();

    return 0;
}
