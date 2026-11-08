#include <iostream>
#include <algorithm>
using namespace std;

class MinHeap
{
    int heap[1000];
    int size;

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (heap[parent] <= heap[index])
                break;

            swap(heap[parent], heap[index]);

            index = parent;
        }
    }

    void heapifyDown(int index)
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

public:

    MinHeap()
    {
        size = 0;
    }

    void insert(int value)
    {
        if (size == 1000)
        {
            cout << "Heap is full!" << endl;
            return;
        }

        heap[size] = value;

        heapifyUp(size);

        size++;
    }

    void display()
    {
        if (size == 0)
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        cout << "Heap elements: ";

        for (int i = 0; i < size; i++)
        {
            cout << heap[i] << " ";
        }

        cout << endl;
    }

    void deleteElement(int value)
    {
        if (size == 0)
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        int index = -1;

        // Search for the element.
        for (int i = 0; i < size; i++)
        {
            if (heap[i] == value)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "Element not found in Heap!" << endl;
            return;
        }

        // Replace the element with the last element.
        heap[index] = heap[size - 1];

        size--;

        // Restore the Min Heap property.
        if (index < size)
        {
            if (index > 0 &&
                heap[index] < heap[(index - 1) / 2])
            {
                heapifyUp(index);
            }
            else
            {
                heapifyDown(index);
            }
        }

        cout << "Element " << value
             << " deleted successfully!" << endl;
    }
};

int main()
{
    MinHeap h;

    int n, value, key;

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

    cout << "\nOriginal Min Heap:\n";
    h.display();

    cout << "\nEnter element to delete: ";
    cin >> key;

    h.deleteElement(key);

    cout << "\nMin Heap after deletion:\n";
    h.display();

    return 0;
}