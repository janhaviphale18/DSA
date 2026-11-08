#include <iostream>
#include <algorithm>
using namespace std;

class MaxHeap
{
    int heap[1000];
    int size;

    // Restore Max Heap property upwards.
    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (heap[parent] >= heap[index])
                break;

            swap(heap[parent], heap[index]);

            index = parent;
        }
    }

    // Restore Max Heap property downwards.
    void heapifyDown(int index)
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

public:

    MaxHeap()
    {
        size = 0;
    }

    // Insert an element into Max Heap.
    void insert(int value)
    {
        if (size == 1000)
        {
            cout << "Heap capacity exceeded!" << endl;
            return;
        }

        heap[size] = value;

        heapifyUp(size);

        size++;
    }

    // Increase the value at a given index.
    void increaseKey(int index, int newValue)
    {
        if (size == 0)
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        if (index < 0 || index >= size)
        {
            cout << "Invalid heap index!" << endl;
            return;
        }

        if (newValue < heap[index])
        {
            cout << "New value must be greater than or equal "
                 << "to the current value!" << endl;
            return;
        }

        int oldValue = heap[index];

        heap[index] = newValue;

        // Only Heapify Up is required.
        heapifyUp(index);

        cout << "Key increased successfully!" << endl;
        cout << "Old value: " << oldValue << endl;
        cout << "New value: " << newValue << endl;
    }

    // Display heap elements with indices.
    void display()
    {
        if (size == 0)
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        cout << "\nHeap elements:\n";

        for (int i = 0; i < size; i++)
        {
            cout << "Index " << i
                 << " : " << heap[i] << endl;
        }
    }
};

int main()
{
    MaxHeap h;

    int n, value;
    int index, newValue;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n < 1 || n > 1000)
    {
        cout << "Invalid number of elements!" << endl;
        return 0;
    }

    cout << "Enter heap elements:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> value;
        h.insert(value);
    }

    cout << "\nOriginal Max Heap:";
    h.display();

    cout << "\nEnter index of element to increase: ";
    cin >> index;

    cout << "Enter new increased value: ";
    cin >> newValue;

    h.increaseKey(index, newValue);

    cout << "\nMax Heap after Increase Key:";
    h.display();

    return 0;
}