
#include <iostream>
using namespace std;

class CustomPriorityQueue
{
private:
    int arr[100];
    int size;

    // Restore Max Heap property upwards
    void heapifyUp(int index)
    {
        int parent = (index - 1) / 2;

        while (index > 0 && arr[index] > arr[parent])
        {
            swap(arr[index], arr[parent]);

            index = parent;
            parent = (index - 1) / 2;
        }
    }

    // Restore Max Heap property downwards
    void heapifyDown(int index)
    {
        while (true)
        {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size && arr[left] > arr[largest])
            {
                largest = left;
            }

            if (right < size && arr[right] > arr[largest])
            {
                largest = right;
            }

            if (largest == index)
            {
                break;
            }

            swap(arr[index], arr[largest]);

            index = largest;
        }
    }

public:
    CustomPriorityQueue()
    {
        size = 0;
    }

    // Insert a new element
    void insert(int value)
    {
        if (size == 100)
        {
            cout << "Priority Queue is full!" << endl;
            return;
        }

        arr[size] = value;

        heapifyUp(size);

        size++;

        cout << value << " inserted successfully." << endl;
    }

    // Return highest-priority element
    void peek()
    {
        if (size == 0)
        {
            cout << "Priority Queue is empty!" << endl;
            return;
        }

        cout << "Highest Priority Element: "
             << arr[0] << endl;
    }

    // Remove highest-priority element
    void removeHighest()
    {
        if (size == 0)
        {
            cout << "Priority Queue is empty!" << endl;
            return;
        }

        int removed = arr[0];

        arr[0] = arr[size - 1];
        size--;

        if (size > 0)
        {
            heapifyDown(0);
        }

        cout << "Removed Element: " << removed << endl;
    }

    // Display all elements in heap array order
    void display()
    {
        if (size == 0)
        {
            cout << "Priority Queue is empty!" << endl;
            return;
        }

        cout << "Priority Queue (Heap Array): ";

        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
    }

    // Display elements in descending priority order
    void displayPriorityOrder()
    {
        if (size == 0)
        {
            cout << "Priority Queue is empty!" << endl;
            return;
        }

        int temp[100];
        int tempSize = size;

        for (int i = 0; i < size; i++)
        {
            temp[i] = arr[i];
        }

        cout << "Elements in Priority Order: ";

        while (tempSize > 0)
        {
            cout << temp[0] << " ";

            temp[0] = temp[tempSize - 1];
            tempSize--;

            // Restore Max Heap in temporary array
            int index = 0;

            while (true)
            {
                int largest = index;
                int left = 2 * index + 1;
                int right = 2 * index + 2;

                if (left < tempSize && temp[left] > temp[largest])
                {
                    largest = left;
                }

                if (right < tempSize && temp[right] > temp[largest])
                {
                    largest = right;
                }

                if (largest == index)
                {
                    break;
                }

                swap(temp[index], temp[largest]);
                index = largest;
            }
        }

        cout << endl;
    }

    // Return current number of elements
    int getSize()
    {
        return size;
    }

    // Check whether queue is empty
    bool isEmpty()
    {
        return size == 0;
    }
};

int main()
{
    CustomPriorityQueue pq;

    int n, value;

    cout << "Enter number of elements (0-100): ";
    cin >> n;

    if (cin.fail() || n < 0 || n > 100)
    {
        cout << "Invalid number of elements!" << endl;
        return 0;
    }

    cout << "Enter " << n << " elements:" << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> value;

        if (cin.fail())
        {
            cout << "Invalid input!" << endl;
            return 0;
        }

        pq.insert(value);
    }

    cout << "\n--- Priority Queue Details ---" << endl;

    pq.display();
    pq.peek();

    cout << "Number of Elements: " << pq.getSize() << endl;

    pq.displayPriorityOrder();

    cout << "\nEnter an element to insert: ";
    cin >> value;

    if (cin.fail())
    {
        cout << "Invalid input!" << endl;
        return 0;
    }

    pq.insert(value);

    cout << "\nAfter Insertion:" << endl;
    pq.display();

    cout << "\nRemoving Highest Priority Element:" << endl;
    pq.removeHighest();

    cout << "\nAfter Removal:" << endl;
    pq.display();

    cout << "\nElements in Priority Order:" << endl;
    pq.displayPriorityOrder();

    return 0;
}
