
#include <iostream>
#include <algorithm>
using namespace std;

class MinHeap
{
    int arr[100];
    int size;

    // Heapify Up
    void heapifyUp(int i)
    {
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

    // Heapify Down
    void heapifyDown(int i)
    {
        while (true)
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
                i = smallest;
            }
            else
            {
                break;
            }
        }
    }

public:

    MinHeap()
    {
        size = 0;
    }

    // Insert element
    bool insert(int value)
    {
        if (size == 100)
        {
            return false;
        }

        arr[size] = value;

        heapifyUp(size);

        size++;

        return true;
    }

    // Update element at given index
    bool update(int index, int newValue, int &oldValue)
    {
        if (index < 0 || index >= size)
        {
            return false;
        }

        oldValue = arr[index];

        arr[index] = newValue;

        if (newValue < oldValue)
        {
            heapifyUp(index);
        }
        else if (newValue > oldValue)
        {
            heapifyDown(index);
        }

        return true;
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

    int n, value;

    cout << "Enter number of elements: ";

    if (!(cin >> n) || n < 1 || n > 100)
    {
        cout << "Invalid number of elements." << endl;
        return 0;
    }

    cout << "Enter " << n << " elements:\n";

    for (int i = 0; i < n; i++)
    {
        if (!(cin >> value))
        {
            cout << "Invalid element." << endl;
            return 0;
        }

        h.insert(value);
    }

    cout << "\nOriginal Min Heap:\n";
    h.display();

    int index, newValue, oldValue;

    cout << "\nEnter index to update (0-based): ";

    if (!(cin >> index))
    {
        cout << "Invalid index input." << endl;
        return 0;
    }

    cout << "Enter new value: ";

    if (!(cin >> newValue))
    {
        cout << "Invalid value input." << endl;
        return 0;
    }

    if (h.update(index, newValue, oldValue))
    {
        cout << "\nOld Value: " << oldValue << endl;
        cout << "New Value: " << newValue << endl;

        cout << "\nUpdated Min Heap:\n";
        h.display();
    }
    else
    {
        cout << "\nInvalid index. Update not possible." << endl;
    }

    return 0;
}
