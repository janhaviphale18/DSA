
#include <iostream>
using namespace std;

class MinHeap
{
    int arr[100];
    int size;

public:

    MinHeap()
    {
        size = 0;
    }

    // Initialize Min Heap
    void initialize(int elements[], int n)
    {
        size = n;

        for (int i = 0; i < n; i++)
        {
            arr[i] = elements[i];
        }
    }

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

    // Delete root element
    void deleteRoot()
    {
        if (size == 0)
        {
            cout << "Heap is empty." << endl;
            return;
        }

        cout << "Deleted Element: " << arr[0] << endl;

        arr[0] = arr[size - 1];

        size--;

        if (size > 0)
        {
            heapifyDown(0);
        }
    }

    // Display Heap
    void display()
    {
        if (size == 0)
        {
            cout << "Heap is empty." << endl;
            return;
        }

        cout << "Min Heap: ";

        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
    }
};

int main()
{
    MinHeap h;

    int elements[] = {10, 20, 30, 40, 50, 60};
    int n = 6;

    h.initialize(elements, n);

    cout << "Original Min Heap:\n";
    h.display();

    cout << "\nDeleting root element...\n";

    h.deleteRoot();

    cout << "\nMin Heap after deletion:\n";
    h.display();

    return 0;
}
