
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

    // Insert element into Min Heap
    void insert(int value)
    {
        if (size == 100)
        {
            cout << "Heap is full." << endl;
            return;
        }

        // Insert element at the end
        int i = size;
        arr[i] = value;
        size++;

        // Heapify Up
        while (i > 0)
        {
            int parent = (i - 1) / 2;

            if (arr[i] < arr[parent])
            {
                swap(arr[i], arr[parent]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }

    // Display Heap
    void display()
    {
        cout << "Min Heap: ";

        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
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
};

int main()
{
    MinHeap h;

    h.insert(20);
    h.insert(30);
    h.insert(40);
    h.insert(50);
    h.insert(60);
    h.insert(10);

    cout << "Min Heap after insertion:\n";

    h.display();

    h.getMin();

    return 0;
}
