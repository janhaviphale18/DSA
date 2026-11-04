
#include <iostream>
using namespace std;

class HeapSort
{
private:
    int arr[100];
    int size;

    // Maintain Max Heap property
    void heapify(int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
        {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest])
        {
            largest = right;
        }

        if (largest != i)
        {
            swap(arr[i], arr[largest]);

            heapify(n, largest);
        }
    }

    // Build Max Heap
    void buildMaxHeap()
    {
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            heapify(size, i);
        }
    }

public:
    // Accept array elements
    bool input()
    {
        cout << "Enter number of elements (1-100): ";
        cin >> size;

        if (cin.fail() || size < 1 || size > 100)
        {
            cout << "Invalid size!" << endl;
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

        return true;
    }

    // Perform Heap Sort
    void sort()
    {
        buildMaxHeap();

        cout << "\nMax Heap: ";

        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;

        // Move maximum element to the end
        for (int i = size - 1; i > 0; i--)
        {
            swap(arr[0], arr[i]);

            // Restore heap property for remaining elements
            heapify(i, 0);
        }
    }

    // Display sorted array
    void display()
    {
        cout << "\nSorted Array (Ascending): ";

        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
    }
};

int main()
{
    HeapSort hs;

    if (!hs.input())
    {
        return 0;
    }

    hs.sort();
    hs.display();

    return 0;
}
