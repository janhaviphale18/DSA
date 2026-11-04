
#include <iostream>
using namespace std;

class KthSmallest
{
private:
    int arr[100];
    int size;

    // Restore Min Heap property
    void heapifyDown(int n, int i)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] < arr[smallest])
        {
            smallest = left;
        }

        if (right < n && arr[right] < arr[smallest])
        {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(arr[i], arr[smallest]);
            heapifyDown(n, smallest);
        }
    }

    // Build Min Heap
    void buildMinHeap()
    {
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            heapifyDown(size, i);
        }
    }

    // Extract minimum element
    int extractMin()
    {
        int minimum = arr[0];

        arr[0] = arr[size - 1];
        size--;

        if (size > 0)
        {
            heapifyDown(size, 0);
        }

        return minimum;
    }

public:
    // Accept array input
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

        return true;
    }

    // Find Kth smallest element
    void findKthSmallest(int k)
    {
        if (k < 1 || k > size)
        {
            cout << "Invalid value of K!" << endl;
            return;
        }

        buildMinHeap();

        cout << "\nMin Heap: ";

        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }

        cout << "\n\nExtracted Elements: ";

        int result = 0;

        for (int i = 1; i <= k; i++)
        {
            result = extractMin();
            cout << result << " ";
        }

        cout << "\n\nKth Smallest Element: " << result << endl;
    }
};

int main()
{
    KthSmallest obj;

    if (!obj.input())
    {
        return 0;
    }

    int k;

    cout << "Enter the value of K: ";
    cin >> k;

    if (cin.fail())
    {
        cout << "Invalid value of K!" << endl;
        return 0;
    }

    obj.findKthSmallest(k);

    return 0;
}
