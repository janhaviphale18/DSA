
#include <iostream>
#include <algorithm>
using namespace std;

class MinHeap
{
    int arr[100];
    int size;

    // Heapify Down
    void heapifyDown(int i)
    {
        int smallest = i;

        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && arr[left] < arr[smallest])
        {
            smallest = left;
        }

        if (right < size && arr[right] < arr[smallest])
        {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(arr[i], arr[smallest]);

            heapifyDown(smallest);
        }
    }

public:

    MinHeap()
    {
        size = 0;
    }

    // Accept array elements
    bool input()
    {
        cout << "Enter number of elements: ";

        if (!(cin >> size) || size < 1 || size > 100)
        {
            cout << "Invalid number of elements." << endl;
            size = 0;
            return false;
        }

        cout << "Enter " << size << " elements:\n";

        for (int i = 0; i < size; i++)
        {
            if (!(cin >> arr[i]))
            {
                cout << "Invalid element." << endl;
                size = 0;
                return false;
            }
        }

        return true;
    }

    // Display array
    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
    }

    // Build Min Heap using Heapify
    void buildHeap()
    {
        // Start from last non-leaf node
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            heapifyDown(i);
        }
    }

    // Display minimum element
    void getMin()
    {
        if (size == 0)
        {
            cout << "Heap is empty." << endl;
        }
        else
        {
            cout << "Minimum Element: " << arr[0] << endl;
        }
    }

    // Verify Min Heap property
    bool isMinHeap()
    {
        for (int i = 0; i < size / 2; i++)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size && arr[i] > arr[left])
            {
                return false;
            }

            if (right < size && arr[i] > arr[right])
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    MinHeap h;

    cout << "MIN HEAPIFY IMPLEMENTATION\n\n";

    if (!h.input())
    {
        return 0;
    }

    cout << "\nOriginal Array:\n";
    h.display();

    h.buildHeap();

    cout << "\nArray after Heapify:\n";
    h.display();

    cout << "\nMin Heap Verification:\n";

    if (h.isMinHeap())
    {
        cout << "Valid Min Heap." << endl;
    }
    else
    {
        cout << "Invalid Min Heap." << endl;
    }

    h.getMin();

    return 0;
}
