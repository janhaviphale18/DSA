
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

    // Peek operation
    void peek()
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

    int elements[] = {10, 20, 30, 40, 50, 60, 70};
    int n = 7;

    h.initialize(elements, n);

    cout << "Min Heap Implementation\n\n";

    h.display();

    cout << "\nPerforming Peek Operation:\n";

    h.peek();

    cout << "\nHeap after Peek Operation:\n";

    h.display();

    return 0;
}
