#include <iostream>
#include <algorithm>
using namespace std;

class HeapConverter
{
    int heap[1000];
    int size;

    // Restore Min Heap property.
    void minHeapifyDown(int index)
    {
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size &&
                heap[left] < heap[smallest])
            {
                smallest = left;
            }

            if (right < size &&
                heap[right] < heap[smallest])
            {
                smallest = right;
            }

            if (smallest == index)
                break;

            swap(heap[index], heap[smallest]);

            index = smallest;
        }
    }

    // Restore Max Heap property.
    void maxHeapifyDown(int index)
    {
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size &&
                heap[left] > heap[largest])
            {
                largest = left;
            }

            if (right < size &&
                heap[right] > heap[largest])
            {
                largest = right;
            }

            if (largest == index)
                break;

            swap(heap[index], heap[largest]);

            index = largest;
        }
    }

    // Build Min Heap using bottom-up heapification.
    void buildMinHeap()
    {
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            minHeapifyDown(i);
        }
    }

    // Build Max Heap using bottom-up heapification.
    void buildMaxHeap()
    {
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            maxHeapifyDown(i);
        }
    }

public:

    HeapConverter()
    {
        size = 0;
    }

    void input()
    {
        cout << "Enter number of elements: ";
        cin >> size;

        if (size < 1 || size > 1000)
        {
            cout << "Invalid number of elements!" << endl;
            size = 0;
            return;
        }

        cout << "Enter elements:\n";

        for (int i = 0; i < size; i++)
        {
            cin >> heap[i];
        }
    }

    void convert()
    {
        if (size == 0)
        {
            cout << "No elements available!" << endl;
            return;
        }

        // First construct a Min Heap.
        buildMinHeap();

        cout << "\nMin Heap:\n";
        display();

        // Convert the same array into a Max Heap.
        buildMaxHeap();

        cout << "\nMax Heap after conversion:\n";
        display();

        if (isMaxHeap())
        {
            cout << "\nConversion successful!" << endl;
            cout << "Max Heap property verified." << endl;
        }
        else
        {
            cout << "\nConversion failed!" << endl;
        }
    }

    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << heap[i] << " ";
        }

        cout << endl;
    }

    // Verify Max Heap property.
    bool isMaxHeap()
    {
        for (int i = 0; i < size; i++)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size && heap[i] < heap[left])
                return false;

            if (right < size && heap[i] < heap[right])
                return false;
        }

        return true;
    }
};

int main()
{
    HeapConverter h;

    h.input();

    h.convert();

    return 0;
}