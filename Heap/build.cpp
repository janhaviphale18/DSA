
#include <iostream>
using namespace std;

class HeapBuilder
{
private:
    int minHeap[100];
    int maxHeap[100];
    int size;

    // Heapify Down for Min Heap
    void minHeapify(int i)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && minHeap[left] < minHeap[smallest])
        {
            smallest = left;
        }

        if (right < size && minHeap[right] < minHeap[smallest])
        {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(minHeap[i], minHeap[smallest]);
            minHeapify(smallest);
        }
    }

    // Heapify Down for Max Heap
    void maxHeapify(int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && maxHeap[left] > maxHeap[largest])
        {
            largest = left;
        }

        if (right < size && maxHeap[right] > maxHeap[largest])
        {
            largest = right;
        }

        if (largest != i)
        {
            swap(maxHeap[i], maxHeap[largest]);
            maxHeapify(largest);
        }
    }

public:
    // Accept input and initialize both arrays
    void input()
    {
        cout << "Enter number of elements (1-100): ";
        cin >> size;

        if (cin.fail() || size < 1 || size > 100)
        {
            cout << "Invalid size!" << endl;
            size = 0;
            return;
        }

        cout << "Enter " << size << " elements:" << endl;

        for (int i = 0; i < size; i++)
        {
            cin >> minHeap[i];

            if (cin.fail())
            {
                cout << "Invalid input!" << endl;
                size = 0;
                return;
            }

            maxHeap[i] = minHeap[i];
        }
    }

    // Build Min Heap using bottom-up approach
    void buildMinHeap()
    {
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            minHeapify(i);
        }
    }

    // Build Max Heap using bottom-up approach
    void buildMaxHeap()
    {
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            maxHeapify(i);
        }
    }

    // Display Min Heap
    void displayMinHeap()
    {
        cout << "Min Heap: ";

        for (int i = 0; i < size; i++)
        {
            cout << minHeap[i] << " ";
        }

        cout << endl;
    }

    // Display Max Heap
    void displayMaxHeap()
    {
        cout << "Max Heap: ";

        for (int i = 0; i < size; i++)
        {
            cout << maxHeap[i] << " ";
        }

        cout << endl;
    }

    // Verify Min Heap property
    bool isMinHeap()
    {
        for (int i = 0; i < size / 2; i++)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size && minHeap[i] > minHeap[left])
                return false;

            if (right < size && minHeap[i] > minHeap[right])
                return false;
        }

        return true;
    }

    // Verify Max Heap property
    bool isMaxHeap()
    {
        for (int i = 0; i < size / 2; i++)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size && maxHeap[i] < maxHeap[left])
                return false;

            if (right < size && maxHeap[i] < maxHeap[right])
                return false;
        }

        return true;
    }

    // Display root elements
    void displayRoots()
    {
        cout << "Minimum Element: " << minHeap[0] << endl;
        cout << "Maximum Element: " << maxHeap[0] << endl;
    }

    // Build and display both heaps
    void process()
    {
        if (size == 0)
            return;

        buildMinHeap();
        buildMaxHeap();

        cout << "\n--- Heap Construction Results ---" << endl;

        displayMinHeap();
        displayMaxHeap();

        cout << "\n--- Root Elements ---" << endl;
        displayRoots();

        cout << "\n--- Heap Verification ---" << endl;

        cout << "Min Heap Valid: "
             << (isMinHeap() ? "Yes" : "No") << endl;

        cout << "Max Heap Valid: "
             << (isMaxHeap() ? "Yes" : "No") << endl;
    }
};

int main()
{
    HeapBuilder heap;

    heap.input();
    heap.process();

    return 0;
}
